#include "Monster.h"
#include "MonsterAction.h"
#include "MonsterCommand.h"
#include "./widget/ProgressView.h"
#include "Config.h"
#include "Controller.h"

RPG_01_BEGIN

Monster::Monster()
{
	
}

Monster::~Monster()
{

}

/************************************************************************
*  ��ʼ��
************************************************************************/
bool Monster::init()
{
	if (!Entity::init())
	{
		return false;
	}

	// ��ʼ�ȼ�Ϊ1
	m_nLevel = 1;

	// �������ͣ���ͨ��Ĭ�ϣ�
	m_nMonsterType = MONSTER_NORMAL;

	// �ٶ�
	m_fSpeed = Game()->GetConfig()->GetMonsterSpeed();

	// ����ֵ��������ֻ����֮����һ�õľ���ֵ
	m_fEmpiricalValue = Game()->GetConfig()->GetMonsterEmpiricalValue();

	// �˺�ֵ�����﹥����ҵ�ʱ������ܵ����˺�ֵ
	m_fDamageValue = Game()->GetConfig()->GetMonsterDamageValue();

	// ��ʼ�Ķ���
	m_nMessage = CodeMsg::code_unknown;

	// Ѫ��
	m_fBloodValue = 100.0;

	// Ŀ�ĵ�
	m_DestPoint = Point(0,0);

	m_pBloodProgress->setVisible(true);

	m_pBloodProgress->setPosition(6,60);

	// �������ú�������ЩһЩ���롣������
	Reset();

	return true;
}

/************************************************************************
*  �������֣����������ֲ����ᱻɾ����������������
*  �ȵ����ʵ�ʱ�������ã�Ȼ��������ʾ
************************************************************************/
void Monster::Reset()
{
	// ����Ϊ��Ч����
	m_nMessage = CodeMsg::code_unknown;
	//����Ѫ��
	m_fBloodValue = m_nLevel * 100.0;
	m_fMaxBloodValue = m_fBloodValue;
	// ����Ŀ�ĵ�
	m_DestPoint = Point(0,0);
	// ���ù����Ѫ��
	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);
	//���÷���
	SetDirection(left_direction);
	// �����Ƿ�ѡ�У���
	SetSelected(false);
}

/************************************************************************
*  ��������
************************************************************************/
void Monster::Upgrade()
{
	// ������߼�֮��Ͳ�����������
	if (m_nLevel >= m_nMaxLevel)
	{
		return;
	}

	// �ȼ�����
	++m_nLevel;

	// �ٶ�����
	m_fSpeed += Game()->GetConfig()->GetMonsterSpeedIncrement();

	// �����ľ���ֵ����
	m_fEmpiricalValue += Game()->GetConfig()->GetMonsterEmpiricalValueIncrement();

	// �˺�ֵ����
	m_fDamageValue += Game()->GetConfig()->GetMonsterDamageValueIncrement();

	// ��������
	m_nMessage = CodeMsg::code_unknown;

	// ����Ѫ��
	m_fBloodValue = m_nLevel * 100.0;

	m_fMaxBloodValue = m_fBloodValue;

	m_DestPoint = Point(0,0);

	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);

	SetDirection(left_direction);

	SetSelected(false);
}

/************************************************************************
*  ���ֶ���
************************************************************************/
void Monster::Action(int action_type,int direction)
{
	if (m_nMessage == action_type && m_nDirection == direction)
	{
		return;
	}

	// ���ö���������
	SetMsg(action_type);

	// ���ö����ķ���
	SetDirection(direction);

	// �������������ô�����͸����ﶯ���࣬���ﶯ����ʹ�ø����������Ӧ�Ķ���
	MonsterCommand cmd;

	// ���÷��������ʵ��
	//cmd.SetEntity(this);
	cmd.SetSender(this);
	cmd.SetReceiver(this);

	// ���ù����Ŀ�ĵ�
	cmd.SetDestPoint(m_DestPoint);

	// ���ù���ķ���
	cmd.SetDirection(m_nDirection);

	// ���ù��������
	cmd.SetMonsterName(m_strMonsterName);

	if (action_type == CodeMsg::code_monster_run)
	{
		cmd.SetMsg(CodeMsg::code_monster_run);
	}
	else
	if (action_type == CodeMsg::code_monster_static)
	{
		cmd.SetMsg(CodeMsg::code_monster_static);
	}
	else
	if (action_type == CodeMsg::code_monster_attack)
	{
		cmd.SetMsg(CodeMsg::code_monster_attack);
	}
	else
	if (action_type == CodeMsg::code_monster_dying)
	{
		cmd.SetMsg(CodeMsg::code_monster_dying);
	}
	else
	if (action_type == CodeMsg::code_monster_bellow)
	{
		cmd.SetMsg(CodeMsg::code_monster_bellow);
	}
	else
	if (action_type == CodeMsg::code_monster_bellow2)
	{
		cmd.SetMsg(CodeMsg::code_monster_bellow2);
	}
	else
	{
		return;
	}

	MonsterAction::GetInstance()->Execute(&cmd);
}

