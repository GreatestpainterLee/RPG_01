#include "PlayerManager.h"
#include "Player.h"
#include "Controller.h"
#include "scene/BaseScene.h"
#include "SceneManager.h"
#include "Config.h"
#include "../CommonClass/GamePackage.pb.h"
#include "../CommonClass/GameProtocol.h"
#include "../CommonClass/PackageHead.h"

RPG_01_BEGIN

PlayerManager* PlayerManager::m_pInstance = 0;

PlayerManager* PlayerManager::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new PlayerManager;

		
	}

	return m_pInstance;
}

void PlayerManager::Init()
{
	NewPlayer(Game()->GetConfig()->GetRandomID());
}

PlayerManager::PlayerManager()
{
}

Player* PlayerManager::GetPlayer(const string& strID)
{
	for (int i = 0; i < m_PlayerList.size(); ++i)
	{
		if (0 == strcmp(strID.c_str(),m_PlayerList[i]->GetID().c_str()))
		{
			return m_PlayerList[i];
		}
	}
	return 0;
}

void PlayerManager::AddPlayer(Player* player)
{
	if (m_PlayerList.size() == MaxPlayerNum)
	{
		return;
	}
	m_PlayerList.push_back(player);
}

Player* PlayerManager::NewPlayer(const string& strID)
{
	Player* play = Player::create();
	play->SetID(strID);

	play->setPosition(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	play->SetDestPoint(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	play->SetDirection(right_direction);

	play->Action(CodeMsg::code_player_static,right_direction);

	AddPlayer(play);

	return play;
}

void PlayerManager::DeletePlayer(Player* player)
{
	vector<Player*>::iterator it;
	for (it = m_PlayerList.begin(); it != m_PlayerList.end(); ++it)
	{
		if ((*it) == player)
		{
			delete player;
			m_PlayerList.erase(it);
			break;
		}
	}
}

void PlayerManager::DeletePlayer(const string& strID)
{
	vector<Player*>::iterator it;
	for (it = m_PlayerList.begin(); it != m_PlayerList.end(); ++it)
	{
		if (0 == strcmp((*it)->GetID().c_str() ,strID.c_str()))
		{
			delete (*it);
			m_PlayerList.erase(it);
			break;
		}
	}
}

void PlayerManager::ConvertPlayer2Package(Player& player,GamePackage_Player& pack_player)
{
	pack_player.set_userid(player.GetID());
	pack_player.set_speed(player.GetSpeed());
	pack_player.set_direction(player.GetDirection());
	pack_player.set_destpointx(player.GetDestPoint().x);
	pack_player.set_destpointy(player.GetDestPoint().y);
	pack_player.set_currentpointx(player.getPosition().x);
	pack_player.set_currentpointy(player.getPosition().y);
	pack_player.set_msgcode(player.GetMsg());

	pack_player.set_bloodvalue(player.GetBloodValue());
	pack_player.set_maxbloodvalue(player.GetMaxBloodValue());
	pack_player.set_magicvalue(player.GetMagicValue());
	pack_player.set_maxmagicvalue(player.GetMaxMagicValue());
	pack_player.set_empiricalvalue(player.GetEmpiricalValue());
	pack_player.set_maxempiricalvalue(player.GetMaxEmpiricalValue());
	pack_player.set_level(player.GetLevel());
	pack_player.set_damagevalue(player.GetDamageValue());
	//pack_player.set_skill(player.GetCurrentSkill()->GetSkillID());
}

void PlayerManager::ConvertPackage2Player(const GamePackage_Player& pack_player,Player& player)
{
	player.SetID(pack_player.userid());
	player.SetSpeed(pack_player.speed());
	//player.SetDirection(pack_player.direction());
	player.SetDestPoint(Point(pack_player.destpointx(),pack_player.destpointy()));
	//player.setPosition(Point(pack_player.currentpointx(),pack_player.currentpointy()));
	//player.SetMsg(pack_player.msgcode());
	player.SetBloodValue(pack_player.bloodvalue());
	player.SetMaxBloodValue(pack_player.maxbloodvalue());
	player.SetMagicValue(pack_player.magicvalue());
	player.SetMaxMagicValue(pack_player.maxmagicvalue());
	player.SetEmpiricalValue(pack_player.empiricalvalue());
	player.SetMaxEmpiricalValue(pack_player.maxempiricalvalue());
	player.SetLevel(pack_player.level());
	player.SetDamageValue(pack_player.damagevalue());
	//player.SetCurrentSkill(pack_player.skill());
}

RPG_01_END