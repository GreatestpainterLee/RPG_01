#include "MainLogic.h"

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
#include "MainLogic.h"
#include "PlayerLogic.h"
#include "MonsterLogic.h"
#include "Player.h"

RPG_01_BEGIN
MainLogic* MainLogic::m_pInstance = 0;

MainLogic* MainLogic::GetInstance()
{
	if (0 == m_pInstance)
	{
		m_pInstance = new MainLogic;
	}

	return m_pInstance;
}




/************************************************************************
*  初始化函数
************************************************************************/
void MainLogic::Init()
{
	m_pPlayer									= Player::create();			// 创建一个玩家

	m_pCurrentSelectedMonster	= 0;								// 当前用鼠标右键选中的怪物

	m_nCurrentChapter					= CHAPTER_1;				// 游戏剧情的章节

	m_bLoopGame							= true;							// 游戏循环标志

	m_bIsNetGame							= Game()->GetConfig()->IsNetworkMode();

	Game()->GetNetworkModule()->ConnectToServer(Game()->GetConfig()->GetServerIP().c_str(),Game()->GetConfig()->GetServerPort());

	Game()->GetNetworkModule()->Born();

	string str = Game()->GetConfig()->GetRandomID();
	CCLOG(str.c_str());
	m_pPlayer->SetPlayerID(str);

}

Player* MainLogic::GetMyPlayer()
{
	return m_pPlayer;
}

Player* MainLogic::GetPlayer(const string& strID)
{
	for (int i = 0; i < m_PlayerList.size(); ++i)
	{
		if (0 == strcmp(strID.c_str(),m_PlayerList[i]->GetPlayerID().c_str()))
		{
			return m_PlayerList[i];
		}
	}
	return 0;
}

void MainLogic::AddPlayer(Player* player)
{
	if (m_PlayerList.size() == MaxPlayerNum)
	{
		return;
	}
	m_PlayerList.push_back(player);
}

