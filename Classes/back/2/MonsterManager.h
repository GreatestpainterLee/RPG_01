#ifndef _MONSTER_MANAGER_H_
#define _MONSTER_MANAGER_H_


#include <cocos2d.h>
USING_NS_CC;
#include "define.h"

RPG_01_BEGIN
class Monster;

/*
** ���������
*/
class MonsterManager
{
public:
	static MonsterManager*			GetInstance();

	~MonsterManager();

	void											Process(float delt);						// ��������������߼�

	void											CreateMonster();							// �������һ������

	void											CleanDieMonster();						// ���������Ĺ���

	void											RemoveAllMonster();						// �Ƴ����й���

	vector<Monster*>&				GetMonsterList();							// ��ȡ������б�

	Monster*									GetMonster(Point point);				// ��ȡ���ѡ������Ĺ����������ھͷ���0��

	Monster*									GetASelectMonster();					// ��ȡһ��ѡ�еĹ���

	void											UnSelectAllMonster();					// �����еĹ�������Ϊδѡ��״̬

	string										GetRandomMonsterName();			// ���������ӳ����л�ȡһ������

	Monster*									CreateBoss();									// ������Ϸ�ĵ�ǰ�½ڴ���һ��Boss

	void											MonsterBloodReturn();					// ����Ѫ���ظ�
private:
	MonsterManager();

	static MonsterManager*			m_pInstance;

	vector<Monster*>					m_MonsterList;									// �����б�

	map<int,string>						m_MonsterNameMap;						// ��������ӳ���

	Monster*									m_pBoss;											// Boss

};
RPG_01_END
#endif // !_MONSTER_MANAGER_H_
