#ifndef _PLAYER_ACTION_MANAGER_H_
#define _PLAYER_ACTION_MANAGER_H_

#include <cocos2d.h>
#include "define.h"
#include "Command.h"
#include "PlayerCommand.h"
USING_NS_CC;

RPG_01_BEGIN
class Player;

/*
** 玩家动作类
** 管理着玩家的各种动作
*/
class PlayerAction
{
public:
	typedef Vector<SpriteFrame*> FrameList;

	static PlayerAction*		GetInstance();

	virtual void								Execute(Command* pCmd);

	void											SetRoleName(const string& name)
	{
		m_strRole = name;
	}

private:
	PlayerAction();

	void											LoadWalkAnimation();

	void											LoadRunAnimation();

	void											LoadStaticAnimation();

	void											LoadAttackAnimation();

	void											LoadThrowoffAnimation();

	void											LoadBeatenAnimation();

	void											LoadDieAnimation();

	void											LoadTestAnimation();

	MoveBy*									CalculatePath(Point srcPoint,Point destPoint);

	void											ActionEndCallback();

	static PlayerAction*					m_pInstance;

	PlayerCommand						m_PlayerCommand;

	string										m_strPlayerActionConfigFile;

	string										m_strRole;

	Animation*				m_pWalkRightUpAnimation;
	Animation*				m_pWalkRightAnimation;
	Animation*				m_pWalkRightDownAnimation;
	Animation*				m_pWalkDownAnimation;
	Animation*				m_pWalkLeftDownAnimation;
	Animation*				m_pWalkLeftAnimation;
	Animation*				m_pWalkLeftUpAnimation;
	Animation*				m_pWalkUpAnimation;

	Animation*				m_pRunRightUpAnimation;
	Animation*				m_pRunRightAnimation;
	Animation*				m_pRunRightDownAnimation;
	Animation*				m_pRunDownAnimation;
	Animation*				m_pRunLeftDownAnimation;
	Animation*				m_pRunLeftAnimation;
	Animation*				m_pRunLeftUpAnimation;
	Animation*				m_pRunUpAnimation;

	Animation*				m_pStaticRightUpAnimation;
	Animation*				m_pStaticRightAnimation;
	Animation*				m_pStaticRightDownAnimation;
	Animation*				m_pStaticDownAnimation;
	Animation*				m_pStaticLeftDownAnimation;
	Animation*				m_pStaticLeftAnimation;
	Animation*				m_pStaticLeftUpAnimation;
	Animation*				m_pStaticUpAnimation;

	Animation*				m_pAttackRightUpAnimation;
	Animation*				m_pAttackRightAnimation;
	Animation*				m_pAttackRightDownAnimation;
	Animation*				m_pAttackDownAnimation;
	Animation*				m_pAttackLeftDownAnimation;
	Animation*				m_pAttackLeftAnimation;
	Animation*				m_pAttackLeftUpAnimation;
	Animation*				m_pAttackUpAnimation;

	Animation*				m_pThrowoffRightUpAnimation;
	Animation*				m_pThrowoffRightAnimation;
	Animation*				m_pThrowoffRightDownAnimation;
	Animation*				m_pThrowoffDownAnimation;
	Animation*				m_pThrowoffLeftDownAnimation;
	Animation*				m_pThrowoffLeftAnimation;
	Animation*				m_pThrowoffLeftUpAnimation;
	Animation*				m_pThrowoffUpAnimation;

	Animation*				m_pBeatenRightUpAnimation;
	Animation*				m_pBeatenRightAnimation;
	Animation*				m_pBeatenRightDownAnimation;
	Animation*				m_pBeatenDownAnimation;
	Animation*				m_pBeatenLeftDownAnimation;
	Animation*				m_pBeatenLeftAnimation;
	Animation*				m_pBeatenLeftUpAnimation;
	Animation*				m_pBeatenUpAnimation;

	Animation*				m_pDieRightUpAnimation;
	Animation*				m_pDieRightAnimation;
	Animation*				m_pDieRightDownAnimation;
	Animation*				m_pDieDownAnimation;
	Animation*				m_pDieLeftDownAnimation;
	Animation*				m_pDieLeftAnimation;
	Animation*				m_pDieLeftUpAnimation;
	Animation*				m_pDieUpAnimation;

	//Beaten
	Animation*				m_pTestRightUpAnimation;
	Animation*				m_pTestRightAnimation;
	Animation*				m_pTestRightDownAnimation;
	Animation*				m_pTestDownAnimation;
	Animation*				m_pTestLeftDownAnimation;
	Animation*				m_pTestLeftAnimation;
	Animation*				m_pTestLeftUpAnimation;
	Animation*				m_pTestUpAnimation;


	map<int,int>							m_DirectionMap;

};
RPG_01_END


#endif // !_PLAYER_ACTION_MANAGER_H_
