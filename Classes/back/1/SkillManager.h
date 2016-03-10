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
** ���ܺ���Ч������
*/
class SkillManager
{
public:
	static SkillManager*						GetInstance();

	void		ShowPortal(BaseScene* baseScene);									// ��ʾ������

	Skill*		CreateSkill(int key_Q_W_E_R,int nSkillID);							// ��������

	Skill*		GetSkill(int nSkillID)															// ��ȡ����
	{
		map<int,Skill*>::iterator it;
		it = m_SkillMap.find(nSkillID) ;
		if (it != m_SkillMap.end())
		{
			return it->second;
		}

		return 0;
	}																					

	void		SetSkill(int nSkillID,Skill* pSkill)											// ���ü��ܣ������뵽����ӳ�����
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

	Skill*		GetUpgradeAnimation();													// �������ʱ����Ч

	Skill*		GetBloodReturnAnimation();												// ��һ�Ѫʱ��ʾ����Ч

	Skill*		GetPortalAnimation();														// ������

	void		ShowBloodDropAnimation(Entity* pEntity,float v);			// ��ʾ��Ѫ��Ч

private:
	SkillManager();
	static SkillManager*			m_pInstance;
	Skill*									m_pUpgradeSkill;									// ������ʱ�������ʾ����Ч
	Skill*									m_pBloodReturnSkill;							// ��Ѫ��Ч
	Skill*									m_pPortalAnimation;							// ��������Ч

	map<int,Skill*>				m_SkillMap;											// ����ID�뼼�ܵ�ӳ��
};
RPG_01_END

#endif // !_TREASURE_MANAGER_H
