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

	void												DropoutBloodVial();				// �������Ѫƿ

	void												DropoutMagicVial();				// �������ħ��ƿ

	void												CheckCollision();					// ��ײ���

	void												RemoveAllEquipment();			// �Ƴ��������е�װ��

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
