#include "PlayerManager.h"
#include "Player.h"

PlayerManager* PlayerManager::m_pInstance = 0;

PlayerManager* PlayerManager::GetInstance()
{
	if (0 == m_pInstance)
	{
		m_pInstance = new PlayerManager;
	}

	return m_pInstance;
}

void PlayerManager::Init(RPG_01_Server* pServer)
{
	m_pServer = pServer;
}

void PlayerManager::CreatePlayer(SOCKET s,sockaddr_in& addr)
{
	Player* player = new Player;
	player->SetAddr(addr);
	player->SetSocket(s);

	m_PlayerList.push_back(player);
}

void PlayerManager::RecordPlayer(const string& strID)
{
	m_PlayerIDSet.insert(strID);
}

Player* PlayerManager::FindPlayer(SOCKET s)
{
	for (int i = 0; i < m_PlayerList.size(); ++i)
	{
		if (m_PlayerList[i]->GetSocket() == s)
		{
			return m_PlayerList[i];
		}
	}

	return 0;
}

bool PlayerManager::IsLogin(const string& strID)
{
	set<string>::iterator it = m_PlayerIDSet.find(strID);
	if (it == m_PlayerIDSet.end())
	{
		return false;
	}

	return true;
}

void PlayerManager::DeletePlayer(SOCKET s)
{
	Player* player = 0;
	vector<Player*>::iterator it;
	for (it = m_PlayerList.begin(); it != m_PlayerList.end(); ++it)
	{
		if ((*it)->GetSocket() == s)
		{
			player = (*it);
			m_PlayerList.erase(it);
			break;
		}
	}

	delete player;
}