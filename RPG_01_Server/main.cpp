// RPG_01_Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
using namespace std;
#include "../CommonClass/GamePackage.pb.h"

#pragma comment(lib,"../CommonClass/libprotobuf-lite.lib")  
#pragma comment(lib,"../CommonClass/libprotobuf.lib")  

#include "RPG_01_Server.h"
#include "../CommonClass/PackageHead.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GamePackage pack;

	GamePackage::Player* pl = pack.add_playerlist();
	pl->set_msgcode(0);
	pl->set_bloodvalue(20);
	pl->set_damagevalue(50);
	GamePackage::Monster* pm = pack.add_monsterlist();
	pm->set_event(0);
	string str = pack.SerializeAsString();
	int s = pack.ByteSize();


	PackageHead head;
	head.SetPackageLength(pack.ByteSize());

	RPG_01_Server S;
	S.CreateServer(0,9000);
	S.ServerLoop();
	return 0;
}

