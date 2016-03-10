#ifndef _MAIN_LOGIC_H_
#define _MAIN_LOGIC_H_

#include "../CommonClass/common.h"

class Player;
class GamePackage;

class PlayerManager;
class RPG_01_Server;

typedef void (PlayerManager::*Handler)(Player* player,GamePackage* pack);
class PlayerManager
{
public:
	static PlayerManager*	GetInstance();
	void								Init(RPG_01_Server* pServer);

	void								CreatePlayer(SOCKET s,sockaddr_in& addr);
	void								DeletePlayer(SOCKET s);

	void								Process(Player* player,GamePackage* pack);

	vector<Player*>&		GetPlayerList(){return m_PlayerList;}

	Player*							FindPlayer(SOCKET s);

	bool								IsLogin(const string& strID);

	void								RecordPlayer(const string& strID);
private:
	void								InitHandleMap();

private:
	set<string>					m_PlayerIDSet;
	static PlayerManager*	m_pInstance;
	vector<Player*>			m_PlayerList;
	map<int,Handler>		m_HandleMap;
	RPG_01_Server*			m_pServer;
};
#endif