#include "Controller.h"
#include "Player.h"
#include "Util.h"
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
#include "MonsterLogic.h"
#include "PlayerLogic.h"
#include "PlayerManager.h"
#include "RecvDataLogic.h"

RPG_01_BEGIN

/************************************************************************
*  获取游戏逻辑实例，是对Controller::GetInstance()的封装
************************************************************************/
Controller*	Game()
{
	return Controller::GetInstance();
}


// Controller的实例
Controller* Controller::m_pInstance = 0;

// 获取Controller的实例
Controller* Controller::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new Controller;

		// 获取各个管理器的目的是让其调用构造函数完成初始化，即生成各个管理器
		m_pInstance->GetConfig();
		m_pInstance->GetEquipmentManager();
		m_pInstance->GetMonsterManager();
		m_pInstance->GetPathManager();
		m_pInstance->GetSceneManager();
		m_pInstance->GetSkillManager();
		m_pInstance->GetNetworkModule();
		m_pInstance->GetPlayerManager();
		m_pInstance->GetRecvDataLogic();

		m_pInstance->GetPlayerManager()->AddPlayer(m_pInstance->GetMyPlayer());

		m_pInstance->SetMyPlayerInfo(m_pInstance->GetConfig()->GetRandomID(),"");
	}

	return m_pInstance;
}

/************************************************************************
*  获取场景管理器
************************************************************************/
SceneManager* Controller::GetSceneManager()
{
	return SceneManager::GetInstance();
}

/************************************************************************
*  获取装备管理器
************************************************************************/
EquipmentManager* Controller::GetEquipmentManager()
{
	return EquipmentManager::GetInstance();
}

/************************************************************************
*  获取怪物管理器
************************************************************************/
MonsterManager* Controller::GetMonsterManager()
{
	return MonsterManager::GetInstance();
}

/************************************************************************
*  获取技能管理器
************************************************************************/
SkillManager* Controller::GetSkillManager()
{
	return SkillManager::GetInstance();
}

/************************************************************************
*  获取路径管理器
************************************************************************/
PathManager* Controller::GetPathManager()
{
	return PathManager::GetInstance();
}

/************************************************************************
*  获取配置
************************************************************************/
Config* Controller::GetConfig()
{
	return Config::GetInstance();
}


/************************************************************************
*  获取AI
************************************************************************/
MonsterAI* Controller::GetMonsterAI()
{
	return MonsterAI::GetInstance();
}

/************************************************************************
*  获取网络模块
************************************************************************/
NetworkModule* Controller::GetNetworkModule()
{
	return NetworkModule::GetInstance();
}


PlayerManager* Controller::GetPlayerManager()
{
	return PlayerManager::GetInstance();
}

MonsterLogic* Controller::GetMonsterLogic()
{
	return MonsterLogic::GetInstance();
}

PlayerLogic* Controller::GetPlayerLogic()
{
	return PlayerLogic::GetInstance();
}


RecvDataLogic* Controller::GetRecvDataLogic()
{
	return RecvDataLogic::GetInstance();
}
/************************************************************************
*  构造函数
************************************************************************/
Controller::Controller()
{
	m_pMyPlayer = 0;

	
}

Controller::~Controller()
{

}



/************************************************************************
*  初始化函数
************************************************************************/
void Controller::Init(const string& strID,const string& strPsd,bool bNetMode)
{
	m_pCurrentSelectedMonster	= 0;								// 当前用鼠标右键选中的怪物

	m_nCurrentChapter					= CHAPTER_0;				// 游戏剧情的章节

	m_bLoopGame							= true;							// 游戏循环标志

	m_bIsNetGame							= bNetMode;

	SetMyPlayerInfo(strID,strPsd);

	RPG_01::Game()->ChangeChapter(CHAPTER_1);

	if (m_bIsNetGame)
	{
		Game()->GetNetworkModule()->Born();

		Game()->GetNetworkModule()->RequestAllOnlinePlayer();
	}
}

