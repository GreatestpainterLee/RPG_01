#ifndef _PLAER_H_
#define _PLAER_H_

#include "define.h"

#include "Entity.h"
#include "PlayerAction.h"
#include "Skill.h"

RPG_01_BEGIN

/*
** 玩家类
*/
class Skill;
typedef Skill* PSkill;
class Player:public Entity
{
public:

	virtual bool init();

	CREATE_FUNC(Player);

	Player();

	~Player();

	void		Action(int action_type,int direction);												// 玩家动作

	void		AdjustPosition();																			// 调整位置

	void		Upgrade();																					// 玩家升级

	PROPERTY_INIT(float,Speed,m_fSpeed);													// 
	PROPERTY_INIT(Point,DestPoint,m_DestPoint);
	PROPERTY_INIT(float,MaxBloodValue,m_fMaxBloodValue);
	PROPERTY_INIT(float,MaxMagicValue,m_fMaxMagicValue);
	PROPERTY_INIT(float,MaxEmpiricalValue,m_fMaxEmpiricalValue);
	PROPERTY_INIT(int,Level,m_nLevel);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);
	PROPERTY_INIT(string,PlayerName,m_strPlayerName);
	PROPERTY_INIT(string,RoleName,m_strRoleName);
	PROPERTY_INIT(string,Password,m_strPassword);

	void		SetBloodValue(float v);
	float		GetBloodValue();

	void		SetMagicValue(float v);
	float		GetMagicValue();

	void		SetEmpiricalValue(float v);
	float		GetEmpiricalValue();

	void		SetDirection(int v);
	int		GetDirection();

	void		SetMsg(int type);
	int		GetMsg();

	int		GetMaxLevel();

	Skill*		GetSkill_Q();
	Skill*		GetSkill_W();
	Skill*		GetSkill_E();
	Skill*		GetSkill_R();

	void		SetCurrentSkill(Skill* pSkill);
	void		SetCurrentSkill(int nSkillID);
	Skill*		GetCurrentSkill();

	void		ShowBloodReturnAnimation();

private:
	string				m_strRoleName;									// 英雄名称
	string				m_strPlayerName;
	string				m_strPassword;

	float					m_fSpeed;											// 速度：随着等级提高，相应的值也会增加

	int					m_nDirection;										// 移动或跑动的方向
	Point				m_DestPoint;										// 移动时的目的地
	int					m_nMessage;									// 动作类型

	int					m_nPreDirection;									// 前一个移动的方向
	int					m_nPreMessage;								// 前一个动作类型

	float					m_fBloodValue;										// 当前血量：随着等级提高，相应的值也会增加
	float					m_fMaxBloodValue;

	float					m_fMagicValue;									// 当前魔法量：随着等级提高，相应的值也会增加
	float					m_fMaxMagicValue;

	float					m_fEmpiricalValue;								// 当前经验值：每次升级都会清空
	float					m_fMaxEmpiricalValue;							// 每一级的最大经验值，当经验值达到这个数量的时候就会升级：：随着等级提高，相应的值也会增加

	int					m_nLevel;												// 当前的等级：初始时候玩家的等级为1
	static const int	m_nMaxLevel = 16;								// 玩家的最大级数

	float					m_fDamageValue;									// 玩家的伤害值，攻击怪物时对怪物造成的伤害：随着等级提高，相应的值也会增加

	Skill*					m_pSkill_Q ;											// Q键的技能
	Skill*					m_pSkill_W;											// W键的技能
	Skill*					m_pSkill_E;											// E键的技能
	Skill*					m_pSkill_R;											// R键的技能

	Skill*					m_pCurrentSkill;									// 玩家当前需要施放的技能

	Skill*					m_pUpgradeSkill;									// 玩家升级的时候显示的特效

	Skill*					m_pBloodReturnSkill;							// 玩家吃到血瓶的时候显示特效
};

RPG_01_END
#endif