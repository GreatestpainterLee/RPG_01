#include "MonsterAI.h"
#include "Monster.h"
#include "Util.h"
#include "MonsterManager.h"
#include "PathManager.h"
#include "Player.h"
#include "Controller.h"
#include "Config.h"
#include "MainLogic.h"
#include "PlayerLogic.h"
#include "MonsterLogic.h"
#include "PlayerManager.h"

RPG_01_BEGIN

MonsterAI* MonsterAI::m_pInstance = 0;

MonsterAI* MonsterAI::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new MonsterAI;
	}

	return m_pInstance;
}

/************************************************************************
*  妖怪AI的主逻辑处理
************************************************************************/
void MonsterAI::Process(float delta)
{
	// 计时
	static float fDelt = 0;

	fDelt += delta;

	vector<Player*> playerList = Game()->GetPlayerManager()->GetPlayerList();
	for (int i = 0; i < playerList.size(); ++i)
	{
		Player* player = playerList[i];


		// 计算概率
		float propability  = Util::GetProbability();

		// 取得下一个应该进行的状态
		int nextState = GetNextAction(propability);

		// 妖怪列表
		vector<Monster*> monsterList = Game()->GetMonsterManager()->GetMonsterList();

		// 从妖怪列表中随机抽取一个妖怪
		int index = Util::GetRandomNum(0,monsterList.size());

		Monster* pMonster = monsterList[index];

		// 如果这个妖怪已经死亡，那么不进行任何处理
		if (pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die || pMonster->isVisible() == false)//
		{
			return;
		}

		// 获取这个妖怪的领地
		Rect scope = pMonster->GetScope();

		// 取得玩家的位置
		Point playerPoint = player->getPosition();

		// 判断玩家是否在妖怪的领地内
		// 如果玩家不在怪物的领地内
		if (!Game()->GetPathManager()->IsInRect(scope,playerPoint))
		{
			MonsterAutoRun(pMonster,fDelt);
		}
		// 如果玩家在妖怪的领地内
		else
		{
			if (player->GetMsg() == CodeMsg::code_player_die)
			{
				return;
			}

			// 由50%的概率发动攻击
			if (Util::GetProbability() > 0.5)
			{
				// 怪物发动攻击
				if (pMonster->GetMsg() != CodeMsg::code_monster_attack)
				{
					pMonster->Action(CodeMsg::code_monster_attack,pMonster->GetDirection());
					Game()->GetMonsterLogic()->HandleMonsterAttack(pMonster,player);
					Game()->GetPlayerLogic()->HandlePlayerBeAttack(player,pMonster);
				}
			}
			else
			{
				if (pMonster->GetMsg() != CodeMsg::code_monster_attack)
				{
					pMonster->Action(CodeMsg::code_monster_static,pMonster->GetDirection());
				}
				MonsterAutoRun(pMonster,fDelt);
			}

		}

		if (fDelt >= Game()->GetConfig()->GetProcessInterval())
		{
			fDelt = 0;
		}
	}

	

}

/************************************************************************
*  妖怪自动移动
************************************************************************/
void MonsterAI::MonsterAutoRun(Monster* pMonster,float fDelt)
{
	// 如果怪物正在移动
	if (pMonster->GetMsg() == CodeMsg::code_monster_run)
	{
		// 调整怪物的位置
		pMonster->AdjustPosition();

		// 如果怪物的坐标已经到达目的地，就停止
		if (pMonster->getPosition().equals(pMonster->GetDestPoint()))
		{
			pMonster->Action(CodeMsg::code_monster_static,pMonster->GetDirection());
		}

		return;
	}

	if (Util::GetProbability() > 0.95)
	{
		return;
	}

	// 如果怪物不是在移动，那么就让他移动

	// 首先计算怪物的目的地（先获取怪物的当前坐标作为怪物的目的地）
	Point destPoint = pMonster->getPosition();

	// 获得怪物的方向（按照怪物的原来方向进行移动）
	int dir = pMonster->GetDirection();

	// 每十秒钟调整一次方向
	if (fDelt > Game()->GetConfig()->GetProcessInterval())
	{
		dir = GetNextDirection(pMonster->GetDirection());
	}

	// 调整怪物的目的地
	if (dir == right_up_direction)
	{
		destPoint.x += 50;
		destPoint.y += 50;
	}

	if (dir == right_direction)
	{
		destPoint.x += 50;
	}

	if (dir == right_down_direction)
	{
		destPoint.x += 50;
		destPoint.y -= 50;
	}

	if (dir == down_direction)
	{
		destPoint.y -= 50;
	}

	if (destPoint.x > 960 || destPoint.y > 640)
	{
		if (destPoint.x > 960)
		{
			destPoint.x = 0;
		}

		if (destPoint.y > 640)
		{
			destPoint.y = 0;
		}

		pMonster->setPosition(destPoint);

		return;
	}
	pMonster->SetDestPoint(destPoint);
	pMonster->Action(CodeMsg::code_monster_run,dir);
}

int MonsterAI::GetNextAction(float f)
{
	if (f < 0.45)
	{
		return CodeMsg::code_monster_attack;
	}

	if (f >= 0.45 && f < 0.5)
	{
		return CodeMsg::code_monster_static;
	}

	if (f >= 0.5 && f < 0.75)
	{
		return CodeMsg::code_monster_bellow;
	}

	if (f >= 0.75 && f <=1.0)
	{
		return CodeMsg::code_monster_run;
	}
}

int MonsterAI::GetNextDirection(int dir)
{
	if (dir == right_up_direction)
	{
		return right_direction;
	}

	if (dir == right_direction)
	{
		return right_down_direction;
	}

	if (dir == right_down_direction)
	{
		return down_direction;
	}

	if (dir == down_direction)
	{
		return right_up_direction;
	}
}
RPG_01_END