void MainLogic::NewPlayer(const string& strID)
{
	Player* play = Player::create();
	play->SetPlayerID(strID);

	Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer()->addChild(play);

	play->setPosition(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	play->SetDestPoint(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	play->SetDirection(right_direction);


	play->Action(CodeMsg::code_player_static,right_direction);

	AddPlayer(play);
}

void MainLogic::DeletePlayer(Player* player)
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

void MainLogic::DeletePlayer(const string& strID)
{
	vector<Player*>::iterator it;
	for (it = m_PlayerList.begin(); it != m_PlayerList.end(); ++it)
	{
		if (0 == strcmp((*it)->GetPlayerID().c_str() ,strID.c_str()))
		{
			delete (*it);
			m_PlayerList.erase(it);
			break;
		}
	}
}

/************************************************************************
*  游戏剧情的章节转换
************************************************************************/
void MainLogic::ChangeChapter(int nChapterID)
{
	if (nChapterID != CHAPTER_1 && nChapterID != CHAPTER_2 && nChapterID != CHAPTER_3 && nChapterID != CHAPTER_4)
	{
		return;
	}

	// 设置当前章节的ID
	m_nCurrentChapter = nChapterID;

	// 先让玩家停止
	GetMyPlayer()->Action(CodeMsg::code_player_static,right_direction);

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
int MainLogic::GetCurrentChapter()
{
	return m_nCurrentChapter;
}

/************************************************************************
*  暂停游戏
************************************************************************/
void MainLogic::SuspendGame()
{
	m_bLoopGame = false;
}

/************************************************************************
*  结束游戏
************************************************************************/
void MainLogic::StopGame()
{
}

/************************************************************************
*  继续游戏
************************************************************************/
void MainLogic::ContinueGame()
{
	m_bLoopGame = true;
}

/************************************************************************
*  判断游戏是否在运行
************************************************************************/
bool MainLogic::IsRunning()
{
	return m_bLoopGame;
}

/************************************************************************
*  设置游戏模式（联网还是单机）
************************************************************************/
void MainLogic::IsNetGame(bool v)
{
	m_bIsNetGame = v;
}


/************************************************************************
*  判断是否为联网游戏
************************************************************************/
bool MainLogic::IsNetGame()
{
	return m_bIsNetGame;
}


/************************************************************************
*  开始游戏（目前没有用到）
************************************************************************/
void MainLogic::StartGame()
{

}


/************************************************************************
*  处理鼠标右击事件
************************************************************************/
void MainLogic::HandleRightClick(Point& destPoint)
{
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
	int dir = Game()->GetPathManager()->GetDirection(GetMyPlayer()->getPosition(),destPoint);

	// 设置玩家的目的地点（玩家要移动到鼠标右键点击的区域）
	GetMyPlayer()->SetDestPoint(destPoint);

	// 玩家跑动
	GetMyPlayer()->Action(CodeMsg::code_player_run,dir);
}

/************************************************************************
*  处理鼠标左击事件
************************************************************************/
void MainLogic::HandleLeftClick(Point& destPoint,Skill* pSkill)
{
}

/************************************************************************
*  获得当前被选中的怪物
************************************************************************/
void MainLogic::SetCurrentSelectedMonster()
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

Monster* MainLogic::GetBoss()
{
	return m_pBoss;
}


/************************************************************************
*  玩家经验值改变
************************************************************************/
bool MainLogic::CheckPlayerIsInPortal()
{
	Point playerPosition = GetMyPlayer()->getPosition();
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
void MainLogic::LoopGame(float delt)
{
	if(!m_bLoopGame)
	{
		return;
	}

	PackageHead head;
	GamePackage pack;

	if (m_bIsNetGame)
	{
		if(Game()->GetNetworkModule()->TryReadPackage(head,pack))
		{
			if (head.GetMsgCode() == CodeMsg::code_player_born)
			{
				NewPlayer("000");
			}
		}

		// 怪物管理器对怪物进行的一些处理
		Game()->GetMonsterManager()->Process(delt);

		// 怪物的AI处理
		Game()->GetMonsterAI()->Process(delt);

		// 玩家死亡
		if (GetMyPlayer()->GetMsg() == CodeMsg::code_player_die)
		{
			PlayerLogic::GetInstance()->HandlePlayerDie(m_pPlayer);
			return;
		}

		// 检测玩家是否在传送门中
		if (CheckPlayerIsInPortal())
		{
			return;
		}

		// 玩家回血
		PlayerLogic::GetInstance()->HandlePlayerBloodChange(m_pPlayer,Game()->GetConfig()->GetPlayerBloodReturnValue());

		// 玩家回魔
		PlayerLogic::GetInstance()->HandlePlayerMagicChange(m_pPlayer,Game()->GetConfig()->GetPlayerMagicReturnValue());

		// 装备管理器对装备进行的一些处理
		Game()->GetEquipmentManager()->Process(delt);

		// 设置当前被选中的怪物（假如有的话）
		SetCurrentSelectedMonster();

		// 主要针对玩家的处理
		PlayerLogic::GetInstance()->PlayerProcess(m_pPlayer,m_pCurrentSelectedMonster);
	}
	else
	{
		// 怪物管理器对怪物进行的一些处理
		Game()->GetMonsterManager()->Process(delt);

		// 怪物的AI处理
		Game()->GetMonsterAI()->Process(delt);

		// 玩家死亡
		if (GetMyPlayer()->GetMsg() == CodeMsg::code_player_die)
		{
			PlayerLogic::GetInstance()->HandlePlayerDie(m_pPlayer);
			return;
		}

		// 检测玩家是否在传送门中
		if (CheckPlayerIsInPortal())
		{
			return;
		}

		// 玩家回血
		PlayerLogic::GetInstance()->HandlePlayerBloodChange(m_pPlayer,Game()->GetConfig()->GetPlayerBloodReturnValue());

		// 玩家回魔
		PlayerLogic::GetInstance()->HandlePlayerMagicChange(m_pPlayer,Game()->GetConfig()->GetPlayerMagicReturnValue());

		// 装备管理器对装备进行的一些处理
		Game()->GetEquipmentManager()->Process(delt);

		// 设置当前被选中的怪物（假如有的话）
		SetCurrentSelectedMonster();

		// 主要针对玩家的处理
		PlayerLogic::GetInstance()->PlayerProcess(m_pPlayer,m_pCurrentSelectedMonster);
	}
}

void MainLogic::Handle(int nMessage)
{

}

RPG_01_END