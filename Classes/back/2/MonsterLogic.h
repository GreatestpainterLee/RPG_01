#ifndef _MONSTER_LOGIC_H_
#define _MONSTER_LOGIC_H_

#include <cocos2d.h>
#include "define.h"

USING_NS_CC;

RPG_01_BEGIN

class Skill;
class Player;
class Monster;
class Player;

class MonsterLogic
{
public:
	static MonsterLogic*		GetInstance();
	//====================ҵ���߼����� begin=============================================

	void									HandleMonsterAttack(Monster* pMonster,Player* player);						// ������﹥��

	void									HandleMonsterBeKilled(Monster* pMonster,Player* player);					// ���ﱻɱ��

	void									HandleMonsterBeAttack(Monster* pMonster,Player* player);					// ���ﱻ����
	void									HandleMonsterBloodChange(Monster* pMonster,float fChangeValue);			// ��ѡ�й���Ѫ��ֵ�ı�

	//====================ҵ���߼����� end=============================================
private:
	MonsterLogic();

	static MonsterLogic*		m_pInstance;
};
RPG_01_END

#endif