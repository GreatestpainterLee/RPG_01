#ifndef _MONSTER_MANAGER_H_
#define _MONSTER_MANAGER_H_


#include <cocos2d.h>
USING_NS_CC;
#include "define.h"

RPG_01_BEGIN
class Monster;

/*
** 怪物管理类
*/
class MonsterManager
{
public:
	static MonsterManager*			GetInstance();

	~MonsterManager();

	void											Process(float delt);						// 怪物管理器的主逻辑

	void											CreateMonster();							// 随机产生一个怪物

	void											CleanDieMonster();						// 清理死亡的怪物

	void											RemoveAllMonster();						// 移除所有怪物

	vector<Monster*>&				GetMonsterList();							// 获取怪物的列表

	Monster*									GetMonster(Point point);				// 获取玩家选中区域的怪物（如果不存在就返回0）

	Monster*									GetASelectMonster();					// 获取一个选中的怪物

	void											UnSelectAllMonster();					// 将所有的怪物设置为未选择状态

	string										GetRandomMonsterName();			// 随机从名称映射表中获取一个名称

	Monster*									CreateBoss();									// 根据游戏的当前章节创建一个Boss

	void											MonsterBloodReturn();					// 怪物血量回复
private:
	MonsterManager();

	static MonsterManager*			m_pInstance;

	vector<Monster*>					m_MonsterList;									// 怪物列表

	map<int,string>						m_MonsterNameMap;						// 怪物名称映射表

	Monster*									m_pBoss;											// Boss

};
RPG_01_END
#endif // !_MONSTER_MANAGER_H_