/************************************************************************
*  游戏剧情的章节转换
************************************************************************/
void Controller::ChangeChapter(int nChapterID)
{
	if (nChapterID != CHAPTER_1 && nChapterID != CHAPTER_2 && nChapterID != CHAPTER_3 && nChapterID != CHAPTER_4)
	{
		return;
	}

	vector<Player*> playerList = Game()->GetPlayerManager()->GetPlayerList();
	if (m_nCurrentChapter != CHAPTER_0)
	{
		for (int i = 0; i < playerList.size(); ++i)
		{
			playerList[i]->Action(CodeMsg::code_player_static,right_direction);
		}
	}
	// 设置当前章节的ID
	m_nCurrentChapter = nChapterID;

	

	// 先让玩家停止
	

	// 暂停游戏
	SuspendGame();

	// 移除地图上所有的怪物 
	Game()->GetMonsterManager()->RemoveAllMonster();					

	// 移除地图上所有的装备
	Game()->GetEquipmentManager()->RemoveAllEquipment();			

	// 当前选中的怪物置为空
	m_pCurrentSelectedMonster = 0;														

	// 新建一个boss（每个章节的Boss都不一样）
	m_pBoss = Game()->GetMonsterManager()->CreateBoss();				

	// 场景转换
	Game()->GetSceneManager()->ChangeScene(nChapterID);				

	// 继续游戏
	ContinueGame();
}

/************************************************************************
*  获取当前游戏进度章节
************************************************************************/
int Controller::GetCurrentChapter()
{
	return m_nCurrentChapter;
}

/************************************************************************
*  暂停游戏
************************************************************************/
void Controller::SuspendGame()
{
	m_bLoopGame = false;
}

/************************************************************************
*  结束游戏
************************************************************************/
void Controller::StopGame()
{
}

/************************************************************************
*  继续游戏
************************************************************************/
void Controller::ContinueGame()
{
	m_bLoopGame = true;
}

/************************************************************************
*  判断游戏是否在运行
************************************************************************/
bool Controller::IsRunning()
{
	return m_bLoopGame;
}

/************************************************************************
*  设置游戏模式（联网还是单机）
************************************************************************/
void Controller::IsNetGame(bool v)
{
	m_bIsNetGame = v;
}


/************************************************************************
*  判断是否为联网游戏
************************************************************************/
bool Controller::IsNetGame()
{
	return m_bIsNetGame;
}


/************************************************************************
*  开始游戏（目前没有用到）
************************************************************************/
void Controller::StartGame()
{

}


/************************************************************************
*  处理鼠标右击事件
************************************************************************/
void Controller::HandleRightClick(Point& destPoint)
{
	Player* myPlayer = GetMyPlayer();//GetPlayerManager()->GetPlayer(m_strMyPlayerID);

	// 把所有的怪物的被选中状态置为未选择状态
	Game()->GetMonsterManager()->UnSelectAllMonster();

	// 判断鼠标右击区域是否存在一个怪物，如果存在就返回该怪物的指针，否则返回空
	Monster* pMonster = Game()->GetMonsterManager()->GetMonster(destPoint);

	if (pMonster != 0)
	{
		m_pCurrentSelectedMonster = pMonster;
		// 设置该怪物为被选中状态
		pMonster->SetSelected(true);			
		// 在怪物血条栏上显示怪物的血量
		MonsterLogic::GetInstance()->HandleMonsterBloodChange(pMonster,0);							
	}
	else
	{
		// 清空怪物血条栏上怪物的血量
		Game()->GetSceneManager()->SetMonsterBloodProgress(0);
	}

	// 获取玩家当前的朝向
	int dir = Game()->GetPathManager()->GetDirection(myPlayer->getPosition(),destPoint);

	// 设置玩家的目的地点（玩家要移动到鼠标右键点击的区域）
	myPlayer->SetDestPoint(destPoint);

	// 玩家跑动
	myPlayer->Action(CodeMsg::code_player_run,dir);

	GetNetworkModule()->SendPlayerState(myPlayer);
}

/************************************************************************
*  处理鼠标左击事件
************************************************************************/
void Controller::HandleLeftClick(Point& destPoint,Skill* pSkill)
{
}

/************************************************************************
*  获得当前被选中的怪物
************************************************************************/
void Controller::SetCurrentSelectedMonster()
{
	// 得到一个玩家用鼠标选择的怪物
	if (m_pCurrentSelectedMonster == 0)
	{
		m_pCurrentSelectedMonster = Game()->GetMonsterManager()->GetASelectMonster();
	}

	if (m_pCurrentSelectedMonster !=0 && m_pCurrentSelectedMonster->IsSelected() == false)
	{
		m_pCurrentSelectedMonster = Game()->GetMonsterManager()->GetASelectMonster();
	}
}

