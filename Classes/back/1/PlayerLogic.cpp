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
	*  �����������
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
*  ������ҵļ��ܹ���
************************************************************************/
void PlayerLogic::HandlePlayerSkillAttack(Player* player,Skill* pSkill)
{
	if (pSkill == 0)
	{
		return ;
	}

	// ��ȡ���ܵ�����
	Point skillPoint = pSkill->getPosition();

	// ���㼼������ҵ���Է���
	int dir = Game()->GetPathManager()->GetDirection(player->getPosition(),skillPoint);

	// ��ҷ���ת��
	if (dir != player->GetDirection())
	{
		player->Action(CodeMsg::code_player_static,dir);
	}

	// ��ҵ�ħ��ֵ�Ƿ��㹻
	if (player->GetMagicValue() < pSkill->GetConsumeMagic())
	{
		return;
	}

	// ������ҵ�ħ��ֵ�ı�
	HandlePlayerMagicChange(player,-pSkill->GetConsumeMagic());

	// ʩ�ż���
	pSkill->Action(pSkill->GetSkillID());

	// ȡ�ü��ܵ��˺���Χ
	Rect scope = pSkill->GetScope();

	// ���ܵ��˺�ֵ
	float damage = pSkill->GetDamageValue();

	// ��ȡ�����б�
	vector<Monster*> monsterList = Game()->GetMonsterManager()->GetMonsterList();

	// ����ÿһ��������ÿ�������Ƿ����˺���Χ֮�ڣ�������˺���Χ֮�ھ��ù����Ѫ
	for (int i = 0; i < monsterList.size(); ++i)
	{
		Monster* pMonster = monsterList[i];

		// ��������Ѿ������Ͳ����д���
		if (pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die || pMonster->isVisible() == false)
		{
			continue;
		}

		// ��ù����λ��
		Point monsterPoint = monsterList[i]->getPosition();

		// �ж��Ƿ����˺���Χ֮��
		if (!Game()->GetPathManager()->IsInRect(scope,monsterPoint))
		{
			continue;
		}

		// ������һ���ĸ��ʻ�˻��
		if (Util::GetProbability() > 0.5)
		{
			monsterList[i]->Action(CodeMsg::code_monster_bellow,monsterList[i]->GetDirection());
		}

		// ���ù����Ѫ��
		monsterList[i]->SetBloodValue(monsterList[i]->GetBloodValue() - damage);

		// ������ﱻ����
		if (monsterList[i]->GetBloodValue() <= 0)
		{
			// ������ﱻ��ɱ
			MonsterLogic::GetInstance()->HandleMonsterBeKilled(monsterList[i],player);
		}
	}
}



/************************************************************************
*  ����ܶ�
************************************************************************/
void PlayerLogic::HandlePlayerRun(Player* player)
{
	//������ҵ�λ��
	player->AdjustPosition();

	// ȡ����ҵĵ�ǰλ��
	Point currentPoint = player->getPosition();

	// �����ǰλ���Ѿ���Ŀ�ĵ���ͬ������Ҫ���ƶ�
	if (currentPoint == player->GetDestPoint())
	{
		player->Action(CodeMsg::code_player_static,player->GetDirection());

		Game()->GetSceneManager()->GetCurrentScene()->ShowDestPoint(false);

		// �������Ŀ�ĵ�֮����ѡ�еĹ������й���
		if (Game()->GetCurrentSelectedMonster() != 0)
		{
			player->Action(CodeMsg::code_player_attack,player->GetDirection());
		}
	}
}

/************************************************************************
*  ��ҹ���
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

	// �����Ѫ
	MonsterLogic::GetInstance()->HandleMonsterBloodChange(pMonster,- player->GetDamageValue());
	//Game()->GetSkillManager()->ShowBloodDropAnimation(pMonster,- GetPlayerManager()->GetMyPlayer()->GetDamageValue());
	if (pMonster->GetBloodValue() <= 0)
	{
		// ���ﱻɱ
		MonsterLogic::GetInstance()->HandleMonsterBeKilled(pMonster,player);
	}
}

/************************************************************************
*  ��ұ�����
************************************************************************/
void PlayerLogic::HandlePlayerBeAttack(Player* player,Monster* pMonster)
{
	// ���Ѫ���ı�
	HandlePlayerBloodChange(player,-pMonster->GetDamageValue());

	Game()->GetSkillManager()->ShowBloodDropAnimation(player,-pMonster->GetDamageValue());


	if (player->GetMsg() != CodeMsg::code_player_attack)
	{
		//m_pPlayer->Action(CodeMsg::code_player_beaten,m_pPlayer->GetDirection());
	}

	if (player->GetBloodValue() <= 0)
	{
		// ��ұ�������
		player->Action(CodeMsg::code_player_die,player->GetDirection());
	}
}

/************************************************************************
*  �������
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
*  ���Ѫ���ı�
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
*  ���ħ�����ı�
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
*  ��Ҿ���ֵ�ı�
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
*  ��Ҵ���
************************************************************************/
void PlayerLogic::PlayerProcess(Player* player,Monster* pMonster)
{
	// ����ܶ�
	if (player->GetMsg() == CodeMsg::code_player_run)
	{
		HandlePlayerRun(player);
	}

	Point playerPosition = player->getPosition();

	// ��ҹ���
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

	// ���ܹ���
	if (player->GetMsg() == CodeMsg::code_player_skillattack)
	{
		HandlePlayerSkillAttack(player,player->GetCurrentSkill());
		player->SetCurrentSkill(0);
	}
}
RPG_01_END