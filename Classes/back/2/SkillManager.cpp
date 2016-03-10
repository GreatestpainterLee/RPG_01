#include <cocos2d.h>
#include "SkillManager.h"
#include "scene/BaseScene.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "Skill.h"
#include "Player.h"
#include "Controller.h"
#include "scene/BaseScene.h"
#include "cocos/2d/CCLayer.h"
#include "FlowWord.h"
#include "Config.h"

USING_NS_CC;
RPG_01_BEGIN
SkillManager* SkillManager::m_pInstance = 0;

SkillManager::SkillManager()
{
	m_pUpgradeSkill = 0;
	m_pBloodReturnSkill = 0;
	m_pPortalAnimation = 0;

	// 创建升级时候的特效
	m_pUpgradeSkill = Skill::create();
	m_pUpgradeSkill->SetSkillID(SKILL_5_ID);

	// 创建回血特效
	m_pBloodReturnSkill = Skill::create();
	m_pBloodReturnSkill->SetSkillID(SKILL_BLOOD_RETURN_ID);

}

SkillManager* SkillManager::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new SkillManager;
	}

	return m_pInstance;
}

/************************************************************************
*  为按键（Q、W、E、R）创建id为nSkillID的技能
************************************************************************/
Skill* SkillManager::CreateSkill(int key_Q_W_E_R,int nSkillID)
{
	Skill* pSkill =  Skill::create();//Skill::create();
	pSkill->init();
	pSkill->SetSkillID(nSkillID);
	SetSkill(nSkillID,pSkill);
	return pSkill;
}

/************************************************************************
*  获取玩家升级的时候的特效动画
************************************************************************/
Skill* SkillManager::GetUpgradeAnimation()
{
	return m_pUpgradeSkill;
}

/************************************************************************
*  获取获取玩家回血的时候的特效
************************************************************************/
Skill* SkillManager::GetBloodReturnAnimation()
{
	return m_pBloodReturnSkill;
}

/************************************************************************
*  获取传送门的动画
************************************************************************/
Skill* SkillManager::GetPortalAnimation()
{
	return m_pPortalAnimation;
}

/************************************************************************
*  显示传送门
************************************************************************/
void SkillManager::ShowPortal(BaseScene* baseScene)
{
	if (baseScene == 0)
	{
		return;
	}

	m_pPortalAnimation = Skill::create();
	m_pPortalAnimation->SetSkillID(SKILL_PORTAL_ID);
	m_pPortalAnimation->setPosition(Point(Game()->GetConfig()->GetPortalPosition_X(),Game()->GetConfig()->GetPortalPosition_Y()));
	baseScene->GetEntityLayer()->addChild(m_pPortalAnimation);
	
	m_pPortalAnimation->Action(m_pPortalAnimation->GetSkillID());
}

/************************************************************************
*  显示玩家掉血的特效
************************************************************************/
void SkillManager::ShowBloodDropAnimation(Entity* pEntity,float v)
{
	char sz[16] = {0};
	if (v >= 0)
	{
		sprintf(sz,"+%0.1f",v);
	}
	else
	{
		sprintf(sz,"%0.1f",v);
	}

	auto pflowword = FlowWord::create();

	Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer()->addChild(pflowword);
	pflowword->setPosition(Point(pEntity->getPositionX(),pEntity->getPositionY()));

	pflowword->setScale(0.3);
	pflowword->showWord(sz,Point(50,150));

}
RPG_01_END

