#ifndef _MONSTER_ACTION_MANGER_H_
#define _MONSTER_ACTION_MANGER_H_


#include <cocos2d.h>
#include "define.h"
#include "Command.h"
#include "MonsterCommand.h"

USING_NS_CC;

RPG_01_BEGIN
class Monster;

/*
** 怪物的动作类
*/
class MonsterAction
{
public:
	static MonsterAction*				GetInstance();

	virtual void								Execute(Command* pCmd);													// 执行怪物动作

private:
	MonsterAction();

	void											LoadStaticAnimation(string monsterName);							// 加载静止时候的动画

	void											LoadWalkAnimation(string monsterName);							// 加载走动的时候的动画

	void											LoadRunAnimation(string monsterName);								// 加载跑动的时候的动画

	void											LoadAttackAnimation(string monsterName);							// 加载攻击的时候的动画

	void											LoadBellowAnimation(string monsterName);							// 加载吼叫的时候的动画

	void											LoadBellow2Animation(string monsterName);						// 加载吼叫的时候的动画

	void											LoadDieAnimation(string monsterName);								// 加载死亡的时候的动作

	void											LoadTestAnimation(string monsterName);							// 测试

	MoveBy*									CalculatePath(Point srcPoint,Point destPoint);						// 计算路径

	void											ActionEndCallback();																// 动作结束后的回调函数

	static MonsterAction*				m_pInstance;

	string										m_strMonsterActionConfigFile;												// 怪物动作的配置文件

	MonsterCommand					m_MonsterCommand;															// 怪物发送过来的动作命令

	Animation*								m_pWalkUpAnimation;															// 行走
	Animation*								m_pWalkDownAnimation;
	Animation*								m_pWalkLeftAnimation;
	Animation*								m_pWalkRightAnimation;

	Animation*								m_pRunRightAnimation;														// 跑动
	Animation*								m_pRunDownAnimation;
	Animation*								m_pRunLeftAnimation;
	Animation*								m_pRunUpAnimation;


	Animation*								m_pStaticRightAnimation;														// 静止
	Animation*								m_pStaticDownAnimation;
	Animation*								m_pStaticLeftAnimation;
	Animation*								m_pStaticUpAnimation;


	Animation*								m_pAttackRightAnimation;													// 攻击
	Animation*								m_pAttackDownAnimation;
	Animation*								m_pAttackLeftAnimation;
	Animation*								m_pAttackUpAnimation;


	Animation*								m_pBellowRightAnimation;													// 吼叫
	Animation*								m_pBellowDownAnimation;
	Animation*								m_pBellowLeftAnimation;
	Animation*								m_pBellowUpAnimation;

	Animation*								m_pBellow2RightAnimation;													// 吼叫
	Animation*								m_pBellow2DownAnimation;
	Animation*								m_pBellow2LeftAnimation;
	Animation*								m_pBellow2UpAnimation;


	Animation*								m_pDieRightAnimation;														// 死亡
	Animation*								m_pDieDownAnimation;
	Animation*								m_pDieLeftAnimation;
	Animation*								m_pDieUpAnimation;


	Animation*								m_pTestRightAnimation;
	Animation*								m_pTestDownAnimation;
	Animation*								m_pTestLeftAnimation;
	Animation*								m_pTestUpAnimation;

	map<int,int>							m_DirectionMap;															// 数字和方向的映射
};
RPG_01_END

#endif // !_MONSTER_ACTION_MANGER_H_


