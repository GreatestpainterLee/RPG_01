#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_


#include <cocos2d.h>

#include "define.h"

USING_NS_CC;

class GameProtocol;
class GamePackage_Player;

RPG_01_BEGIN

	/*
	** 玩家的管理类
	*/
class Player;
class PlayerManager
{
public:
	static const int					MaxPlayerNum = 8;

	static PlayerManager* GetInstance();
	virtual ~PlayerManager(){};

	void									Init();

	Player*								GetPlayer(const string& strID);

	void									AddPlayer(Player* player);

	Player*								NewPlayer(const string& strID);

	void									DeletePlayer(Player* player);

	void									DeletePlayer(const string& strID);

	vector<Player*>&			GetPlayerList(){return m_PlayerList;}

	void									ConvertPlayer2Package(Player& player,GamePackage_Player& pack_player);
	void									ConvertPackage2Player(const GamePackage_Player& pack_player,Player& player);

private:
	PlayerManager();
	static PlayerManager*			m_pInstance;

	vector<Player*>					m_PlayerList;													// 玩家列表

};

RPG_01_END

#endif

