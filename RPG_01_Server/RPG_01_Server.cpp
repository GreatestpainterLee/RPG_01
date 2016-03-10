#include "RPG_01_Server.h"

#include "../CommonClass/GamePackage.pb.h"
#include "../CommonClass/PackageHead.h"
#include "Player.h"
#include "PlayerManager.h"
#include "../CommonClass/CodeMsg.h"
#include "../CommonClass/GameProtocol.h"
#include "RPG_01_Business.h"

RPG_01_Server::RPG_01_Server()
{
	Business()->Init(this);
}

void RPG_01_Server::HandleAccpet(SOCKET fd,sockaddr_in& addr)
{
	PlayerManager::GetInstance()->CreatePlayer(fd,addr);
}

void RPG_01_Server::HandleRead(SOCKET fd,int nBytes)
{
	Player* player = Business()->GetPlayerManager()->FindPlayer(fd);

	if (player == 0)
	{
		return;
	}

	GameProtocol protocol;

	char buff[1024] = {0};

	Read(fd,buff,PackageHead::HeadLength);

	protocol.DeserializeHeadFromByteArray(buff);
	
	memset(buff,0,1024);

	Read(fd,buff,protocol.GetPackageLength());

	protocol.DeserializePackFromByteArray(buff,protocol.GetPackageLength());

	//protocol.Print();

	Business()->Process(player,protocol);
}

void RPG_01_Server::HandleClose(SOCKET fd)
{
	CloseSocket(fd);
	PlayerManager::GetInstance()->DeletePlayer(fd);
}

void RPG_01_Server::BroadcastPackage(Player* player,GameProtocol& protocol)
{
	vector<Player*> plyerlist = Business()->GetPlayerManager()->GetPlayerList();
	vector<Player*>::iterator it;

	char* pData = 0;
	int len = protocol.SerializeToByteArray(pData);

	for (it = plyerlist.begin(); it != plyerlist.end(); ++it)
	{
		Write((*it)->GetSocket(),pData,len);
	}
}

void RPG_01_Server::ForwardPackage(Player* player,GameProtocol& protocol)
{
	vector<Player*> plyerlist = Business()->GetPlayerManager()->GetPlayerList();
	vector<Player*>::iterator it;

	char* pData = 0;
	int len = protocol.SerializeToByteArray(pData);

	for (it = plyerlist.begin(); it != plyerlist.end(); ++it)
	{
		if ((*it) == player)
		{
			continue;
		}
		Write((*it)->GetSocket(),pData,len);
	}
}

void RPG_01_Server::Respone(Player* player,GameProtocol& protocol)
{
	if (player == 0 )
	{
		return;
	}

	char* pData = 0;
	int len = protocol.SerializeToByteArray(pData);
	Write(player->GetSocket(),pData,len);
}