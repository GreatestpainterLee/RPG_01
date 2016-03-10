#include "Player.h"
#include "PlayerAction.h"
#include "PlayerCommand.h"
#include "MonsterManager.h"
#include "Monster.h"
#include "SceneManager.h"
#include "widget/ProgressView.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Controller.h"
#include "Config.h"

RPG_01_BEGIN

Player::Player()
{	
	
}


Player::~Player()
{

}

/************************************************************************
*  初始化函数
************************************************************************/
bool Player::init()
{
	if (!Entity::init())
	{
		return false;
	}

	m_nLevel = 1;
	m_fSpeed = Game()->GetConfig()->GetPlayerSpeed();
	m_fDamageValue = Game()->GetConfig()->GetPlayerDamageValue();

	m_fMagicValue = m_nLevel * 100;
	m_fMaxMagicValue = m_fMagicValue;

	m_fBloodValue = m_nLevel * 100;
	m_fMaxBloodValue = m_fBloodValue;

	m_fEmpiricalValue = 0;
	m_fMaxEmpiricalValue = m_nLevel * 100;

	m_nMessage = CodeMsg::code_unknown;

	SetRoleName(Game()->GetConfig()->GetRoleName());


	m_pBloodProgress->SetCurrentProgress(1.0);

	PlayerAction::GetInstance()->SetRoleName(m_strRoleName);
	SkillManager * pM = Game()->GetSkillManager();
	m_pSkill_Q = Game()->GetSkillManager()->CreateSkill(SKILL_Q,SKILL_6_ID);
	
	m_pSkill_W = Game()->GetSkillManager()->CreateSkill(SKILL_W,SKILL_2_ID);
	m_pSkill_E = Game()->GetSkillManager()->CreateSkill(SKILL_E,SKILL_3_ID);
	m_pSkill_R = Game()->GetSkillManager()->CreateSkill(SKILL_R,SKILL_4_ID);

	m_pUpgradeSkill = Game()->GetSkillManager()->GetUpgradeAnimation();
	m_pBloodReturnSkill = Game()->GetSkillManager()->GetBloodReturnAnimation();

	addChild(m_pUpgradeSkill);
	addChild(m_pBloodReturnSkill);

	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);

	m_pBloodProgress->setVisible(true);

	return true;
}

/************************************************************************
*  升级
************************************************************************/
void Player::Upgrade()
{
	if (m_nLevel >= m_nMaxLevel)
	{
		return;
	}

	m_pUpgradeSkill->Action(m_pUpgradeSkill->GetSkillID());

	++m_nLevel;

	m_fMagicValue = m_nLevel * 100;
	m_fMaxMagicValue = m_fMagicValue;

	m_fBloodValue = m_nLevel * 100;
	m_fMaxBloodValue = m_fBloodValue;

	m_fEmpiricalValue = 0;
	m_fMaxEmpiricalValue = m_nLevel * 100;

	m_fSpeed  += Game()->GetConfig()->GetPlayerSpeedIncrement();
	m_fDamageValue += Game()->GetConfig()->GetPlayerDamageValueIncrement();

	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);

	if (m_nLevel % 4 == 1)
	{
		m_pSkill_Q->Upgrade();
	}

	if (m_nLevel % 4 == 2)
	{
		m_pSkill_W->Upgrade();
	}

	if (m_nLevel % 4 == 3)
	{
		m_pSkill_E->Upgrade();
	}

	if (m_nLevel % 4 == 0)
	{
		m_pSkill_R->Upgrade();
	}
}

/************************************************************************
*  显示回血特效
************************************************************************/
void Player::ShowBloodReturnAnimation()
{
	m_pBloodReturnSkill->Action(m_pBloodReturnSkill->GetSkillID());
}

/************************************************************************
*  设置血量
************************************************************************/
void Player::SetBloodValue(float v)
{

	m_fBloodValue = v;

	if (m_fBloodValue < 0)
	{
		m_fBloodValue = 0;
	}

	if (m_fBloodValue > m_fMaxBloodValue)
	{
		m_fBloodValue = m_fMaxBloodValue;
	}

	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxMagicValue);
}

/************************************************************************
*  获得血量
************************************************************************/
float Player::GetBloodValue()
{
	return m_fBloodValue;
}

void Player::SetMagicValue(float v)
{
	m_fMagicValue = v;
	if (m_fMagicValue < 0)
	{
		m_fMagicValue = 0;
	}

	if (m_fMagicValue > m_fMaxMagicValue)
	{
		m_fMagicValue = m_fMaxMagicValue;
	}

}

/************************************************************************
*  获得魔法量
************************************************************************/
float Player::GetMagicValue()
{
	return m_fMagicValue;
}

/************************************************************************
*  设置经验值
************************************************************************/
void Player::SetEmpiricalValue(float v)
{
	m_fEmpiricalValue = v;
	if (m_fEmpiricalValue < 0)
	{
		m_fEmpiricalValue = 0;
	}

	if (m_fEmpiricalValue > m_fMaxEmpiricalValue)
	{
		m_fEmpiricalValue = m_fMaxEmpiricalValue;
	}

}

/************************************************************************
*  获得经验值
************************************************************************/
float Player::GetEmpiricalValue()
{
	return m_fEmpiricalValue;
}


