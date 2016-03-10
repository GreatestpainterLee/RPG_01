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
*  ��ʼ������
************************************************************************/
void MainLogic::Init()
{
	m_pPlayer									= Player::create();			// ����һ�����

	m_pCurrentSelectedMonster	= 0;								// ��ǰ������Ҽ�ѡ�еĹ���

	m_nCurrentChapter					= CHAPTER_1;				// ��Ϸ������½�

	m_bLoopGame							= true;							// ��Ϸѭ����־

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
*  ��Ϸ������½�ת��
************************************************************************/
void MainLogic::ChangeChapter(int nChapterID)
{
	if (nChapterID != CHAPTER_1 && nChapterID != CHAPTER_2 && nChapterID != CHAPTER_3 && nChapterID != CHAPTER_4)
	{
		return;
	}

	// ���õ�ǰ�½ڵ�ID
	m_nCurrentChapter = nChapterID;

	// �������ֹͣ
	GetMyPlayer()->Action(CodeMsg::code_player_static,right_direction);

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
int MainLogic::GetCurrentChapter()
{
	return m_nCurrentChapter;
}

/************************************************************************
*  ��ͣ��Ϸ
************************************************************************/
void MainLogic::SuspendGame()
{
	m_bLoopGame = false;
}

/************************************************************************
*  ������Ϸ
************************************************************************/
void MainLogic::StopGame()
{
}

/************************************************************************
*  ������Ϸ
************************************************************************/
void MainLogic::ContinueGame()
{
	m_bLoopGame = true;
}

/************************************************************************
*  �ж���Ϸ�Ƿ�������
************************************************************************/
bool MainLogic::IsRunning()
{
	return m_bLoopGame;
}

/************************************************************************
*  ������Ϸģʽ���������ǵ�����
************************************************************************/
void MainLogic::IsNetGame(bool v)
{
	m_bIsNetGame = v;
}


/************************************************************************
*  �ж��Ƿ�Ϊ������Ϸ
************************************************************************/
bool MainLogic::IsNetGame()
{
	return m_bIsNetGame;
}


/************************************************************************
*  ��ʼ��Ϸ��Ŀǰû���õ���
************************************************************************/
void MainLogic::StartGame()
{

}


/************************************************************************
*  ��������һ��¼�
************************************************************************/
void MainLogic::HandleRightClick(Point& destPoint)
{
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
	int dir = Game()->GetPathManager()->GetDirection(GetMyPlayer()->getPosition(),destPoint);

	// ������ҵ�Ŀ�ĵص㣨���Ҫ�ƶ�������Ҽ����������
	GetMyPlayer()->SetDestPoint(destPoint);

	// ����ܶ�
	GetMyPlayer()->Action(CodeMsg::code_player_run,dir);
}

/************************************************************************
*  �����������¼�
************************************************************************/
void MainLogic::HandleLeftClick(Point& destPoint,Skill* pSkill)
{
}

/************************************************************************
*  ��õ�ǰ��ѡ�еĹ���
************************************************************************/
void MainLogic::SetCurrentSelectedMonster()
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

Monster* MainLogic::GetBoss()
{
	return m_pBoss;
}


/************************************************************************
*  ��Ҿ���ֵ�ı�
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
*  ��Ϸ��ѭ��
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

		// ����������Թ�����е�һЩ����
		Game()->GetMonsterManager()->Process(delt);

		// �����AI����
		Game()->GetMonsterAI()->Process(delt);

		// �������
		if (GetMyPlayer()->GetMsg() == CodeMsg::code_player_die)
		{
			PlayerLogic::GetInstance()->HandlePlayerDie(m_pPlayer);
			return;
		}

		// �������Ƿ��ڴ�������
		if (CheckPlayerIsInPortal())
		{
			return;
		}

		// ��һ�Ѫ
		PlayerLogic::GetInstance()->HandlePlayerBloodChange(m_pPlayer,Game()->GetConfig()->GetPlayerBloodReturnValue());

		// ��һ�ħ
		PlayerLogic::GetInstance()->HandlePlayerMagicChange(m_pPlayer,Game()->GetConfig()->GetPlayerMagicReturnValue());

		// װ����������װ�����е�һЩ����
		Game()->GetEquipmentManager()->Process(delt);

		// ���õ�ǰ��ѡ�еĹ�������еĻ���
		SetCurrentSelectedMonster();

		// ��Ҫ�����ҵĴ���
		PlayerLogic::GetInstance()->PlayerProcess(m_pPlayer,m_pCurrentSelectedMonster);
	}
	else
	{
		// ����������Թ�����е�һЩ����
		Game()->GetMonsterManager()->Process(delt);

		// �����AI����
		Game()->GetMonsterAI()->Process(delt);

		// �������
		if (GetMyPlayer()->GetMsg() == CodeMsg::code_player_die)
		{
			PlayerLogic::GetInstance()->HandlePlayerDie(m_pPlayer);
			return;
		}

		// �������Ƿ��ڴ�������
		if (CheckPlayerIsInPortal())
		{
			return;
		}

		// ��һ�Ѫ
		PlayerLogic::GetInstance()->HandlePlayerBloodChange(m_pPlayer,Game()->GetConfig()->GetPlayerBloodReturnValue());

		// ��һ�ħ
		PlayerLogic::GetInstance()->HandlePlayerMagicChange(m_pPlayer,Game()->GetConfig()->GetPlayerMagicReturnValue());

		// װ����������װ�����е�һЩ����
		Game()->GetEquipmentManager()->Process(delt);

		// ���õ�ǰ��ѡ�еĹ�������еĻ���
		SetCurrentSelectedMonster();

		// ��Ҫ�����ҵĴ���
		PlayerLogic::GetInstance()->PlayerProcess(m_pPlayer,m_pCurrentSelectedMonster);
	}
}

void MainLogic::Handle(int nMessage)
{

}

RPG_01_END