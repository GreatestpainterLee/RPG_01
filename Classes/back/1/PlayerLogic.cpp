#include "PlayerLogic.h"
#include "MainLogic.h"

#include "Controller.h"
#include "Player.h"
#include "Util.h"
#include "MonsterManager.h"
#include "Monster.h"
#include "PathManager.h"
#include "./scene/BaseScene.h"
#include "SceneManager.h"
#include "Skill.h"
#include "MonsterAI.h"
#include "EquipmentManager.h"
#include "SkillManager.h"
#include "Config.h"
#include "FlowWord.h"
#include "NetworkModule.h"
#include "MonsterLogic.h"
#include "PlayerManager.h"

RPG_01_BEGIN

	/************************************************************************
	*  处理玩家死亡
	************************************************************************/
PlayerLogic* PlayerLogic::m_pInstance = 0;

PlayerLogic* PlayerLogic::GetInstance()
{
	if (0 == m_pInstance)
	{
		m_pInstance = new PlayerLogic;
	}

	return m_pInstance;
}

PlayerLogic::PlayerLogic()
{

}

void PlayerLogic::HandlePlayerDie(Player* player)
{
	Game()->StopGame();
}

/************************************************************************
*  处理玩家的技能攻击
************************************************************************/
void PlayerLogic::HandlePlayerSkillAttack(Player* player,Skill* pSkill)
{
	if (pSkill == 0)
	{
		return ;
	}

	// 获取技能的坐标
	Point skillPoint = pSkill->getPosition();

	// 计算技能与玩家的相对方向
	int dir = Game()->GetPathManager()->GetDirection(player->getPosition(),skillPoint);

	// 玩家方向转动
	if (dir != player->GetDirection())
	{
		player->Action(CodeMsg::code_player_static,dir);
	}

	// 玩家的魔法值是否足够
	if (player->GetMagicValue() < pSkill->GetConsumeMagic())
	{
		return;
	}

	// 处理玩家的魔法值改变
	HandlePlayerMagicChange(player,-pSkill->GetConsumeMagic());

	// 施放技能
	pSkill->Action(pSkill->GetSkillID());

	// 取得技能的伤害范围
	Rect scope = pSkill->GetScope();

	// 技能的伤害值
	float damage = pSkill->GetDamageValue();

	// 获取怪物列表
	vector<Monster*> monsterList = Game()->GetMonsterManager()->GetMonsterList();

	// 遍历每一个怪物，检测每个怪物是否在伤害范围之内，如果在伤害范围之内就让怪物掉血
	for (int i = 0; i < monsterList.size(); ++i)
	{
		Monster* pMonster = monsterList[i];

		// 如果怪物已经死亡就不进行处理
		if (pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die || pMonster->isVisible() == false)
		{
			continue;
		}

		// 获得怪物的位置
		Point monsterPoint = monsterList[i]->getPosition();

		// 判断是否在伤害范围之内
		if (!Game()->GetPathManager()->IsInRect(scope,monsterPoint))
		{
			continue;
		}

		// 怪物有一定的概率会嘶吼
		if (Util::GetProbability() > 0.5)
		{
			monsterList[i]->Action(CodeMsg::code_monster_bellow,monsterList[i]->GetDirection());
		}

		// 设置怪物的血量
		monsterList[i]->SetBloodValue(monsterList[i]->GetBloodValue() - damage);

		// 如果怪物被打死
		if (monsterList[i]->GetBloodValue() <= 0)
		{
			// 处理怪物被击杀
			MonsterLogic::GetInstance()->HandleMonsterBeKilled(monsterList[i],player);
		}
	}
}



/************************************************************************
*  玩家跑动
************************************************************************/
void PlayerLogic::HandlePlayerRun(Player* player)
{
	//调整玩家的位置
	player->AdjustPosition();

	// 取得玩家的当前位置
	Point currentPoint = player->getPosition();

	// 如果当前位置已经和目的地相同，则不需要再移动
	if (currentPoint == player->GetDestPoint())
	{
		player->Action(CodeMsg::code_player_static,player->GetDirection());

		Game()->GetSceneManager()->GetCurrentScene()->ShowDestPoint(false);

		// 如果到达目的地之后有选中的怪物，则进行攻击
		if (Game()->GetCurrentSelectedMonster() != 0)
		{
			player->Action(CodeMsg::code_player_attack,player->GetDirection());
		}
	}
}

