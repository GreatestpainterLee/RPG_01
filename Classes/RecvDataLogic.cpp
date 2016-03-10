#include "RecvDataLogic.h"

#include "Controller.h"
#include "Player.h"
#include "Util.h"
#include "Player.h"
#include "MonsterManager.h"
#include "Monster.h"
#include "PathManager.h"
#include "./scene/BaseScene.h"
#include "SceneManager.h"
#include "Skill.h"
#include "MonsterAI.h"
#include "EquipmentManager.h"
#include "SkillManager.h"
#include "Config.h"
#include "FlowWord.h"
#include "NetworkModule.h"
#include "RecvDataLogic.h"
#include "PlayerLogic.h"
#include "PlayerManager.h"
#include "../CommonClass/PackageHead.h"
#include "../CommonClass/GameProtocol.h"

RPG_01_BEGIN

RecvDataLogic* RecvDataLogic::m_pInstance = 0;

RecvDataLogic* RecvDataLogic::GetInstance()
{
	if(0 == m_pInstance)
	{
		m_pInstance = new RecvDataLogic;
		m_pInstance->InitHandleMap();
	}

	return m_pInstance;
}

RecvDataLogic::RecvDataLogic()
{
}

void RecvDataLogic::InitHandleMap()
{
	m_HandleMap[CodeMsg::code_player_born] = &RecvDataLogic::HandlePlayerBorn;
	m_HandleMap[CodeMsg::code_player_request_all_online_players_ret] = &RecvDataLogic::HandleGetCurrentPlayer;
	m_HandleMap[CodeMsg::code_player_run] = &RecvDataLogic::HandlePlayerRun;
}


void RecvDataLogic::Process(GameProtocol& protocol)
{

	map<int,RecvDataLogicHandle>::iterator it;

	it = m_HandleMap.find(protocol.GetMsgCode());

	if (it == m_HandleMap.end())
	{
		CCLOG("未找到处理函数 code = %d",protocol.GetMsgCode());
		return;
	}

	(this->*(it->second))(protocol);
}

void RecvDataLogic::HandlePlayerBorn(GameProtocol& protocol)
{
	Player* ply = Game()->GetPlayerManager()->NewPlayer(protocol.GetPlayer(0).userid());
	Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer()->addChild(ply);
}

void RecvDataLogic::HandleGetCurrentPlayer(GameProtocol& protocol)
{
	for (int i = 0; i < protocol.GetPlayerNum(); ++i)
	{
		Player* ply = Game()->GetPlayerManager()->NewPlayer(protocol.GetPlayer(i).userid());
		//Game()->GetPlayerManager()->ConvertPackage2Player((protocol.GetPlayer(0)),*ply);
		Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer()->addChild(ply);
		ply->setPosition(protocol.GetPlayer(i).currentpointx(),protocol.GetPlayer(i).currentpointy());
		ply->Action(protocol.GetPlayer(i).msgcode(),protocol.GetPlayer(i).direction());
	}
}

void RecvDataLogic::HandlePlayerRun(GameProtocol& protocol)
{
	Player* ply =  Game()->GetPlayerManager()->GetPlayer(protocol.GetPlayer(0).userid());
	vector<Player*> playerlist = Game()->GetPlayerManager()->GetPlayerList();
	CCLOG(protocol.GetPlayer(0).userid().c_str());
	if (ply != 0)
	{
		ply->SetDestPoint(Point(protocol.GetPlayer(0).destpointx(),protocol.GetPlayer(0).destpointy()));
		ply->Action(CodeMsg::code_player_run,protocol.GetPlayer(0).direction());
	}
}
RPG_01_END