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
#include "PlayerLogic.h"
#include "PlayerManager.h"
RPG_01_BEGIN

MonsterLogic* MonsterLogic::m_pInstance = 0;

MonsterLogic* MonsterLogic::GetInstance()
{
	if(0 == m_pInstance)
	{
		m_pInstance = new MonsterLogic;
	}

	return m_pInstance;
}

MonsterLogic::MonsterLogic()
{
}


/************************************************************************
*  怪物进行攻击
************************************************************************/
void MonsterLogic::HandleMonsterAttack(Monster* pMonster,Player* player)
{
	// 取得玩家的坐标
	Point playerPoint = player->getPosition();

	// 取得怪物的领地或者攻击范围
	Rect monsterScope = pMonster->GetScope();

	// 判断玩家是否在怪物的领地之内
	if (!Game()->GetPathManager()->IsInRect(monsterScope,playerPoint))
	{
		return;
	}
	// 玩家被攻击
	PlayerLogic::GetInstance()->HandlePlayerBeAttack(player,pMonster);
}


/************************************************************************
*  怪物被杀死
************************************************************************/
void MonsterLogic::HandleMonsterBeKilled(Monster* pMonster,Player* player)
{
	if (pMonster == 0)
	{
		return;
	}

	// 每杀死一只怪物，玩家就增加经验值
	PlayerLogic::GetInstance()->HandlePlayerEmpiricalChange(player,pMonster->GetEmpiricalValue());

	// 怪物被杀死之后玩家就停手
	player->Action(CodeMsg::code_player_static,player->GetDirection());

	if (player->GetEmpiricalValue() >= player->GetMaxEmpiricalValue())
	{
		// 玩家升级了
		PlayerLogic::GetInstance()->HandlePlayerUpgrade(player);
	}
}

/************************************************************************
*  怪物血量改变
************************************************************************/
void MonsterLogic::HandleMonsterBloodChange(Monster* pMonster,float fChangeValue)
{
	if (pMonster == 0)
	{
		return ;
	}

	pMonster->SetBloodValue(pMonster->GetBloodValue() + fChangeValue);
	Game()->GetSceneManager()->SetMonsterBloodProgress(100 * pMonster->GetBloodValue() / pMonster->GetMaxBloodValue());
}
RPG_01_END