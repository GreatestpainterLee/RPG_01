#ifndef _SKILL_COMMAND_H_
#define _SKILL_COMMAND_H_


#include <cocos2d.h>
#include "define.h"
#include "Command.h"

USING_NS_CC;

RPG_01_BEGIN
	/*
	** 怪物命令类
	** 用于给怪物发送各种命令
	*/
class SkillCommand:public Command
{
public:
	SkillCommand(){}
	~SkillCommand(){}
	PROPERTY_INIT(int,SkillID,m_nSkillID);
protected:
private:
	int			m_nSkillID;										// 技能ID
};
RPG_01_END
#endif // !_SKILL_COMMAND_H_
