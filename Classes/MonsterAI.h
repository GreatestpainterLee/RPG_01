#ifndef _MONSTER_AI_H_
#define _MONSTER_AI_H_

#include "define.h"

RPG_01_BEGIN
/*
** 怪物AI类
*/
class Monster;
class Player;
class MonsterAI
{
public:
	static MonsterAI*		GetInstance();

	void							Process(float f);																// 主逻辑处理
private:
	MonsterAI(){}
	static MonsterAI*		m_pInstance;
	int							GetNextAction(float f);													// 下一个动作
	int							GetNextDirection(int dir);												// 下一个方向
	void							MonsterAutoRun(Monster* pMonster,float fDelt);		// 怪物自己移动
};

RPG_01_END

#endif // !_MONSTER_AI_H_
