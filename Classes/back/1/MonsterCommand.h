#ifndef _MONSTER_COMMAND_H_
#define _MONSTER_COMMAND_H_

#include <cocos2d.h>
#include "define.h"
#include "Command.h"

USING_NS_CC;

RPG_01_BEGIN
/*
** ����������
** ���ڸ����﷢�͸�������
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
	int			m_nMessage;														// ��������
	Point		m_DestPoint;															// Ŀ�ĵ�
	int			m_nDirection;															// ����
	string		m_strMonsterName;													// ���������

};
RPG_01_END
#endif // !_MONSTER_COMMAND_H_
