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

	// ��������ʱ�����Ч
	m_pUpgradeSkill = Skill::create();
	m_pUpgradeSkill->SetSkillID(SKILL_5_ID);

	// ������Ѫ��Ч
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
*  Ϊ������Q��W��E��R������idΪnSkillID�ļ���
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
*  ��ȡ���������ʱ�����Ч����
************************************************************************/
Skill* SkillManager::GetUpgradeAnimation()
{
	return m_pUpgradeSkill;
}

/************************************************************************
*  ��ȡ��ȡ��һ�Ѫ��ʱ�����Ч
************************************************************************/
Skill* SkillManager::GetBloodReturnAnimation()
{
	return m_pBloodReturnSkill;
}

/************************************************************************
*  ��ȡ�����ŵĶ���
************************************************************************/
Skill* SkillManager::GetPortalAnimation()
{
	return m_pPortalAnimation;
}

/************************************************************************
*  ��ʾ������
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
*  ��ʾ��ҵ�Ѫ����Ч
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

