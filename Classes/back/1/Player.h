#ifndef _PLAER_H_
#define _PLAER_H_

#include "define.h"

#include "Entity.h"
#include "PlayerAction.h"
#include "Skill.h"

RPG_01_BEGIN

/*
** �����
*/
class Skill;
typedef Skill* PSkill;
class Player:public Entity
{
public:

	virtual bool init();

	CREATE_FUNC(Player);

	Player();

	~Player();

	void		Action(int action_type,int direction);												// ��Ҷ���

	void		AdjustPosition();																			// ����λ��

	void		Upgrade();																					// �������

	PROPERTY_INIT(float,Speed,m_fSpeed);													// 
	PROPERTY_INIT(Point,DestPoint,m_DestPoint);
	PROPERTY_INIT(float,MaxBloodValue,m_fMaxBloodValue);
	PROPERTY_INIT(float,MaxMagicValue,m_fMaxMagicValue);
	PROPERTY_INIT(float,MaxEmpiricalValue,m_fMaxEmpiricalValue);
	PROPERTY_INIT(int,Level,m_nLevel);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);
	PROPERTY_INIT(string,PlayerName,m_strPlayerName);
	PROPERTY_INIT(string,RoleName,m_strRoleName);
	PROPERTY_INIT(string,Password,m_strPassword);

	void		SetBloodValue(float v);
	float		GetBloodValue();

	void		SetMagicValue(float v);
	float		GetMagicValue();

	void		SetEmpiricalValue(float v);
	float		GetEmpiricalValue();

	void		SetDirection(int v);
	int		GetDirection();

	void		SetMsg(int type);
	int		GetMsg();

	int		GetMaxLevel();

	Skill*		GetSkill_Q();
	Skill*		GetSkill_W();
	Skill*		GetSkill_E();
	Skill*		GetSkill_R();

	void		SetCurrentSkill(Skill* pSkill);
	void		SetCurrentSkill(int nSkillID);
	Skill*		GetCurrentSkill();

	void		ShowBloodReturnAnimation();

private:
	string				m_strRoleName;									// Ӣ������
	string				m_strPlayerName;
	string				m_strPassword;

	float					m_fSpeed;											// �ٶȣ����ŵȼ���ߣ���Ӧ��ֵҲ������

	int					m_nDirection;										// �ƶ����ܶ��ķ���
	Point				m_DestPoint;										// �ƶ�ʱ��Ŀ�ĵ�
	int					m_nMessage;									// ��������

	int					m_nPreDirection;									// ǰһ���ƶ��ķ���
	int					m_nPreMessage;								// ǰһ����������

	float					m_fBloodValue;										// ��ǰѪ�������ŵȼ���ߣ���Ӧ��ֵҲ������
	float					m_fMaxBloodValue;

	float					m_fMagicValue;									// ��ǰħ���������ŵȼ���ߣ���Ӧ��ֵҲ������
	float					m_fMaxMagicValue;

	float					m_fEmpiricalValue;								// ��ǰ����ֵ��ÿ�������������
	float					m_fMaxEmpiricalValue;							// ÿһ���������ֵ��������ֵ�ﵽ���������ʱ��ͻ������������ŵȼ���ߣ���Ӧ��ֵҲ������

	int					m_nLevel;												// ��ǰ�ĵȼ�����ʼʱ����ҵĵȼ�Ϊ1
	static const int	m_nMaxLevel = 16;								// ��ҵ������

	float					m_fDamageValue;									// ��ҵ��˺�ֵ����������ʱ�Թ�����ɵ��˺������ŵȼ���ߣ���Ӧ��ֵҲ������

	Skill*					m_pSkill_Q ;											// Q���ļ���
	Skill*					m_pSkill_W;											// W���ļ���
	Skill*					m_pSkill_E;											// E���ļ���
	Skill*					m_pSkill_R;											// R���ļ���

	Skill*					m_pCurrentSkill;									// ��ҵ�ǰ��Ҫʩ�ŵļ���

	Skill*					m_pUpgradeSkill;									// ���������ʱ����ʾ����Ч

	Skill*					m_pBloodReturnSkill;							// ��ҳԵ�Ѫƿ��ʱ����ʾ��Ч
};

RPG_01_END
#endif