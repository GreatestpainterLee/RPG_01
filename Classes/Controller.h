#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <cocos2d.h>
#include "define.h"

USING_NS_CC;


RPG_01_BEGIN
class Player;
class Monster;
class MonsterAI;
class Boss;
class SceneManager;
class EquipmentManager;
class MonsterManager;
class SkillManager;
class PathManager;
class Skill;
class Config;
class MainLogic;
class MonsterLogic;
class PlayerLogic;
class PlayerManager;
class NetworkModule;
class RecvDataLogic;
/*
** 游戏逻辑类
*/
class Controller
{
public:
	~Controller();
	static Controller*			GetInstance();

	SceneManager*				GetSceneManager();

	EquipmentManager*			GetEquipmentManager();

	MonsterManager*			GetMonsterManager();

	SkillManager*					GetSkillManager();

	PathManager*					GetPathManager();

	Config*								GetConfig();

	MonsterAI*						GetMonsterAI();

	NetworkModule*				GetNetworkModule();

	PlayerManager*				GetPlayerManager();

	PlayerLogic*						GetPlayerLogic();

	MonsterLogic*					GetMonsterLogic();

	RecvDataLogic*				GetRecvDataLogic();

public:
	void									Init(const string& strID,const string& strPsd,bool bNetMode);

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

	void									SetCurrentSelectedMonster();

	Monster*							GetBoss();

	Monster*							GetCurrentSelectedMonster(){return m_pCurrentSelectedMonster;}


	string&								GetMyPlayerID(){return m_strMyPlayerID;}
	void									SetMyPlayerInfo(const string& strID,const string& strPsd);

	Player*								GetMyPlayer();

	void									SendPlayerState();
private:
	Controller();

	static Controller*			m_pInstance;

	Monster*						m_pCurrentSelectedMonster;						// 当前被选中的怪物

	Monster*						m_pBoss;														// 当前章节的Boss

	int								m_nCurrentChapter;										// 当前游戏章节

	bool								m_bLoopGame;											// 游戏主循环的循环标志

	bool								m_bIsNetGame;											// 是否为联网游戏

	string							m_strMyPlayerID;

	Player*							m_pMyPlayer;
};

// 全局函数 Game，目的是为了避免总是书写Controller::GetInstance()这样的代码
Controller*							Game();
MainLogic*							GameLogic();

RPG_01_END

#endif // !_GAME_LOGIC_H_
