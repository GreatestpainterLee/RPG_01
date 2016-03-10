#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "define.h"
#include "Entity.h"

RPG_01_BEGIN

/*
** ������
*/
class Monster:public Entity
{
public:

	X_CREATE_FUNC(Monster);

	virtual bool init();

	Monster();

	~Monster();

	void		Reset();																					// ���ã�����������ʱ�򲢲�������ɾ�����ֻ�ǽ��������������Ⱥ��ʵ�ʱ�����ò��ٴ���ʾ��

	void		Upgrade();																			// ����

	void		Action(int action_type,int direction);										// �������Ϊ����

	void		Stop();																					// ֹͣ�������Ϊ����

	void		AdjustPosition();																	// ����λ��

	bool		IsSelected();																			// �жϹ����Ƿ�ѡ��


	PROPERTY_INIT(float,Speed,m_fSpeed);
	PROPERTY_INIT(Point,DestPoint,m_DestPoint);
	PROPERTY_INIT(float,EmpiricalValue,m_fEmpiricalValue);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);
	PROPERTY_INIT(string,MonsterName,m_strMonsterName);

	int		GetMonsterType();																// �������ͣ���ͨ�ֻ���Boss
	void		SetMonsterType(int type);														// ���ù�������

	void		SetDirection(int v)	;																// ���÷���
	int		GetDirection();																		// ��÷���

	void		SetMsg(int type);														// ���ö�������
	int		GetMsg();																	// ��ö�������

	void		SetBloodValue(float v);															// ����Ѫ��
	float		GetBloodValue();																	// ��ȡѪ��

	float		GetMaxBloodValue();															// ��ù�������Ѫ��
protected:
	int					m_nPreDirection;														// ǰһ���ƶ��ķ���
	int					m_nPreMessage;													// ǰһ������������
private:
	int					m_nMonsterType;
	string				m_strMonsterName;													// ��������֣����ڼ��ظ��ֲ������͵Ĺ���ͼƬ��Դ��
	float					m_fSpeed;																// �ٶ�
	int					m_nDirection;															// ����
	Point				m_DestPoint;															// ��������һϵ�ж����������ߡ��ܶ��ȣ�ʱ��Ŀ��λ��
	int					m_nMessage;														// ��������
	float					m_fBloodValue;															// ��ǰѪ��
	float					m_fMaxBloodValue;													// ���Ѫ�������ż�����������ֵҲ����������
	int					m_nLevel;																	// ��ǰ�ȼ�
	static const int m_nMaxLevel = 16;													// ���ȼ� 
	float					m_fEmpiricalValue;													// ��ֻ���ﱻɱ����ʱ���������õľ���ֵ
	float					m_fDamageValue;														// ���﹥����ҵ�ʱ������յ����˺�ֵ
};

RPG_01_END

#endif // !_MONSTER_H_
