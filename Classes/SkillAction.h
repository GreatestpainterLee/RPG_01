#ifndef _SKILL_ACTION_H_
#define _SKILL_ACTION_H_

#include <cocos2d.h>
#include "define.h"
#include "SkillCommand.h"

USING_NS_CC;
RPG_01_BEGIN

/*
** ���ܵĶ�����
*/
class SkillAction
{
public:
	
	static SkillAction*							GetInstance();

	~SkillAction();

	virtual void									Execute(Command* pCmd);
	void												ActionEndCallback();

	Animation*									LoadSkillAnimation1();							// ����1
	Animation*									LoadSkillAnimation2();							// ����2
	Animation*									LoadSkillAnimation3();							// ����3
	Animation*									LoadSkillAnimation4();							// ����4

	Animation*									LoadSkillAnimation5();							// ����5
	Animation*									LoadSkillAnimation6();							// ����6
	Animation*									LoadSkillAnimation7();							// ����7
	Animation*									LoadSkillAnimation8();							// ����8

	Animation*									LoadSkillPortal();

	Animation*									LoadSkillBloodReturn();					

private:
	SkillAction();

	static SkillAction*				m_pInstance;

	string								m_strSkillActionConfigFile;

	SkillCommand					m_SkillCommand;

	Animation*						m_pSkillAnimation1;
	Animation*						m_pSkillAnimation2;
	Animation*						m_pSkillAnimation3;
	Animation*						m_pSkillAnimation4;

	Animation*						m_pSkillAnimation5;
	Animation*						m_pSkillAnimation6;
	Animation*						m_pSkillAnimation7;
	Animation*						m_pSkillAnimation8;

	Animation*						m_pSkillPortal;

	Animation*						m_pSkillBloodReturn;

};
RPG_01_END
#endif // !_SKILL_ACTION_H_
