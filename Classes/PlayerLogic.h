#ifndef _PLAYER_LOGIC_H_
#define _PLAYER_LOGIC_H_

#include <cocos2d.h>
#include "define.h"

USING_NS_CC;

RPG_01_BEGIN

class Skill;
class Player;
class Monster;

class PlayerLogic
{
public:
	static PlayerLogic*			GetInstance();
	//====================业务逻辑处理 begin=============================================

	void									PlayerProcess(Player* player,Monster* pMonster);																	// 玩家处理

	void									HandlePlayerRun(Player* player);															// 处理玩家跑动

	void									HandlePlayerDie(Player* player);																// 处理玩家死亡

	void									HandlePlayerAttack(Player* player,Monster* pMonster);							// 处理玩家攻击

	void									HandlePlayerBeAttack(Player* player,Monster* pMonster);						// 玩家被攻击

	void									HandlePlayerSkillAttack(Player* player,Skill* pSkill);									// 玩家技能攻击


	void									HandlePlayerUpgrade(Player* player);													// 玩家升级

	void									HandlePlayerBloodChange(Player* player,float fChangeValue);				// 玩家血量改变
	void									HandlePlayerMagicChange(Player* player,float fChangeValue);				// 玩家魔法值改变
	void									HandlePlayerEmpiricalChange(Player* player,float fChangeValue);			// 玩家经验值改变
	

	//====================业务逻辑处理 end=============================================

private:
	PlayerLogic();
	static PlayerLogic*			m_pInstance;

private:
};
RPG_01_END

#endif