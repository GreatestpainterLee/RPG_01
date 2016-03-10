#ifndef _RECVDATA_LOGIC_H_
#define _RECVDATA_LOGIC_H_

#include <cocos2d.h>
#include "define.h"

USING_NS_CC;

struct PackageHead;
class GamePackage;
class GameProtocol;
RPG_01_BEGIN

class Skill;
class Player;
class Monster;
class Player;



class RecvDataLogic;


typedef void (RecvDataLogic::*RecvDataLogicHandle)(GameProtocol& protocol);

class RecvDataLogic
{
public:
	static RecvDataLogic*						GetInstance();
	//====================ҵ���߼����� begin=============================================
	void													Process(GameProtocol& protocol);

	void													HandlePlayerBorn(GameProtocol& protocol);
	void													HandleGetCurrentPlayer(GameProtocol& protocol);
	void													HandlePlayerRun(GameProtocol& protocol);
	//====================ҵ���߼����� end=============================================
private:
	RecvDataLogic();

	void													InitHandleMap();

	static RecvDataLogic*						m_pInstance;

	map<int,RecvDataLogicHandle>		m_HandleMap;
};
RPG_01_END

#endif