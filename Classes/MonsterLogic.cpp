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
*  ������й���
************************************************************************/
void MonsterLogic::HandleMonsterAttack(Monster* pMonster,Player* player)
{
	// ȡ����ҵ�����
	Point playerPoint = player->getPosition();

	// ȡ�ù������ػ��߹�����Χ
	Rect monsterScope = pMonster->GetScope();

	// �ж�����Ƿ��ڹ�������֮��
	if (!Game()->GetPathManager()->IsInRect(monsterScope,playerPoint))
	{
		return;
	}
	// ��ұ�����
	PlayerLogic::GetInstance()->HandlePlayerBeAttack(player,pMonster);
}


/************************************************************************
*  ���ﱻɱ��
************************************************************************/
void MonsterLogic::HandleMonsterBeKilled(Monster* pMonster,Player* player)
{
	if (pMonster == 0)
	{
		return;
	}

	// ÿɱ��һֻ�����Ҿ����Ӿ���ֵ
	PlayerLogic::GetInstance()->HandlePlayerEmpiricalChange(player,pMonster->GetEmpiricalValue());

	// ���ﱻɱ��֮����Ҿ�ͣ��
	player->Action(CodeMsg::code_player_static,player->GetDirection());

	if (player->GetEmpiricalValue() >= player->GetMaxEmpiricalValue())
	{
		// ���������
		PlayerLogic::GetInstance()->HandlePlayerUpgrade(player);
	}
}

/************************************************************************
*  ����Ѫ���ı�
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