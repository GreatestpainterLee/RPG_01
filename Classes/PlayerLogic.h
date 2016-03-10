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
	//====================ҵ���߼����� begin=============================================

	void									PlayerProcess(Player* player,Monster* pMonster);																	// ��Ҵ���

	void									HandlePlayerRun(Player* player);															// ��������ܶ�

	void									HandlePlayerDie(Player* player);																// �����������

	void									HandlePlayerAttack(Player* player,Monster* pMonster);							// ������ҹ���

	void									HandlePlayerBeAttack(Player* player,Monster* pMonster);						// ��ұ�����

	void									HandlePlayerSkillAttack(Player* player,Skill* pSkill);									// ��Ҽ��ܹ���


	void									HandlePlayerUpgrade(Player* player);													// �������

	void									HandlePlayerBloodChange(Player* player,float fChangeValue);				// ���Ѫ���ı�
	void									HandlePlayerMagicChange(Player* player,float fChangeValue);				// ���ħ��ֵ�ı�
	void									HandlePlayerEmpiricalChange(Player* player,float fChangeValue);			// ��Ҿ���ֵ�ı�
	

	//====================ҵ���߼����� end=============================================

private:
	PlayerLogic();
	static PlayerLogic*			m_pInstance;

private:
};
RPG_01_END

#endif