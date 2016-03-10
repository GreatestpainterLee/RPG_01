#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <vector>
#include <string>
using namespace std;


#define _USE_PC_

#include "../CommonClass/CodeMsg.h"
// �����
enum Direction
{
	static_direction,			// ��ֹ
	right_up_direction,		// ���Ͻ�
	right_direction,				// �ұ�
	right_down_direction,	// ���½�
	down_direction,			// �·�
	left_down_direction,		// ���·�
	left_direction,				// ���
	left_up_direction,			// ���Ϸ�
	up_direction,					// �Ϸ�
};

// ���������
enum MONSTER_TYPE
{
	MONSTER_NORMAL,													// ��ͨ����
	MONSTER_BOSS,															// ��boss
};

// װ������
enum EQUIPMENT_TYPE
{
	EQUIPMENT_BLOOD,													// Ѫƿ
	EQUIPMENT_MAGIC,													// ħƿ
	EQUIPMENT_WEAPON,												// ����
};

// ����ID
enum SCENE_ID
{
	INVALID_SCENE = -1,													// ��Ч����
	CHAPTER_1_SCENE,														// �½�1����
	CHAPTER_2_SCENE,														// �½�2����
	CHAPTER_3_SCENE,														// �½�3����
	CHAPTER_4_SCENE														// �½�4����
};

// �����ռ䶨��Ŀ�ʼ�ͽ���
#define RPG_01_BEGIN namespace RPG_01{
#define RPG_01_END }

enum CHAPTER_ID
{
	CHAPTER_0, // ��Ч�½�
	CHAPTER_1,
	CHAPTER_2,
	CHAPTER_3,
	CHAPTER_4,
};

enum SKILL_KEY
{
	SKILL_Q,
	SKILL_W,
	SKILL_E,
	SKILL_R,
};

enum SKILL_ID
{
	SKILL_INVALID_ID,
	SKILL_1_ID,
	SKILL_2_ID,
	SKILL_3_ID,
	SKILL_4_ID,
	SKILL_5_ID,
	SKILL_6_ID,
	SKILL_7_ID,
	SKILL_8_ID,

	SKILL_BLOOD_RETURN_ID,
	SKILL_PORTAL_ID,
};

// �����������Եķ��ʷ��������Լ��ٱ�д�ظ��Ĵ��룩
#ifndef PROPERTY_INIT
#define PROPERTY_INIT(xtype,xname,proper)\
	void	Set##xname(xtype val)\
{\
	proper = val;\
	}\
	xtype Get##xname()\
{\
	return proper;\
	}\

#endif

#ifndef IF_NULL_RETURN
#define IF_NULL_RETURN(pVal) \
	if (0 == pVal) {return;}
#endif

// ��������־
#define LEFT_MOUSE_BUTTON (0)

// ����Ҽ���־
#define RIGHT_MOUSE_BUTTON (1)


#endif // !_DEFINE_H_
