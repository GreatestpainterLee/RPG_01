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
*  ����AI�����߼�����
************************************************************************/
void MonsterAI::Process(float delta)
{
	// ��ʱ
	static float fDelt = 0;

	fDelt += delta;

	vector<Player*> playerList = Game()->GetPlayerManager()->GetPlayerList();
	for (int i = 0; i < playerList.size(); ++i)
	{
		Player* player = playerList[i];


		// �������
		float propability  = Util::GetProbability();

		// ȡ����һ��Ӧ�ý��е�״̬
		int nextState = GetNextAction(propability);

		// �����б�
		vector<Monster*> monsterList = Game()->GetMonsterManager()->GetMonsterList();

		// �������б��������ȡһ������
		int index = Util::GetRandomNum(0,monsterList.size());

		Monster* pMonster = monsterList[index];

		// �����������Ѿ���������ô�������κδ���
		if (pMonster->GetBloodValue() <= 0 || pMonster->GetMsg() == CodeMsg::code_monster_die || pMonster->isVisible() == false)//
		{
			return;
		}

		// ��ȡ������ֵ����
		Rect scope = pMonster->GetScope();

		// ȡ����ҵ�λ��
		Point playerPoint = player->getPosition();

		// �ж�����Ƿ������ֵ������
		// �����Ҳ��ڹ���������
		if (!Game()->GetPathManager()->IsInRect(scope,playerPoint))
		{
			MonsterAutoRun(pMonster,fDelt);
		}
		// �����������ֵ������
		else
		{
			if (player->GetMsg() == CodeMsg::code_player_die)
			{
				return;
			}

			// ��50%�ĸ��ʷ�������
			if (Util::GetProbability() > 0.5)
			{
				// ���﷢������
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
*  �����Զ��ƶ�
************************************************************************/
void MonsterAI::MonsterAutoRun(Monster* pMonster,float fDelt)
{
	// ������������ƶ�
	if (pMonster->GetMsg() == CodeMsg::code_monster_run)
	{
		// ���������λ��
		pMonster->AdjustPosition();

		// �������������Ѿ�����Ŀ�ĵأ���ֹͣ
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

	// ������ﲻ�����ƶ�����ô�������ƶ�

	// ���ȼ�������Ŀ�ĵأ��Ȼ�ȡ����ĵ�ǰ������Ϊ�����Ŀ�ĵأ�
	Point destPoint = pMonster->getPosition();

	// ��ù���ķ��򣨰��չ����ԭ����������ƶ���
	int dir = pMonster->GetDirection();

	// ÿʮ���ӵ���һ�η���
	if (fDelt > Game()->GetConfig()->GetProcessInterval())
	{
		dir = GetNextDirection(pMonster->GetDirection());
	}

	// ���������Ŀ�ĵ�
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