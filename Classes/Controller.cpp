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
*  ��ȡ��Ϸ�߼�ʵ�����Ƕ�Controller::GetInstance()�ķ�װ
************************************************************************/
Controller*	Game()
{
	return Controller::GetInstance();
}


// Controller��ʵ��
Controller* Controller::m_pInstance = 0;

// ��ȡController��ʵ��
Controller* Controller::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new Controller;

		// ��ȡ������������Ŀ����������ù��캯����ɳ�ʼ���������ɸ���������
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
*  ��ȡ����������
************************************************************************/
SceneManager* Controller::GetSceneManager()
{
	return SceneManager::GetInstance();
}

/************************************************************************
*  ��ȡװ��������
************************************************************************/
EquipmentManager* Controller::GetEquipmentManager()
{
	return EquipmentManager::GetInstance();
}

/************************************************************************
*  ��ȡ���������
************************************************************************/
MonsterManager* Controller::GetMonsterManager()
{
	return MonsterManager::GetInstance();
}

/************************************************************************
*  ��ȡ���ܹ�����
************************************************************************/
SkillManager* Controller::GetSkillManager()
{
	return SkillManager::GetInstance();
}

/************************************************************************
*  ��ȡ·��������
************************************************************************/
PathManager* Controller::GetPathManager()
{
	return PathManager::GetInstance();
}

/************************************************************************
*  ��ȡ����
************************************************************************/
Config* Controller::GetConfig()
{
	return Config::GetInstance();
}


/************************************************************************
*  ��ȡAI
************************************************************************/
MonsterAI* Controller::GetMonsterAI()
{
	return MonsterAI::GetInstance();
}

/************************************************************************
*  ��ȡ����ģ��
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
*  ���캯��
************************************************************************/
Controller::Controller()
{
	m_pMyPlayer = 0;

	
}

Controller::~Controller()
{

}



/************************************************************************
*  ��ʼ������
************************************************************************/
void Controller::Init(const string& strID,const string& strPsd,bool bNetMode)
{
	m_pCurrentSelectedMonster	= 0;								// ��ǰ������Ҽ�ѡ�еĹ���

	m_nCurrentChapter					= CHAPTER_0;				// ��Ϸ������½�

	m_bLoopGame							= true;							// ��Ϸѭ����־

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
*  ��Ϸ������½�ת��
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
	// ���õ�ǰ�½ڵ�ID
	m_nCurrentChapter = nChapterID;

	

	// �������ֹͣ
	

	// ��ͣ��Ϸ
	SuspendGame();

	// �Ƴ���ͼ�����еĹ��� 
	Game()->GetMonsterManager()->RemoveAllMonster();					

	// �Ƴ���ͼ�����е�װ��
	Game()->GetEquipmentManager()->RemoveAllEquipment();			

	// ��ǰѡ�еĹ�����Ϊ��
	m_pCurrentSelectedMonster = 0;														

	// �½�һ��boss��ÿ���½ڵ�Boss����һ����
	m_pBoss = Game()->GetMonsterManager()->CreateBoss();				

	// ����ת��
	Game()->GetSceneManager()->ChangeScene(nChapterID);				

	// ������Ϸ
	ContinueGame();
}

/************************************************************************
*  ��ȡ��ǰ��Ϸ�����½�
************************************************************************/
int Controller::GetCurrentChapter()
{
	return m_nCurrentChapter;
}

/************************************************************************
*  ��ͣ��Ϸ
************************************************************************/
void Controller::SuspendGame()
{
	m_bLoopGame = false;
}

/************************************************************************
*  ������Ϸ
************************************************************************/
void Controller::StopGame()
{
}

/************************************************************************
*  ������Ϸ
************************************************************************/
void Controller::ContinueGame()
{
	m_bLoopGame = true;
}

/************************************************************************
*  �ж���Ϸ�Ƿ�������
************************************************************************/
bool Controller::IsRunning()
{
	return m_bLoopGame;
}

