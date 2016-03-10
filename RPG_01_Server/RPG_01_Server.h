#ifndef _RPG_01_SERVER_H_
#define _RPG_01_SERVER_H_

#include "../CommonClass/SelectSocket.h"

struct PackageHead;
class Player;
class GamePackage;
class GameProtocol;

class RPG_01_Server:public SelectSocket
{
public:
	RPG_01_Server();

	void						HandleAccpet(SOCKET fd,sockaddr_in& addr);

	void						HandleRead(SOCKET fd,int nBytes);

	void						HandleClose(SOCKET fd);

	void						BroadcastPackage(Player* player,GameProtocol& protocol);

	void						ForwardPackage(Player* player,GameProtocol& protocol);

	void						Respone(Player* player,GameProtocol& protocol);
};
#endif