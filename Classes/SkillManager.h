#ifndef _SKILL_MANAGER_H_
#define _SKILL_MANAGER_H_

#include "define.h"
#include <cocos2d.h>
#include "Skill.h"
USING_NS_CC;


RPG_01_BEGIN
class Player;
class Skill;
class BaseScene;

/*
** 技能和特效管理器
*/
class SkillManager
{
public:
	static SkillManager*						GetInstance();

	void		ShowPortal(BaseScene* baseScene);									// 显示传送门

	Skill*		CreateSkill(int key_Q_W_E_R,int nSkillID);							// 创建技能

	Skill*		GetSkill(int nSkillID)															// 获取技能
	{
		map<int,Skill*>::iterator it;
		it = m_SkillMap.find(nSkillID) ;
		if (it != m_SkillMap.end())
		{
			return it->second;
		}

		return 0;
	}																					

	void		SetSkill(int nSkillID,Skill* pSkill)											// 设置技能，并加入到技能映射表中
	{
		map<int,Skill*>::iterator it;
		pSkill->SetSkillID(nSkillID);
		it = m_SkillMap.find(nSkillID) ;
		if (it != m_SkillMap.end())
		{
			m_SkillMap.erase(it);
		}

		m_SkillMap.insert(make_pair(nSkillID,pSkill));
	}									

	Skill*		GetUpgradeAnimation();													// 玩家升级时的特效

	Skill*		GetBloodReturnAnimation();												// 玩家回血时显示的特效

	Skill*		GetPortalAnimation();														// 传送门

	void		ShowBloodDropAnimation(Entity* pEntity,float v);			// 显示掉血特效

private:
	SkillManager();
	static SkillManager*			m_pInstance;
	Skill*									m_pUpgradeSkill;									// 升级的时候玩家显示的特效
	Skill*									m_pBloodReturnSkill;							// 回血特效
	Skill*									m_pPortalAnimation;							// 传送门特效

	map<int,Skill*>				m_SkillMap;											// 技能ID与技能的映射
};
RPG_01_END

#endif // !_TREASURE_MANAGER_H
