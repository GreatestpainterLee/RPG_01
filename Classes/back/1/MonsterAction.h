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
** ����Ķ�����
*/
class MonsterAction
{
public:
	static MonsterAction*				GetInstance();

	virtual void								Execute(Command* pCmd);													// ִ�й��ﶯ��

private:
	MonsterAction();

	void											LoadStaticAnimation(string monsterName);							// ���ؾ�ֹʱ��Ķ���

	void											LoadWalkAnimation(string monsterName);							// �����߶���ʱ��Ķ���

	void											LoadRunAnimation(string monsterName);								// �����ܶ���ʱ��Ķ���

	void											LoadAttackAnimation(string monsterName);							// ���ع�����ʱ��Ķ���

	void											LoadBellowAnimation(string monsterName);							// ���غ�е�ʱ��Ķ���

	void											LoadBellow2Animation(string monsterName);						// ���غ�е�ʱ��Ķ���

	void											LoadDieAnimation(string monsterName);								// ����������ʱ��Ķ���

	void											LoadTestAnimation(string monsterName);							// ����

	MoveBy*									CalculatePath(Point srcPoint,Point destPoint);						// ����·��

	void											ActionEndCallback();																// ����������Ļص�����

	static MonsterAction*				m_pInstance;

	string										m_strMonsterActionConfigFile;												// ���ﶯ���������ļ�

	MonsterCommand					m_MonsterCommand;															// ���﷢�͹����Ķ�������

	Animation*								m_pWalkUpAnimation;															// ����
	Animation*								m_pWalkDownAnimation;
	Animation*								m_pWalkLeftAnimation;
	Animation*								m_pWalkRightAnimation;

	Animation*								m_pRunRightAnimation;														// �ܶ�
	Animation*								m_pRunDownAnimation;
	Animation*								m_pRunLeftAnimation;
	Animation*								m_pRunUpAnimation;


	Animation*								m_pStaticRightAnimation;														// ��ֹ
	Animation*								m_pStaticDownAnimation;
	Animation*								m_pStaticLeftAnimation;
	Animation*								m_pStaticUpAnimation;


	Animation*								m_pAttackRightAnimation;													// ����
	Animation*								m_pAttackDownAnimation;
	Animation*								m_pAttackLeftAnimation;
	Animation*								m_pAttackUpAnimation;


	Animation*								m_pBellowRightAnimation;													// ���
	Animation*								m_pBellowDownAnimation;
	Animation*								m_pBellowLeftAnimation;
	Animation*								m_pBellowUpAnimation;

	Animation*								m_pBellow2RightAnimation;													// ���
	Animation*								m_pBellow2DownAnimation;
	Animation*								m_pBellow2LeftAnimation;
	Animation*								m_pBellow2UpAnimation;


	Animation*								m_pDieRightAnimation;														// ����
	Animation*								m_pDieDownAnimation;
	Animation*								m_pDieLeftAnimation;
	Animation*								m_pDieUpAnimation;


	Animation*								m_pTestRightAnimation;
	Animation*								m_pTestDownAnimation;
	Animation*								m_pTestLeftAnimation;
	Animation*								m_pTestUpAnimation;

	map<int,int>							m_DirectionMap;															// ���ֺͷ����ӳ��
};
RPG_01_END

#endif // !_MONSTER_ACTION_MANGER_H_


