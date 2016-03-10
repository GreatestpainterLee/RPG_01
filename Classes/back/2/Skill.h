#ifndef _SKILL_H_
#define _SKILL_H_

#include "define.h"
#include "Entity.h"

RPG_01_BEGIN
/*
** �����ࣨ������Ч�ࣩ��
*/
class Skill:public Entity
{
public:

	X_CREATE_FUNC(Skill);
	Skill();
	~Skill();

	bool								init();

	PROPERTY_INIT(int,SkillID,m_nSkillID);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);

	void								Action(int nSkillID);									// ���ܵ�ʩ�Ŷ���Ч��
	void								Upgrade();												// ����������������ʹ�˺�ֵ���ߣ���ī������

	PROPERTY_INIT(float,ConsumeMagic,m_fDamageValue);
private:
	int								m_nSkillID;												// ���ܵ�ID��Ψһ�ı�־һ�ּ���
	float								m_fDamageValue;										// ʩ�Ÿü��ܣ��ܸ�������ɶ����˺�
	float								m_fConsumeMagic;									// ʩ��һ�μ���Ҫ���ĵ�ħ����
	int								m_nLevel;													// ���ܵĵ�ǰ�ȼ�
	static const int				m_nMaxLevel = 4;									// ���ܵ����ȼ�
};
RPG_01_END

#endif