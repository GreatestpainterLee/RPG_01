#ifndef _MAIN_LOGIC_H_
#define _MAIN_LOGIC_H_

#include <cocos2d.h>
#include "define.h"

USING_NS_CC;


RPG_01_BEGIN

class Skill;
class Player;
class Monster;
class Command;

class MainLogic
{
public:
	static MainLogic* GetInstance();

	void									Init();

	void									StartGame();																		// ��ʼ��Ϸ

	void									Handle(int nMessage);

	void									LoopGame(float delt);														// ��Ϸ����ѭ��

	void									ChangeChapter(int nChapterID);										// ���³���ת��

	int									GetCurrentChapter();														// ��Ϸ�½�ת��

	void									StopGame();																		// ֹͣ��Ϸ

	void									SuspendGame();																// ��ͣ��Ϸ

	void									ContinueGame();																// ������Ϸ

	bool									IsRunning();																		// �ж���Ϸ�Ƿ�������

	bool									IsNetGame();																	// �Ƿ�����

	void									IsNetGame(bool v);															// �Ƿ�����

	bool									CheckPlayerIsInPortal();													// �������Ƿ��ڴ����ŵ�λ��		

	//====================ҵ���߼����� begin=============================================
	void									HandleRightClick(Point& destPoint);									// ��������Ҽ������Ļ���¼�

	void									HandleLeftClick(Point& destPoint,Skill* pSkill);					// �����������¼�

	//====================ҵ���߼����� end=============================================

	Player*								GetMyPlayer();

	Player*								GetPlayer(const string& strID);

	void									AddPlayer(Player* player);

	void									NewPlayer(const string& strID);

	void									DeletePlayer(Player* player);

	void									DeletePlayer(const string& strID);

	void									SetCurrentSelectedMonster();

	Monster*							GetBoss();

	Monster*							GetCurrentSelectedMonster(){return m_pCurrentSelectedMonster;}

public:
	static const int					MaxPlayerNum = 8;

private:

	Monster*							m_pCurrentSelectedMonster;						// ��ǰ��ѡ�еĹ���

	Monster*							m_pBoss;														// ��ǰ�½ڵ�Boss

	Player*								m_pPlayer;													// ��Ҷ���

	int									m_nCurrentChapter;										// ��ǰ��Ϸ�½�

	bool									m_bLoopGame;											// ��Ϸ��ѭ����ѭ����־

	bool									m_bIsNetGame;											// �Ƿ�Ϊ������Ϸ

	vector<Player*>				m_PlayerList;													// ����б�

private:
	MainLogic(){}
	static MainLogic* m_pInstance;
};
RPG_01_END

#endif