/************************************************************************
*  玩家攻击
************************************************************************/
void PlayerLogic::HandlePlayerAttack(Player* player,Monster* pMonster)
{
	if (pMonster == 0)
	{
		return;
	}

	if (pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die || pMonster->isVisible() == false)
	{
		return;
	}

	// 怪物掉血
	MonsterLogic::GetInstance()->HandleMonsterBloodChange(pMonster,- player->GetDamageValue());
	//Game()->GetSkillManager()->ShowBloodDropAnimation(pMonster,- GetPlayerManager()->GetMyPlayer()->GetDamageValue());
	if (pMonster->GetBloodValue() <= 0)
	{
		// 怪物被杀
		MonsterLogic::GetInstance()->HandleMonsterBeKilled(pMonster,player);
	}
}

/************************************************************************
*  玩家被攻击
************************************************************************/
void PlayerLogic::HandlePlayerBeAttack(Player* player,Monster* pMonster)
{
	// 玩家血量改变
	HandlePlayerBloodChange(player,-pMonster->GetDamageValue());

	Game()->GetSkillManager()->ShowBloodDropAnimation(player,-pMonster->GetDamageValue());


	if (player->GetMsg() != CodeMsg::code_player_attack)
	{
		//m_pPlayer->Action(CodeMsg::code_player_beaten,m_pPlayer->GetDirection());
	}

	if (player->GetBloodValue() <= 0)
	{
		// 玩家被打死了
		player->Action(CodeMsg::code_player_die,player->GetDirection());
	}
}

/************************************************************************
*  玩家升级
************************************************************************/
void PlayerLogic::HandlePlayerUpgrade(Player* player)
{
	player->Upgrade();
	if (player != Game()->GetPlayerManager()->GetPlayer(Game()->GetConfig()->GetRandomID()))
	{
		return;
	}
	Game()->GetSceneManager()->SetBloodProgress(100);
	Game()->GetSceneManager()->SetMagicProgress(100);
	Game()->GetSceneManager()->SetEmpiricalProgress(0);
}

/************************************************************************
*  玩家血量改变
************************************************************************/
void PlayerLogic::HandlePlayerBloodChange(Player* player,float fChangeValue)
{
	player->SetBloodValue(player->GetBloodValue() + fChangeValue);
	if (player != Game()->GetPlayerManager()->GetPlayer(Game()->GetConfig()->GetRandomID()))
	{
		return;
	}
	Game()->GetSceneManager()->SetBloodProgress(100 * player->GetBloodValue() / player->GetMaxBloodValue());
}


/************************************************************************
*  玩家魔法量改变
************************************************************************/
void PlayerLogic::HandlePlayerMagicChange(Player* player,float fChangeValue)
{
	player->SetMagicValue(player->GetMagicValue() + fChangeValue);
	if (player != Game()->GetPlayerManager()->GetPlayer(Game()->GetConfig()->GetRandomID()))
	{
		return;
	}
	Game()->GetSceneManager()->SetMagicProgress(100 * player->GetMagicValue() / player->GetMaxMagicValue());
}

/************************************************************************
*  玩家经验值改变
************************************************************************/
void PlayerLogic::HandlePlayerEmpiricalChange(Player* player,float fChangeValue)
{
	player->SetEmpiricalValue(player->GetEmpiricalValue() + fChangeValue);
	if (player != Game()->GetPlayerManager()->GetPlayer(Game()->GetConfig()->GetRandomID()))
	{
		return;
	}
	Game()->GetSceneManager()->SetEmpiricalProgress(100 * player->GetEmpiricalValue() / player->GetMaxEmpiricalValue());
}

/************************************************************************
*  玩家处理
************************************************************************/
void PlayerLogic::PlayerProcess(Player* player,Monster* pMonster)
{
	// 玩家跑动
	if (player->GetMsg() == CodeMsg::code_player_run)
	{
		HandlePlayerRun(player);
	}

	Point playerPosition = player->getPosition();

	// 玩家攻击
	if (player->GetMsg() == CodeMsg::code_player_attack)
	{
		Point monsterPosition = Game()->GetCurrentSelectedMonster()->getPosition();
		int direction = -1;

		int distance = Game()->GetPathManager()->GetDistance(playerPosition,monsterPosition,direction);

		if (distance > 50)
		{
			player->SetDirection(direction);
			player->SetDestPoint(monsterPosition);
			HandlePlayerRun(player);
		}
		else
		{
			HandlePlayerAttack(player,pMonster);
		}
	}

	// 技能攻击
	if (player->GetMsg() == CodeMsg::code_player_skillattack)
	{
		HandlePlayerSkillAttack(player,player->GetCurrentSkill());
		player->SetCurrentSkill(0);
	}
}
RPG_01_END