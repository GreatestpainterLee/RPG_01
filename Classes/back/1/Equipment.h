#ifndef _EQUIPMENTMENT_H_
#define _EQUIPMENTMENT_H_

#include "define.h"
#include <cocos2d.h>
#include "Entity.h"
#include "./widget/ProgressView.h"
#include "Config.h"

/*
** 装备类：血瓶、魔瓶、武器等
*/
USING_NS_CC;
RPG_01_BEGIN
class Equipment:public Entity
{
public:
	bool init()
	{
		
		if (!Entity::init())
		{
			return false;
		}
		m_pBloodProgress->setVisible(false);
		return true;
	}
	CREATE_FUNC(Equipment);
	PROPERTY_INIT(int,EquipmentType,m_nEquipmentType);

	
protected:
	int					m_nEquipmentType;
};

class BloodEquipment:public Equipment
{
public:
	bool init()
	{
		if (!Equipment::init())
		{
			return false;
		}
		m_fReturnBlood = Game()->GetConfig()->GetEquipmentBloodReturnValue();
		m_nEquipmentType = EQUIPMENT_BLOOD;
		m_pSprite = Sprite::create(Game()->GetConfig()->GetEquipmentBloodPicName());
		addChild(m_pSprite);
		return true;
	}
	CREATE_FUNC(BloodEquipment);
	PROPERTY_INIT(float,ReturnBlood,m_fReturnBlood);
protected:
private:
	float					m_fReturnBlood;
};

class MagicEquipment:public Equipment
{
public:
	bool init()
	{
		if (!Equipment::init())
		{
			return false;
		}
		m_fReturnMagic = Game()->GetConfig()->GetEquipmentMagicReturnValue();
		m_nEquipmentType = EQUIPMENT_MAGIC;
		m_pSprite = Sprite::create(Game()->GetConfig()->GetEquipmentMagicPicName());
		addChild(m_pSprite);
		return true;
	}
	CREATE_FUNC(MagicEquipment);
	PROPERTY_INIT(float,ReturnMagic,m_fReturnMagic);
protected:
private:
	float					m_fReturnMagic;
};

RPG_01_END
#endif // !_EQUIPMENTMENT_H_
