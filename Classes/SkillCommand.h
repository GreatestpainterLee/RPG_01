#ifndef _SKILL_COMMAND_H_
#define _SKILL_COMMAND_H_


#include <cocos2d.h>
#include "define.h"
#include "Command.h"

USING_NS_CC;

RPG_01_BEGIN
	/*
	** ����������
	** ���ڸ����﷢�͸�������
	*/
class SkillCommand:public Command
{
public:
	SkillCommand(){}
	~SkillCommand(){}
	PROPERTY_INIT(int,SkillID,m_nSkillID);
protected:
private:
	int			m_nSkillID;										// ����ID
};
RPG_01_END
#endif // !_SKILL_COMMAND_H_
