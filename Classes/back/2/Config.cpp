#include "Config.h"
#include "cocos-ext.h"

#include "LuaHandler.h"
#include "Util.h"

USING_NS_CC_EXT;

RPG_01_BEGIN
Config* Config::m_pInstance = 0;

Config::Config()
{
	m_fProcessInterval = 10.0f;
}

Config* Config::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new Config;
		m_pInstance->LoadConfig();
	}

	return m_pInstance;
}

void Config::LoadConfig()
{
	// Lua处理器
	LuaHandler lua_hadndler;

	string strLuaFile = "E:/Work/cocos2d-x-3.4/MyGame/testAll/proj.win32/Debug.win32/config/config.lua";
	// 加载lua文件
	lua_hadndler.LoadFile(Util::Unix2WinPath(strLuaFile).c_str());//

	// 设置堆栈
	lua_hadndler.SetTop(0);

	// 读取lua配置文件
	m_strPlayerActionConfigFile					= lua_hadndler.GetGlobalString("player_action_configfile"); 
	m_strMonsterActionConfigFile				=  lua_hadndler.GetGlobalString("monster_action_configfile");
	m_strSkillActionConfigFile						= lua_hadndler.GetGlobalString("skill_action_configfile"); 

	m_strRoleName									= lua_hadndler.GetGlobalString("PlayerName"); 

	m_fProcessInterval								= lua_hadndler.GetGlobalNum("ProcessInterval");
	m_fPlayerSpeed									= lua_hadndler.GetGlobalNum("PlayerSpeed");
	m_fPlayerSpeedIncrement					= lua_hadndler.GetGlobalNum("PlayerSpeedIncrement");
	m_fPlayerDamageValue						= lua_hadndler.GetGlobalNum("PlayerDamageValue");
	m_fPlayerDamageValueIncrement		= lua_hadndler.GetGlobalNum("PlayerDamageValueIncrement");
	m_fMonsterSpeed								= lua_hadndler.GetGlobalNum("MonsterSpeed");
	m_fMonsterSpeedIncrement				= lua_hadndler.GetGlobalNum("MonsterSpeedIncrement");
	m_fMonsterDamageValue					= lua_hadndler.GetGlobalNum("MonsterDamageValue");
	m_fMonsterDamageValueIncrement		= lua_hadndler.GetGlobalNum("MonsterDamageValueIncrement");
	m_fMonsterEmpiricalValue					= lua_hadndler.GetGlobalNum("MonsterEmpiricalValue");
	m_fMonsterEmpiricalValueIncrement	= lua_hadndler.GetGlobalNum("MonsterEmpiricalValueIncrement");
	m_fPlayerBloodReturnValue					= lua_hadndler.GetGlobalNum("PlayerBloodReturn");
	m_fPlayerMagicReturnValue					= lua_hadndler.GetGlobalNum("PlayerMagicReturn");
	m_fMonsterBloodReturnValue				= lua_hadndler.GetGlobalNum("MonsterBloodReturn");
	m_nMonsterMaxCount							= (int)lua_hadndler.GetGlobalNum("MonsterMaxCount");
	m_nEquipmentBloodMaxCount			= (int)lua_hadndler.GetGlobalNum("EquipmentBloodMaxCount");
	m_nEquipmentMagicMaxCount			= (int)lua_hadndler.GetGlobalNum("EquipmentMagicMaxCount");

	m_fEquipmentBloodReturnValue			= lua_hadndler.GetGlobalNum("EquipmentBloodReturnValue");
	m_fEquipmentMagicReturnValue			= lua_hadndler.GetGlobalNum("EquipmentMagicReturnValue");

	m_strEquipmentBloodPicName				= lua_hadndler.GetGlobalString("EquipmentBloodPicName");
	m_strEquipmentMagicPicName			=lua_hadndler.GetGlobalString("EquipmentMagicPicName");

	m_fPlayerPosition_X								= lua_hadndler.GetGlobalNum("PlayerPosition_X");
	m_fPlayerPosition_Y								= lua_hadndler.GetGlobalNum("PlayerPosition_Y");
	m_fBossPosition_X								= lua_hadndler.GetGlobalNum("BossPosition_X");
	m_fBossPosition_Y								= lua_hadndler.GetGlobalNum("BossPosition_Y");

	m_strSelfIndicatorFileName					= lua_hadndler.GetGlobalString("self_indicator");
	m_strUIFileName									= lua_hadndler.GetGlobalString("UI_FileName");
	m_strMap1FileName								= lua_hadndler.GetGlobalString("Map1_FileName");
	m_strMap2FileName								= lua_hadndler.GetGlobalString("Map2_FileName");
	m_strMap3FileName								= lua_hadndler.GetGlobalString("Map3_FileName");
	m_strMap4FileName								= lua_hadndler.GetGlobalString("Map4_FileName");
	m_fPortalPosition_X								= lua_hadndler.GetGlobalNum("PortalPosition_X");
	m_fPortalPosition_Y								= lua_hadndler.GetGlobalNum("PortalPosition_Y");

	m_strServerIP										= lua_hadndler.GetGlobalString("ServerIP");
	m_nServerPort										= (int)lua_hadndler.GetGlobalNum("Port");
	int temp												= (int)lua_hadndler.GetGlobalNum("NetworkMode");
	if (temp == 1)
	{
		m_bNetworkMode = true;
	}
	else
	{
		m_bNetworkMode = false;
	}

	return;
}

string& Config::GetRandomID()
{
	if (m_strPlayerID.size() == 0)
	{
		m_strPlayerID =  Util::GetRandomString(16);
	}

	return m_strPlayerID;
	
}

string& Config::GetPlayerActionConfigFile()
{
	return m_strPlayerActionConfigFile;
}

string& Config::GetMonsterActionConfigFile()
{
	return m_strMonsterActionConfigFile;
}

string& Config::GetSkillActionConfigFile()
{
	return m_strSkillActionConfigFile;
}


string& Config::GetRoleName()
{
	return m_strRoleName;
}

RPG_01_END