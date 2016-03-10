#include "Skill.h"
#include "SkillCommand.h"
#include "SkillAction.h"
#include "widget/ProgressView.h"

RPG_01_BEGIN
Skill::Skill()
{
	
}

Skill::~Skill()
{

}

/************************************************************************
*  初始化
************************************************************************/
bool Skill::init()
{
	if (!Entity::init())
	{
		return false;
	}
	SetDamageValue(10);
	m_pBloodProgress->setVisible(false);
	SetScope(256,256);
	m_nLevel = 0;
	m_fConsumeMagic = 0;
	Upgrade();
	return true;
}

/************************************************************************
*  升级
************************************************************************/
void Skill::Upgrade()
{
	if (m_nLevel >= m_nMaxLevel)
	{
		return;
	}

	++m_nLevel;
	m_fConsumeMagic += 5;
	m_fDamageValue    += 10;
}

/************************************************************************
*  技能的动作（动画）
************************************************************************/
void Skill::Action(int nSkillID)
{
	SkillCommand cmd;
	cmd.SetSender(this);
	cmd.SetReceiver(this);
	cmd.SetSkillID(nSkillID);
	SkillAction::GetInstance()->Execute(&cmd);
}

RPG_01_END