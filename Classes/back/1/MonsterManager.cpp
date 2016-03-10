#include "MonsterManager.h"
#include "Monster.h"
#include "Controller.h"
#include "SceneManager.h"
#include "Util.h"
#include "./scene/BaseScene.h"
#include "PathManager.h"
#include "Config.h"
#include "MainLogic.h"
#include "MonsterLogic.h"

RPG_01_BEGIN
MonsterManager* MonsterManager::m_pInstance = 0;

MonsterManager* MonsterManager::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new MonsterManager;
	}

	return m_pInstance;
}


MonsterManager::MonsterManager()
{

}

MonsterManager::~MonsterManager()
{

}

/************************************************************************
*  妖怪管理器主逻辑
************************************************************************/
void MonsterManager::Process(float delt)
{
	static float fDelt = 0;
	fDelt += delt;
	if (fDelt >= Game()->GetConfig()->GetProcessInterval() )
	{
		// 清理死亡怪物的尸体
		CleanDieMonster();
	}

	// 随机产生怪物
	if (Util::GetProbability() > 0.9)
	{
		Game()->GetMonsterManager()->CreateMonster();
	}

	MonsterBloodReturn();

	Game()->GetMonsterLogic()->HandleMonsterBloodChange(Game()->GetCurrentSelectedMonster(),0);

	if (fDelt >= Game()->GetConfig()->GetProcessInterval())
	{
		fDelt = 0;
	}
}

/************************************************************************
*  怪物回血
************************************************************************/
void MonsterManager::MonsterBloodReturn()
{	
	for (int i = 0; i < m_MonsterList.size(); ++i)
	{
		Monster* pMonster = m_MonsterList[i];

		if (pMonster->isVisible() == false || pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die)
		{
			continue;
		}

		if (pMonster->GetBloodValue() >= pMonster->GetMaxBloodValue())
		{
			continue;
		}

		pMonster->SetBloodValue(pMonster->GetBloodValue() + Game()->GetConfig()->GetMonsterBloodReturnValue());
	}
}

/************************************************************************
*  创建怪物
************************************************************************/
void MonsterManager::CreateMonster()
{
	if (m_MonsterList.size() >= Game()->GetConfig()->GetMonsterMaxCount())
	{
		for (int i = 0; i < m_MonsterList.size(); ++i)
		{
			Monster* pMonster = 0;

			pMonster = m_MonsterList[i];

			if (pMonster->GetMonsterType() == MONSTER_BOSS)
			{
				continue;
			}

			if (pMonster->isVisible() == false)
			{
				pMonster->setPosition(Game()->GetPathManager()->GetRandomPoint(Point(50,50),Point(800,600)));
				pMonster->Reset();
				pMonster->setVisible(true);
				pMonster->Action(CodeMsg::code_monster_static,Game()->GetPathManager()->GetRandomDirection());
				break;
			}
		}
		return;
	}

	Monster* pMonster = Monster::create();
	if (Game()->GetCurrentChapter() == CHAPTER_1)
	{
		pMonster->SetMonsterName("monster1");
	}

	if (Game()->GetCurrentChapter() == CHAPTER_2)
	{
		pMonster->SetMonsterName("monster2");
	}

	if (Game()->GetCurrentChapter() == CHAPTER_3)
	{
		pMonster->SetMonsterName("monster3");
	}

	if (Game()->GetCurrentChapter() == CHAPTER_4)
	{
		pMonster->SetMonsterName("monster4");
	}
	
	m_MonsterList.push_back(pMonster);
	Layer* pScene = Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer();
	
	Point point = Game()->GetPathManager()->GetRandomPoint(Point(50,50),Point(800,600));
	
	pMonster->setPosition(point);

	pScene->addChild(pMonster);

	Rect rect = pMonster->GetScope();

	int direction = Game()->GetPathManager()->GetRandomDirection();
	
	pMonster->SetDestPoint(point);
	pMonster->Action(CodeMsg::code_monster_static,direction);
}

/************************************************************************
*  创建Boss
************************************************************************/
Monster* MonsterManager::CreateBoss()
{
	m_pBoss = Monster::create();
	if (Game()->GetCurrentChapter() == CHAPTER_1)
	{
		m_pBoss->SetMonsterName("monster1");
	}

	if (Game()->GetCurrentChapter() == CHAPTER_2)
	{
		m_pBoss->SetMonsterName("monster2");
	}

	if (Game()->GetCurrentChapter() == CHAPTER_3)
	{
		m_pBoss->SetMonsterName("monster3");
	}

	if (Game()->GetCurrentChapter() == CHAPTER_4)
	{
		m_pBoss->SetMonsterName("monster4");
	}

	m_pBoss->SetMonsterType(MONSTER_BOSS);

	m_MonsterList.push_back(m_pBoss);

	return m_pBoss;
}

/************************************************************************
*  移除所有怪物
************************************************************************/
void MonsterManager::RemoveAllMonster()
{
	m_MonsterList.clear();
}

/************************************************************************
*  清理死亡怪物
************************************************************************/
void MonsterManager::CleanDieMonster()
{
	for (int i = 0; i < m_MonsterList.size(); ++i)
	{
		Monster* pMonster = 0;

		pMonster = m_MonsterList[i];

		if (pMonster->isVisible() && (pMonster->GetBloodValue() <= 0.1 || pMonster->GetMsg() == CodeMsg::code_monster_die))//7
		{
			pMonster->setVisible(false);
		}
	}
}

/************************************************************************
*  得到怪物列表
************************************************************************/
vector<Monster*>& MonsterManager::GetMonsterList()
{
	return m_MonsterList;
}

/************************************************************************
*  将所有怪物的被选中状态设置为未被选中
************************************************************************/
void MonsterManager::UnSelectAllMonster()
{
	for (int i = 0; i < m_MonsterList.size(); ++i)
	{
		Monster* pMonster = 0;

		pMonster = m_MonsterList[i];

		pMonster->SetSelected(false);
	}
}

/************************************************************************
*  随机获取一个名字
************************************************************************/
string MonsterManager::GetRandomMonsterName()
{
	static int x = 0;
	if (x == 0)
	{
		m_MonsterNameMap.insert(make_pair(1,"monster1"));
		m_MonsterNameMap.insert(make_pair(2,"monster2"));
		m_MonsterNameMap.insert(make_pair(3,"monster3"));
		m_MonsterNameMap.insert(make_pair(4,"monster4"));
		x = 1;
	}

	int num = Util::GetRandomNum(1,5);
	map<int,string>::iterator it;
	it = m_MonsterNameMap.find(num);
	if (it == m_MonsterNameMap.end())
	{
		return "";
	}

	return it->second;

}

/************************************************************************
*  得到point坐标处的怪物
************************************************************************/
Monster* MonsterManager::GetMonster(Point point)
{
	for (int i = 0; i < m_MonsterList.size(); ++i)
	{
		Monster* pMonster = 0;

		pMonster = m_MonsterList[i];

		if (pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die || pMonster->isVisible() == false)
		{
			continue;
		}

		Rect rect = pMonster->GetScope();

		if (Game()->GetPathManager()->IsInRect(rect,point))
		{
			return pMonster;
			break;
		}
	}
	return 0;
}

/************************************************************************
*  得到一个被选中的怪物
************************************************************************/
Monster* MonsterManager::GetASelectMonster()
{
	for (int i = 0; i < m_MonsterList.size(); ++i)
	{
		Monster* pMonster = 0;

		pMonster = m_MonsterList[i];

		if (pMonster->IsSelected())
		{
			return pMonster;
		}
	}

	return 0;
}
RPG_01_END