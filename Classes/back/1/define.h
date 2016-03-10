#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <vector>
#include <string>
using namespace std;


#define _USE_PC_

#include "../CommonClass/CodeMsg.h"
// 方向宏
enum Direction
{
	static_direction,			// 静止
	right_up_direction,		// 右上角
	right_direction,				// 右边
	right_down_direction,	// 右下角
	down_direction,			// 下方
	left_down_direction,		// 左下方
	left_direction,				// 左边
	left_up_direction,			// 左上方
	up_direction,					// 上方
};

// 怪物的类型
enum MONSTER_TYPE
{
	MONSTER_NORMAL,													// 普通怪物
	MONSTER_BOSS,															// 大boss
};

// 装备类型
enum EQUIPMENT_TYPE
{
	EQUIPMENT_BLOOD,													// 血瓶
	EQUIPMENT_MAGIC,													// 魔瓶
	EQUIPMENT_WEAPON,												// 武器
};

// 场景ID
enum SCENE_ID
{
	INVALID_SCENE = -1,													// 无效场景
	CHAPTER_1_SCENE,														// 章节1场景
	CHAPTER_2_SCENE,														// 章节2场景
	CHAPTER_3_SCENE,														// 章节3场景
	CHAPTER_4_SCENE														// 章节4场景
};

// 命名空间定义的开始和结束
#define RPG_01_BEGIN namespace RPG_01{
#define RPG_01_END }

enum CHAPTER_ID
{
	CHAPTER_0, // 无效章节
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

// 定义类中属性的访问方法（可以减少编写重复的代码）
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

// 鼠标左键标志
#define LEFT_MOUSE_BUTTON (0)

// 鼠标右键标志
#define RIGHT_MOUSE_BUTTON (1)


#endif // !_DEFINE_H_
