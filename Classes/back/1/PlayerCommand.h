#ifndef _PLAYER_COMMAND_H_
#define _PLAYER_COMMAND_H_

#include <cocos2d.h>
#include "define.h"
#include "Command.h"

USING_NS_CC;

/*
** 玩家命令类
** 用于发送各种命令来控制玩家
*/
RPG_01_BEGIN
class PlayerCommand:public Command
{
public:
	PROPERTY_INIT(int,Msg,m_nMessage);
	PROPERTY_INIT(Point,DestPoint,m_DestPoint);
	PROPERTY_INIT(int,Direction,m_nDirection);
	PROPERTY_INIT(float,BloodfChangeValue,m_fBloodfChangeValue);
	PROPERTY_INIT(float,MagicfChangeValue,m_fMagicfChangeValue);
	PROPERTY_INIT(float,EmpiricalChangeValue,m_fEmpiricalChangeValue);

protected:
private:
	int			m_nMessage;
	Point		m_DestPoint;
	int			m_nDirection;

	float			m_fBloodfChangeValue;
	float			m_fMagicfChangeValue;
	float			m_fEmpiricalChangeValue;

};

RPG_01_END
#endif