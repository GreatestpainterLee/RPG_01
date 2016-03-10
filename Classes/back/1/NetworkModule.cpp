#include "NetworkModule.h"
#include "../CommonClass/CodeMsg.h"
#include "Player.h"
#include "Controller.h"
#include "PlayerManager.h"

RPG_01_BEGIN
NetworkModule* NetworkModule::m_pInstance = 0;

NetworkModule* NetworkModule::GetInstance()
{
	if (0 == m_pInstance)
	{
		m_pInstance = new NetworkModule;
	}

	return m_pInstance;
}

void NetworkModule::ReadPackage(GameProtocol& protocol)
{
	char buf[1024] = {0};
	Read(buf,PackageHead::HeadLength);
	protocol.DeserializeHeadFromByteArray(buf);

	if (protocol.GetPackageLength() == 0)
	{
		return;
	}

	memset(buf,0,1024);

	Read(buf,protocol.GetPackageLength());

	protocol.DeserializePackFromByteArray(buf,protocol.GetPackageLength());
}

void NetworkModule::SendPackage(GameProtocol& protocol)
{
	char* pData = 0;
	int len = protocol.SerializeToByteArray(pData);

	Write(pData,len);
}

bool NetworkModule::TryReadPackage(GameProtocol& protocol)
{
	char buf[1024] = {0};
	bool nRet = TryRead(buf,PackageHead::HeadLength);
	if (nRet == false)
	{
		return false;
	}
	protocol.DeserializeHeadFromByteArray(buf);

	if (protocol.GetPackageLength() == 0)
	{
		return true;
	}

	memset(buf,0,1024);

	nRet = Read(buf,protocol.GetPackageLength());
	/*
	if (nRet == false)
	{
		return false;
	}*/

	protocol.DeserializePackFromByteArray(buf,protocol.GetPackageLength());

	return true;
}

bool NetworkModule::TryReadPackageHead(PackageHead& head)
{
	char buf[1024] = {0};
	bool bRet = TryRead(buf,PackageHead::HeadLength);
	if (bRet == false)
	{
		return false;
	}
	head.DeserializeFromByteArray(buf);
	return true;
}

void NetworkModule::ReadPackageBody(int len,GamePackage& package)
{
	char buf[1024] = {0};
	bool bRet = Read(buf,len);

	package.ParseFromArray(buf,len);
}

bool NetworkModule::Login(const string& strID,const string& password)
{
	GameProtocol protocol;
	protocol.SetMsgCode(CodeMsg::code_login);
	GamePackage_Player* pl = protocol.AddPlayer();
	pl->set_userid(strID);
	pl->set_password(password);
	SendPackage(protocol);
	protocol.Clean();
	ReadPackage(protocol);
	if (protocol.GetMsgCode() != CodeMsg::code_login_ret_ok)
	{
		return false;
	}
	return true;
}

void NetworkModule::Logout()
{

}

void NetworkModule::Born()
{
	GameProtocol protocol;
	protocol.SetMsgCode(CodeMsg::code_player_born);
	SendPackage(protocol);
}

void NetworkModule::RequestAllOnlinePlayer()
{
	GameProtocol protocol;
	protocol.SetMsgCode(CodeMsg::code_player_request_all_online_players);
	SendPackage(protocol);
}

void NetworkModule::SendPlayerState(Player* player)
{
	GameProtocol protocol;
	protocol.SetMsgCode(player->GetMsg());
	GamePackage_Player* pl = protocol.AddPlayer();
	//Game()->GetPlayerManager()->ConvertPlayer2Package(*player,*pl);
	pl->set_userid(player->GetID());
	pl->set_destpointx(player->GetDestPoint().x);
	pl->set_destpointy(player->GetDestPoint().y);
	pl->set_direction(player->GetDirection());

	SendPackage(protocol);
}

RPG_01_END