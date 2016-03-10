#ifndef _SKILL_H_
#define _SKILL_H_

#include "define.h"
#include "Entity.h"

RPG_01_BEGIN
/*
** 技能类（或者特效类）：
*/
class Skill:public Entity
{
public:

	X_CREATE_FUNC(Skill);
	Skill();
	~Skill();

	bool								init();

	PROPERTY_INIT(int,SkillID,m_nSkillID);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);

	void								Action(int nSkillID);									// 技能的施放动画效果
	void								Upgrade();												// 技能升级（升级会使伤害值更高，耗墨量更大）

	PROPERTY_INIT(float,ConsumeMagic,m_fDamageValue);
private:
	int								m_nSkillID;												// 技能的ID，唯一的标志一种技能
	float								m_fDamageValue;										// 施放该技能，能给怪物造成多少伤害
	float								m_fConsumeMagic;									// 施放一次技能要消耗的魔法量
	int								m_nLevel;													// 技能的当前等级
	static const int				m_nMaxLevel = 4;									// 技能的最大等级
};
RPG_01_END

#endif