/************************************************************************
*  ������Ϸģʽ���������ǵ�����
************************************************************************/
void Controller::IsNetGame(bool v)
{
	m_bIsNetGame = v;
}


/************************************************************************
*  �ж��Ƿ�Ϊ������Ϸ
************************************************************************/
bool Controller::IsNetGame()
{
	return m_bIsNetGame;
}


/************************************************************************
*  ��ʼ��Ϸ��Ŀǰû���õ���
************************************************************************/
void Controller::StartGame()
{

}


/************************************************************************
*  ��������һ��¼�
************************************************************************/
void Controller::HandleRightClick(Point& destPoint)
{
	Player* myPlayer = GetMyPlayer();//GetPlayerManager()->GetPlayer(m_strMyPlayerID);

	// �����еĹ���ı�ѡ��״̬��Ϊδѡ��״̬
	Game()->GetMonsterManager()->UnSelectAllMonster();

	// �ж�����һ������Ƿ����һ�����������ھͷ��ظù����ָ�룬���򷵻ؿ�
	Monster* pMonster = Game()->GetMonsterManager()->GetMonster(destPoint);

	if (pMonster != 0)
	{
		m_pCurrentSelectedMonster = pMonster;
		// ���øù���Ϊ��ѡ��״̬
		pMonster->SetSelected(true);			
		// �ڹ���Ѫ��������ʾ�����Ѫ��
		MonsterLogic::GetInstance()->HandleMonsterBloodChange(pMonster,0);							
	}
	else
	{
		// ��չ���Ѫ�����Ϲ����Ѫ��
		Game()->GetSceneManager()->SetMonsterBloodProgress(0);
	}

	// ��ȡ��ҵ�ǰ�ĳ���
	int dir = Game()->GetPathManager()->GetDirection(myPlayer->getPosition(),destPoint);

	// ������ҵ�Ŀ�ĵص㣨���Ҫ�ƶ�������Ҽ����������
	myPlayer->SetDestPoint(destPoint);

	// ����ܶ�
	myPlayer->Action(CodeMsg::code_player_run,dir);

	GetNetworkModule()->SendPlayerState(myPlayer);
}

/************************************************************************
*  �����������¼�
************************************************************************/
void Controller::HandleLeftClick(Point& destPoint,Skill* pSkill)
{
}

/************************************************************************
*  ��õ�ǰ��ѡ�еĹ���
************************************************************************/
void Controller::SetCurrentSelectedMonster()
{
	// �õ�һ����������ѡ��Ĺ���
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
*  ��Ҿ���ֵ�ı�
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
*  ��Ϸ��ѭ��
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

	// ����������Թ�����е�һЩ����
	Game()->GetMonsterManager()->Process(delt);

	if (!m_bIsNetGame)
	{
		// �����AI����
		Game()->GetMonsterAI()->Process(delt);
	}

	vector<Player*> playerList = GetPlayerManager()->GetPlayerList();

	for (int i = 0 ;i < playerList.size(); ++i)
	{
		Player* player = playerList[i];

		// �������
		if (player->GetMsg() == CodeMsg::code_player_die)
		{
			PlayerLogic::GetInstance()->HandlePlayerDie(player);
			continue;;
		}

		// �������Ƿ��ڴ�������
		if (CheckPlayerIsInPortal())
		{
			return;
		}

		// ��һ�Ѫ
		PlayerLogic::GetInstance()->HandlePlayerBloodChange(player,Game()->GetConfig()->GetPlayerBloodReturnValue());

		// ��һ�ħ
		PlayerLogic::GetInstance()->HandlePlayerMagicChange(player,Game()->GetConfig()->GetPlayerMagicReturnValue());

		// װ����������װ�����е�һЩ����
		Game()->GetEquipmentManager()->Process(delt);

		// ���õ�ǰ��ѡ�еĹ�������еĻ���
		SetCurrentSelectedMonster();

		// ��Ҫ�����ҵĴ���
		PlayerLogic::GetInstance()->PlayerProcess(player,m_pCurrentSelectedMonster);
	}
	
}

RPG_01_END