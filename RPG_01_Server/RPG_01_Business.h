#ifndef _RPG_01_BUSINESS_H_
#define _RPG_01_BUSINESS_H_

#include "../CommonClass/common.h"
class GameProtocol;
class RPG_01_Business;
class RPG_01_Server;
class PlayerManager;
class Player;

typedef void (RPG_01_Business::*RPG_01_Business_Handle)(Player* player,GameProtocol& protocol);

class RPG_01_Business
{
public:
	static RPG_01_Business*		GetInstance();
	void										Init(RPG_01_Server* pServer);
	void										Process(Player* player,GameProtocol& protocol);

	PlayerManager*					GetPlayerManager();

protected:
	void										InitHandleMap();

	void										HandlePlayerLogin(Player* player,GameProtocol& protocol);
	void										HandlePlayerLogout(Player* player,GameProtocol& protocol);
	void										HandlePlayerBorn(Player* player,GameProtocol& protocol);
	void										HandleRequestAllOnlinePlayer(Player* player,GameProtocol& protocol);
	void										HandlePlayerRun(Player* player,GameProtocol& protocol);
	void										HandlePlayerState(Player* player,GameProtocol& protocol);
private:
	static RPG_01_Business* m_pInstance;
	RPG_01_Server*					m_pServer;

	map<int,RPG_01_Business_Handle> m_HandleMap;
};

RPG_01_Business* Business();

#endif