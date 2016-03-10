#ifndef _NETWORK_MODULE_H_
#define _NETWORK_MODULE_H_

#include "define.h"
#include "../CommonClass/SelectSocket.h"
#include "../CommonClass/GamePackage.pb.h"
#include "../CommonClass/PackageHead.h"
#include "../CommonClass/GameProtocol.h"

#pragma comment(lib,"../CommonClass/libprotobuf-lite-re.lib")  
#pragma comment(lib,"../CommonClass/libprotobuf-re.lib")  

RPG_01_BEGIN
class Player;
class NetworkModule:public SelectSocketClient
{
public:
	static NetworkModule*GetInstance();

	void								ReadPackage(GameProtocol& protocol);

	void								SendPackage(GameProtocol& protocol);

	bool								TryReadPackage(GameProtocol& protocol);

	bool								TryReadPackageHead(PackageHead& head);

	void								ReadPackageBody(int len,GamePackage& pack);

public:
	bool								Login(const string& strID,const string& password);
	void								Logout();

	void								Born();

	void								RequestAllOnlinePlayer();

	void								SendPlayerState(Player* player);

protected:
	NetworkModule(){}
private:
	static NetworkModule* m_pInstance;

};
RPG_01_END
#endif