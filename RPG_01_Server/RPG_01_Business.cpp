#include "RPG_01_Business.h"
#include "PlayerManager.h"
#include "../CommonClass/CodeMsg.h"
#include "../CommonClass/GamePackage.pb.h"
#include "../CommonClass/GameProtocol.h"
#include "../CommonClass/PackageHead.h"
#include "Player.h"
#include "RPG_01_Server.h"

RPG_01_Business* Business()
{
	return RPG_01_Business::GetInstance();
}

RPG_01_Business* RPG_01_Business::m_pInstance = 0;

RPG_01_Business* RPG_01_Business::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new RPG_01_Business;
	}

	return m_pInstance;
}


PlayerManager* RPG_01_Business::GetPlayerManager()
{
	return PlayerManager::GetInstance();
}

void RPG_01_Business::Init(RPG_01_Server* pServer)
{
	m_pServer = pServer;
	GetPlayerManager()->Init(pServer);
	InitHandleMap();
}

void RPG_01_Business::InitHandleMap()
{
	m_HandleMap[CodeMsg::code_login] = &RPG_01_Business::HandlePlayerLogin;
	m_HandleMap[CodeMsg::code_logout] = &RPG_01_Business::HandlePlayerLogout;
	m_HandleMap[CodeMsg::code_player_born] = &RPG_01_Business::HandlePlayerBorn;
	m_HandleMap[CodeMsg::code_player_request_all_online_players] = &RPG_01_Business::HandleRequestAllOnlinePlayer;
	m_HandleMap[CodeMsg::code_player_run] = &RPG_01_Business::HandlePlayerRun;
	//m_HandleMap[CodeMsg::code_player_send_state] = &RPG_01_Business::HandlePlayerState;
}

void RPG_01_Business::Process(Player* player,GameProtocol& protocol)
{
	map<int ,RPG_01_Business_Handle>::iterator it;

	it = m_HandleMap.find(protocol.GetMsgCode());

	if (it == m_HandleMap.end())
	{
		return;
	}

	(this->*(it->second))(player,protocol);

}



void RPG_01_Business::HandlePlayerLogin(Player* player,GameProtocol& protocol)
{
	if (GetPlayerManager()->IsLogin(protocol.GetPlayer(0).userid()))
	{
		protocol.Clean();
		protocol.SetMsgCode(CodeMsg::code_login_ret_failed);
	}
	else
	{
		player->SetID(protocol.GetPlayer(0).userid());
		player->SetPassword(protocol.GetPlayer(0).password());

		GetPlayerManager()->RecordPlayer(player->GetID());

		protocol.Clean();
		protocol.SetMsgCode(CodeMsg::code_login_ret_ok);

	}
	
	m_pServer->Respone(player,protocol);

	cout << "Player = " << player->GetID() << endl;
}

void RPG_01_Business::HandlePlayerLogout(Player* player,GameProtocol& protocol)
{

}

void RPG_01_Business::HandlePlayerBorn(Player* player,GameProtocol& protocol)
{
	protocol.Clean();
	protocol.SetMsgCode(CodeMsg::code_player_born);
	GamePackage_Player* pl = protocol.AddPlayer();
	pl->set_userid(player->GetID());
	m_pServer->ForwardPackage(player,protocol);
}

void RPG_01_Business::HandleRequestAllOnlinePlayer(Player* player,GameProtocol& protocol)
{
	vector<Player*> plyerlist = Business()->GetPlayerManager()->GetPlayerList();

	vector<Player*>::iterator it;
	protocol.SetMsgCode(CodeMsg::code_player_request_all_online_players_ret);

	if (plyerlist.size() == 1)
	{
		//return;
	}

	for (it = plyerlist.begin(); it != plyerlist.end(); ++it)
	{
		if ((*it) == player)
		{
			continue;
		}
		GamePackage_Player* pl =  protocol.AddPlayer();
		pl->set_userid((*it)->GetID());
		pl->set_msgcode(CodeMsg::code_player_static);
		pl->set_direction(6);
		pl->set_currentpointx(200);
		pl->set_currentpointy(200);
		pl->set_currentpointx(player->GetCurrentPointX());
		pl->set_currentpointy(player->GetCurrentPointY());
		//Player::ConvertPlayer2Pack(*player,*pl);
	}

	m_pServer->Respone(player,protocol);
	return;
}

void RPG_01_Business::HandlePlayerRun(Player* player,GameProtocol& protocol)
{
	m_pServer->ForwardPackage(player,protocol);
}

void RPG_01_Business::HandlePlayerState(Player* player,GameProtocol& protocol)
{
	if (protocol.GetPlayerNum() <= 0)
	{
		return;
	}
	Player::ConvertPack2Player(protocol.GetPlayer(0),*player);
}