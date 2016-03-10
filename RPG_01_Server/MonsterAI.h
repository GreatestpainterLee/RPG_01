#ifndef _MONSTER_AI_H_
#define _MONSTER_AI_H_

#include "define.h"

/*
** ����AI��
*/
class Monster;
class Player;
class MonsterAI
{
public:
	static MonsterAI*		GetInstance();

	void							Process(float f);																// ���߼�����
private:
	MonsterAI(){}
	static MonsterAI*		m_pInstance;
	int							GetNextAction(float f);													// ��һ������
	int							GetNextDirection(int dir);												// ��һ������
	void							MonsterAutoRun(Monster* pMonster,float fDelt);		// �����Լ��ƶ�
};


#endif // !_MONSTER_AI_H_