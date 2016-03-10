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

	void									StartGame();																		// 开始游戏

	void									Handle(int nMessage);

	void									LoopGame(float delt);														// 游戏的主循环

	void									ChangeChapter(int nChapterID);										// 故事场景转换

	int									GetCurrentChapter();														// 游戏章节转换

	void									StopGame();																		// 停止游戏

	void									SuspendGame();																// 暂停游戏

	void									ContinueGame();																// 继续游戏

	bool									IsRunning();																		// 判断游戏是否在运行

	bool									IsNetGame();																	// 是否联网

	void									IsNetGame(bool v);															// 是否联网

	bool									CheckPlayerIsInPortal();													// 检查玩家是否在传送门的位置		

	//====================业务逻辑处理 begin=============================================
	void									HandleRightClick(Point& destPoint);									// 处理鼠标右键点击屏幕的事件

	void									HandleLeftClick(Point& destPoint,Skill* pSkill);					// 处理鼠标左键事件

	//====================业务逻辑处理 end=============================================

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

	Monster*							m_pCurrentSelectedMonster;						// 当前被选中的怪物

	Monster*							m_pBoss;														// 当前章节的Boss

	Player*								m_pPlayer;													// 玩家对象

	int									m_nCurrentChapter;										// 当前游戏章节

	bool									m_bLoopGame;											// 游戏主循环的循环标志

	bool									m_bIsNetGame;											// 是否为联网游戏

	vector<Player*>				m_PlayerList;													// 玩家列表

private:
	MainLogic(){}
	static MainLogic* m_pInstance;
};
RPG_01_END

#endif