#ifndef _PRG_COMMAND_H_
#define _PRG_COMMAND_H_

#include "define.h"

/*
** 命令基类
*/
RPG_01_BEGIN

class Entity;
class Command
{
public:
	Command()
	{
			m_pEntity = 0;
			m_nMessage = -1;
			m_pSender = 0;
			m_pReceiver = 0;
	}

	virtual ~Command()
	{
	}

	/*void									SetEntity(Entity* pEntity)
	{
		m_pEntity = pEntity;
	}

	Entity*								GetEntity()
	{
		return m_pEntity;
	}*/

	void									SetMsg(int nMessage){m_nMessage = nMessage;}
	int									GetMsg(){return m_nMessage;}

	Entity*								GetReceiver(){return m_pReceiver;}
	void									SetReceiver(Entity* pEntity){m_pReceiver = pEntity;}

	Entity*								GetSender(){return m_pSender;}
	void									SetSender(Entity* pEntity){m_pSender = pEntity;}
protected:
	Entity*			m_pEntity;													// 发送命令的对象
	int				m_nMessage;												// 事件
	Entity*			m_pSender;
	Entity*			m_pReceiver;
private:
public:
	
};

RPG_01_END
#endif