Monster* Controller::GetBoss()
{
	return m_pBoss;
}


Player* Controller::GetMyPlayer()
{
	if (m_pMyPlayer == 0)
	{
		m_strMyPlayerID = Game()->GetConfig()->GetRandomID();
		m_pMyPlayer = Player::create();
		m_pMyPlayer->SetID(m_strMyPlayerID);
		GetPlayerManager()->AddPlayer(m_pMyPlayer);
	}

	return m_pMyPlayer;
}

void Controller::SetMyPlayerInfo(const string& strID,const string& strPsd)
{
	m_strMyPlayerID = strID;
	m_pMyPlayer->SetID(m_strMyPlayerID);
	m_pMyPlayer->SetPassword(strPsd);

}


/************************************************************************
*  玩家经验值改变
************************************************************************/
bool Controller::CheckPlayerIsInPortal()
{
	Player* myPlayer = GetMyPlayer();//GetPlayerManager()->GetPlayer(m_strMyPlayerID);
	Point playerPosition = myPlayer->getPosition();
	if (GetCurrentChapter() != CHAPTER_4 && Game()->GetPathManager()->IsInRect(Game()->GetSkillManager()->GetPortalAnimation()->GetScope(),playerPosition))
	{
		if (GetCurrentChapter() == CHAPTER_1)
		{
			ChangeChapter(CHAPTER_2);
		}
		else if (GetCurrentChapter() == CHAPTER_2)
		{
			ChangeChapter(CHAPTER_3);
		}
		else if (GetCurrentChapter() == CHAPTER_3)
		{
			ChangeChapter(CHAPTER_4);
		}
		return true;
	}
	return false;
}

/************************************************************************
*  游戏主循环
************************************************************************/
void Controller::LoopGame(float delt)
{
	static int StaticTimeInterval = 0.0f;

	if(!m_bLoopGame)
	{
		return;
	}

	StaticTimeInterval += delt;

	if(m_bIsNetGame)
	{
		GameProtocol protocol;
		 if (Game()->GetNetworkModule()->TryReadPackage(protocol))
		 {
			 Game()->GetRecvDataLogic()->Process(protocol);
		 }
	}

	if (m_bIsNetGame && StaticTimeInterval > 0.5f)
	{
		GameProtocol protocol;
		GamePackage_Player* pl = protocol.AddPlayer();
		GetPlayerManager()->ConvertPlayer2Package(*GetPlayerManager()->GetPlayer(m_strMyPlayerID),*pl);
		protocol.SetMsgCode(CodeMsg::code_player_send_state);
		GetNetworkModule()->SendPackage(protocol);
		StaticTimeInterval = 0.0f;
	}

	// 怪物管理器对怪物进行的一些处理
	Game()->GetMonsterManager()->Process(delt);

	if (!m_bIsNetGame)
	{
		// 怪物的AI处理
		Game()->GetMonsterAI()->Process(delt);
	}

	vector<Player*> playerList = GetPlayerManager()->GetPlayerList();

	for (int i = 0 ;i < playerList.size(); ++i)
	{
		Player* player = playerList[i];

		// 玩家死亡
		if (player->GetMsg() == CodeMsg::code_player_die)
		{
			PlayerLogic::GetInstance()->HandlePlayerDie(player);
			continue;;
		}

		// 检测玩家是否在传送门中
		if (CheckPlayerIsInPortal())
		{
			return;
		}

		// 玩家回血
		PlayerLogic::GetInstance()->HandlePlayerBloodChange(player,Game()->GetConfig()->GetPlayerBloodReturnValue());

		// 玩家回魔
		PlayerLogic::GetInstance()->HandlePlayerMagicChange(player,Game()->GetConfig()->GetPlayerMagicReturnValue());

		// 装备管理器对装备进行的一些处理
		Game()->GetEquipmentManager()->Process(delt);

		// 设置当前被选中的怪物（假如有的话）
		SetCurrentSelectedMonster();

		// 主要针对玩家的处理
		PlayerLogic::GetInstance()->PlayerProcess(player,m_pCurrentSelectedMonster);
	}
	
}

RPG_01_END