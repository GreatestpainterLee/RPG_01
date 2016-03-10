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
	//====================业务逻辑处理 begin=============================================

	void									HandleMonsterAttack(Monster* pMonster,Player* player);						// 处理怪物攻击

	void									HandleMonsterBeKilled(Monster* pMonster,Player* player);					// 怪物被杀死

	void									HandleMonsterBeAttack(Monster* pMonster,Player* player);					// 怪物被攻击
	void									HandleMonsterBloodChange(Monster* pMonster,float fChangeValue);			// 被选中怪物血量值改变

	//====================业务逻辑处理 end=============================================
private:
	MonsterLogic();

	static MonsterLogic*		m_pInstance;
};
RPG_01_END

#endif