/************************************************************************
*  ����ֹͣ
************************************************************************/
void Monster::Stop()
{	
	MonsterCommand cmd;
	cmd.SetSender(this);
	cmd.SetReceiver(this);
	cmd.SetDestPoint(m_DestPoint);
	cmd.SetDirection(m_nDirection);

	cmd.SetMsg(CodeMsg::code_monster_static);
	
	MonsterAction::GetInstance()->Execute(&cmd);
}

/************************************************************************
*  ����λ�õ���
************************************************************************/
void Monster::AdjustPosition()
{
	// ��ȡ��ǰλ��
	Point currentPoint = getPosition();

	// ������Ӧ���������
	if (m_nDirection == right_up_direction)
	{
		currentPoint.x += GetSpeed();
		currentPoint.y += GetSpeed();
		if (currentPoint.x >= m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
		}

		if (currentPoint.y >= m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
		}
	}

	if (m_nDirection == right_direction)
	{
		currentPoint.x += GetSpeed();
		if (currentPoint.x >= m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
		}

	}

	if (m_nDirection == right_down_direction)
	{
		currentPoint.y -= GetSpeed();
		currentPoint.x += GetSpeed();
		if (currentPoint.y <= m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
		}

		if (currentPoint.x >= m_DestPoint.x)
		{
			currentPoint.x = m_DestPoint.x;
		}
	}

	if (m_nDirection == down_direction)
	{
		currentPoint.y -= GetSpeed();
		if (currentPoint.y <= m_DestPoint.y)
		{
			currentPoint.y = m_DestPoint.y;
		}
	}

	setPosition(currentPoint);
}

/************************************************************************
*  �жϹ����Ƿ���������ѡ��
************************************************************************/
bool Monster::IsSelected()
{
	if (m_pCircleLight->isVisible())
	{
		return true;
	}

	return false;
}

/************************************************************************
*  ��ȡѪ��
************************************************************************/
float Monster::GetBloodValue()
{
	return m_fBloodValue;
}

/************************************************************************
*  ��ȡѪ��
************************************************************************/
float Monster::GetMaxBloodValue()
{
	return m_fMaxBloodValue;
}

/************************************************************************
*  ����Ѫ��
************************************************************************/
void Monster::SetBloodValue(float v)
{
	m_fBloodValue = v;

	if (v <= 0)
	{
		m_fBloodValue = 0;
	}

	if (v >= m_fMaxBloodValue)
	{
		m_fBloodValue =m_fMaxBloodValue;
	}

	// ����Ѫ��������
	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);

	// ���Ѫ��������ô����
	if (m_fBloodValue <= 0)
	{
		Action(CodeMsg::code_monster_dying,m_nDirection);
	}
}

/************************************************************************
*  ��ȡ��������
************************************************************************/
int Monster::GetMonsterType()
{
	return m_nMonsterType;
}

/************************************************************************
*  ���ù�������
************************************************************************/
void	Monster::SetMonsterType(int type)
{
	m_nMonsterType = type;

	// �������ͨ������ֱ�ӷ���
	if (m_nMonsterType == MONSTER_NORMAL)
	{
		return;
	}

	// �����Boss����ô��Ҫ��������Ѫ�����˺�ֵ���еȼ�
	if (m_nMonsterType == MONSTER_BOSS)
	{
		m_nLevel = 64;
		m_fBloodValue = 6400;
		m_fMaxBloodValue = 6400;
		m_fDamageValue = 2;
		//m_pBloodProgress->SetCurrentProgress(10240);
		m_pBloodProgress->setScale(0.3);
		m_pCircleLight->setScale(2);
		SetScope(256,256);
	}
}

/************************************************************************
*  ���÷���
************************************************************************/
void	Monster::SetDirection(int v)																	
{
	m_nPreDirection = m_nDirection;
	m_nDirection = v;
}														

/************************************************************************
*  ��÷���
************************************************************************/
int	Monster::GetDirection()																		
{
	return m_nDirection;
}

/************************************************************************
*  ���ö���
************************************************************************/
void	Monster::SetMsg(int type)														
{
	m_nPreMessage = m_nMessage;
	m_nMessage = type;
}

/************************************************************************
*  ��ö���
************************************************************************/
int	Monster::GetMsg()																	
{
	return m_nMessage;
}
RPG_01_END