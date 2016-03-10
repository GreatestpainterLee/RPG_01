#ifndef _TREASURE_MANAGER_H_
#define _TREASURE_MANAGER_H_

#include "define.h"
#include <cocos2d.h>
USING_NS_CC;

RPG_01_BEGIN
class Equipment;
class EquipmentManager
{
public:
	static EquipmentManager*			GetInstance();

	void												Process(float delt);

	void												DropoutBloodVial();				// 随机掉下血瓶

	void												DropoutMagicVial();				// 随机掉下魔法瓶

	void												CheckCollision();					// 碰撞检测

	void												RemoveAllEquipment();			// 移除地上所有的装备

	void												TestAnimation();
private:
	EquipmentManager()
	{
		m_nBloodVial = 0;
		m_nMagicVial = 0;
	}
	static EquipmentManager*			m_pInstance;

	int												m_nBloodVial;
	int												m_nMagicVial;

	vector<Equipment*>					m_EquipmentList;

};
RPG_01_END

#endif // !_TREASURE_MANAGER_H