void Player::Action(int action_type,int direction)
{
	if (m_nMessage == CodeMsg::code_player_die)
	{
		return;
	}

	if (m_nMessage == action_type && m_nDirection == direction)
	{
		return;
	}

	SetMsg(action_type);
	SetDirection(direction);

	PlayerCommand cmd;
	cmd.SetSender(this);
	cmd.SetReceiver(this);
	cmd.SetDestPoint(m_DestPoint);
	cmd.SetDirection(m_nDirection);

	if (action_type == CodeMsg::code_player_run)
	{
		cmd.SetMsg(CodeMsg::code_player_run);
	}

	if (action_type == CodeMsg::code_player_static)
	{
		cmd.SetMsg(CodeMsg::code_player_static);
	}

	if (action_type == CodeMsg::code_player_attack)
	{
		cmd.SetMsg(CodeMsg::code_player_attack);
	}

	if (action_type == CodeMsg::code_player_walk)
	{
		cmd.SetMsg(CodeMsg::code_player_walk);
	}

	if (action_type == CodeMsg::code_player_throwoff)
	{
		cmd.SetMsg(CodeMsg::code_player_throwoff);
	}

	if (action_type == CodeMsg::code_player_beaten)
	{
		cmd.SetMsg(CodeMsg::code_player_beaten);
	}

	if (action_type == CodeMsg::code_player_die)
	{
		cmd.SetMsg(CodeMsg::code_player_die);
	}


	if (action_type == CodeMsg::code_player_test)
	{
		cmd.SetMsg(CodeMsg::code_player_test);
	}

	PlayerAction::GetInstance()->Execute(&cmd);
}

void Player::AdjustPosition()
{
	Point currentPoint = getPosition();

	if (m_nDirection == right_up_direction)
	{
		currentPoint.x += sqrt(GetSpeed());
		if (currentPoint.x > m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
			Action(m_nMessage,up_direction);
		}

		currentPoint.y += sqrt(GetSpeed());
		if (currentPoint.y > m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
			Action(m_nMessage,right_direction);
		}

	}

	if (m_nDirection == right_direction)
	{
		currentPoint.x += GetSpeed();
		if (currentPoint.x > m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
		}

	}

	if (m_nDirection == right_down_direction)
	{
		currentPoint.x += sqrt(GetSpeed());
		if (currentPoint.x > m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
			Action(m_nMessage,down_direction);
		}

		currentPoint.y -= sqrt(GetSpeed());
		if (currentPoint.y < m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
			Action(m_nMessage,right_direction);
		}
	}

	if (m_nDirection == down_direction)
	{
		currentPoint.y -= GetSpeed();
		if (currentPoint.y < m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
		}
	}

	if (m_nDirection == left_down_direction)
	{
		currentPoint.x -= sqrt(GetSpeed());
		if (currentPoint.x < m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
			Action(m_nMessage,down_direction);
		}

		currentPoint.y -= sqrt(GetSpeed());
		if (currentPoint.y < m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
			Action(m_nMessage,left_direction);
		}
	}

	if (m_nDirection == left_direction)
	{
		currentPoint.x -= GetSpeed();
		if (currentPoint.x < m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
		}

	}

	if (m_nDirection == left_up_direction)
	{
		currentPoint.x -= sqrt(GetSpeed());
		if (currentPoint.x < m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
			Action(m_nMessage,up_direction);
		}

		currentPoint.y += sqrt(GetSpeed());
		if (currentPoint.y > m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
			Action(m_nMessage,left_direction);
		}
	}

	if (m_nDirection == up_direction)
	{
		currentPoint.y += GetSpeed();
		if (currentPoint.y > m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
		}
	}
	setPosition(currentPoint);
}


void Player::SetDirection(int v)
{
	m_nPreDirection = m_nDirection;
	m_nDirection = v;
}

int Player::GetDirection()
{
	return m_nDirection;
}

void Player::SetMsg(int type)
{
	m_nPreMessage = m_nMessage;
	m_nMessage = type;
}

int Player::GetMsg()
{
	return m_nMessage;
}

int Player::GetMaxLevel()
{
	return m_nMaxLevel;
}

Skill* Player::GetSkill_Q()
{
	return m_pSkill_Q;
}

Skill* Player::GetSkill_W()
{
	return m_pSkill_W;
}

Skill* Player::GetSkill_E()
{
	return m_pSkill_E;
}

Skill* Player::GetSkill_R()
{
	return m_pSkill_R;
}

void Player::SetCurrentSkill(Skill* pSkill)
{
	m_pCurrentSkill = 0;
	if (pSkill != m_pSkill_Q && pSkill != m_pSkill_W && pSkill != m_pSkill_E && pSkill != m_pSkill_R)
	{
		return;
	}
	m_pCurrentSkill = pSkill;
}

void Player::SetCurrentSkill(int nSkillID)
{
	m_pCurrentSkill = 0;

	if (nSkillID == m_pSkill_Q->GetSkillID())
	{
		m_pCurrentSkill = m_pSkill_Q;
	}
	if (nSkillID == m_pSkill_W->GetSkillID())
	{
		m_pCurrentSkill = m_pSkill_W;
	}
	if (nSkillID == m_pSkill_E->GetSkillID())
	{
		m_pCurrentSkill = m_pSkill_E;
	}
	if (nSkillID == m_pSkill_R->GetSkillID())
	{
		m_pCurrentSkill = m_pSkill_R;
	}
	
}

Skill* Player::GetCurrentSkill()
{
	return m_pCurrentSkill;
}


RPG_01_END