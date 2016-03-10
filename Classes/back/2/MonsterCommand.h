#ifndef _MONSTER_COMMAND_H_
#define _MONSTER_COMMAND_H_

#include <cocos2d.h>
#include "define.h"
#include "Command.h"

USING_NS_CC;

RPG_01_BEGIN
/*
** 怪物命令类
** 用于给怪物发送各种命令
*/
class MonsterCommand:public Command
{
public:
	PROPERTY_INIT(int,Msg,m_nMessage);
	PROPERTY_INIT(Point,DestPoint,m_DestPoint);
	PROPERTY_INIT(int,Direction,m_nDirection);
	PROPERTY_INIT(string,MonsterName,m_strMonsterName);
protected:
private:
	int			m_nMessage;														// 动作类型
	Point		m_DestPoint;															// 目的地
	int			m_nDirection;															// 方向
	string		m_strMonsterName;													// 怪物的名字

};
RPG_01_END
#endif // !_MONSTER_COMMAND_H_
