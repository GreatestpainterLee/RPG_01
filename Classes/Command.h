#ifndef _PRG_COMMAND_H_
#define _PRG_COMMAND_H_

#include "define.h"

/*
** �������
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
	Entity*			m_pEntity;													// ��������Ķ���
	int				m_nMessage;												// �¼�
	Entity*			m_pSender;
	Entity*			m_pReceiver;
private:
public:
	
};

RPG_01_END
#endif