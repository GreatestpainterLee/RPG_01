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
*  初始化
************************************************************************/
bool Monster::init()
{
	if (!Entity::init())
	{
		return false;
	}

	// 初始等级为1
	m_nLevel = 1;

	// 怪物类型：普通（默认）
	m_nMonsterType = MONSTER_NORMAL;

	// 速度
	m_fSpeed = Game()->GetConfig()->GetMonsterSpeed();

	// 经验值：打死这只怪物之后玩家获得的经验值
	m_fEmpiricalValue = Game()->GetConfig()->GetMonsterEmpiricalValue();

	// 伤害值：怪物攻击玩家的时候玩家受到的伤害值
	m_fDamageValue = Game()->GetConfig()->GetMonsterDamageValue();

	// 起始的动作
	m_nMessage = CodeMsg::code_unknown;

	// 血量
	m_fBloodValue = 100.0;

	// 目的地
	m_DestPoint = Point(0,0);

	m_pBloodProgress->setVisible(true);

	m_pBloodProgress->setPosition(6,60);

	// 调用重置函数（少些一些代码。。。）
	Reset();

	return true;
}

/************************************************************************
*  重置妖怪：死亡的妖怪并不会被删除，而是隐藏起来
*  等到合适的时候在重置，然后重新显示
************************************************************************/
void Monster::Reset()
{
	// 动作为无效动作
	m_nMessage = CodeMsg::code_unknown;
	//设置血量
	m_fBloodValue = m_nLevel * 100.0;
	m_fMaxBloodValue = m_fBloodValue;
	// 设置目的地
	m_DestPoint = Point(0,0);
	// 设置怪物的血条
	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);
	//设置方向
	SetDirection(left_direction);
	// 怪物是否被选中（否）
	SetSelected(false);
}

/************************************************************************
*  怪物升级
************************************************************************/
void Monster::Upgrade()
{
	// 到达最高级之后就不能再升级了
	if (m_nLevel >= m_nMaxLevel)
	{
		return;
	}

	// 等级增加
	++m_nLevel;

	// 速度增加
	m_fSpeed += Game()->GetConfig()->GetMonsterSpeedIncrement();

	// 包含的经验值增加
	m_fEmpiricalValue += Game()->GetConfig()->GetMonsterEmpiricalValueIncrement();

	// 伤害值增加
	m_fDamageValue += Game()->GetConfig()->GetMonsterDamageValueIncrement();

	// 动作类型
	m_nMessage = CodeMsg::code_unknown;

	// 设置血量
	m_fBloodValue = m_nLevel * 100.0;

	m_fMaxBloodValue = m_fBloodValue;

	m_DestPoint = Point(0,0);

	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);

	SetDirection(left_direction);

	SetSelected(false);
}

/************************************************************************
*  妖怪动作
************************************************************************/
void Monster::Action(int action_type,int direction)
{
	if (m_nMessage == action_type && m_nDirection == direction)
	{
		return;
	}

	// 设置动作的类型
	SetMsg(action_type);

	// 设置动作的方向
	SetDirection(direction);

	// 怪物的命令：怪物用此命令发送给怪物动作类，怪物动作类使用该命令调用相应的动作
	MonsterCommand cmd;

	// 设置发送命令的实体
	//cmd.SetEntity(this);
	cmd.SetSender(this);
	cmd.SetReceiver(this);

	// 设置怪物的目的地
	cmd.SetDestPoint(m_DestPoint);

	// 设置怪物的方向
	cmd.SetDirection(m_nDirection);

	// 设置怪物的名称
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
*  动作停止
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
*  怪物位置调整
************************************************************************/
void Monster::AdjustPosition()
{
	// 获取当前位置
	Point currentPoint = getPosition();

	// 进行相应的坐标调整
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
*  判断怪物是否被玩家用鼠标选中
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
*  获取血量
************************************************************************/
float Monster::GetBloodValue()
{
	return m_fBloodValue;
}

/************************************************************************
*  获取血量
************************************************************************/
float Monster::GetMaxBloodValue()
{
	return m_fMaxBloodValue;
}

/************************************************************************
*  设置血量
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

	// 设置血量进度条
	m_pBloodProgress->SetCurrentProgress(m_fBloodValue/m_fMaxBloodValue);

	// 如果血量过低那么死亡
	if (m_fBloodValue <= 0)
	{
		Action(CodeMsg::code_monster_dying,m_nDirection);
	}
}

/************************************************************************
*  获取怪物类型
************************************************************************/
int Monster::GetMonsterType()
{
	return m_nMonsterType;
}

/************************************************************************
*  设置怪物类型
************************************************************************/
void	Monster::SetMonsterType(int type)
{
	m_nMonsterType = type;

	// 如果是普通怪物则直接返回
	if (m_nMonsterType == MONSTER_NORMAL)
	{
		return;
	}

	// 如果是Boss，那么需要重新设置血量和伤害值还有等级
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
*  设置方向
************************************************************************/
void	Monster::SetDirection(int v)																	
{
	m_nPreDirection = m_nDirection;
	m_nDirection = v;
}														

/************************************************************************
*  获得方向
************************************************************************/
int	Monster::GetDirection()																		
{
	return m_nDirection;
}

/************************************************************************
*  设置动作
************************************************************************/
void	Monster::SetMsg(int type)														
{
	m_nPreMessage = m_nMessage;
	m_nMessage = type;
}

/************************************************************************
*  获得动作
************************************************************************/
int	Monster::GetMsg()																	
{
	return m_nMessage;
}
RPG_01_END