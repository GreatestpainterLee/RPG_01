#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "define.h"
#include "Entity.h"

RPG_01_BEGIN

/*
** 怪物类
*/
class Monster:public Entity
{
public:

	X_CREATE_FUNC(Monster);

	virtual bool init();

	Monster();

	~Monster();

	void		Reset();																					// 重置（怪物死亡的时候并不真正的删除怪物，只是将其隐藏起来，等合适的时候重置并再次显示）

	void		Upgrade();																			// 升级

	void		Action(int action_type,int direction);										// 怪物的行为动作

	void		Stop();																					// 停止怪物的行为动作

	void		AdjustPosition();																	// 调整位置

	bool		IsSelected();																			// 判断怪物是否被选中


	PROPERTY_INIT(float,Speed,m_fSpeed);
	PROPERTY_INIT(Point,DestPoint,m_DestPoint);
	PROPERTY_INIT(float,EmpiricalValue,m_fEmpiricalValue);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);
	PROPERTY_INIT(string,MonsterName,m_strMonsterName);

	int		GetMonsterType();																// 怪物类型：普通怪还是Boss
	void		SetMonsterType(int type);														// 设置怪物类型

	void		SetDirection(int v)	;																// 设置方向
	int		GetDirection();																		// 获得方向

	void		SetMsg(int type);														// 设置动作类型
	int		GetMsg();																	// 获得动作类型

	void		SetBloodValue(float v);															// 设置血量
	float		GetBloodValue();																	// 获取血量

	float		GetMaxBloodValue();															// 获得怪物的最大血量
protected:
	int					m_nPreDirection;														// 前一个移动的方向
	int					m_nPreMessage;													// 前一个动作的类型
private:
	int					m_nMonsterType;
	string				m_strMonsterName;													// 怪物的名字（用于加载各种不懂类型的怪物图片资源）
	float					m_fSpeed;																// 速度
	int					m_nDirection;															// 方向
	Point				m_DestPoint;															// 怪物做出一系列动作（如行走、跑动等）时的目标位置
	int					m_nMessage;														// 动作类型
	float					m_fBloodValue;															// 当前血量
	float					m_fMaxBloodValue;													// 最大血量（随着级数上升，其值也会随着增大）
	int					m_nLevel;																	// 当前等级
	static const int m_nMaxLevel = 16;													// 最大等级 
	float					m_fEmpiricalValue;													// 这只怪物被杀死的时候玩家所获得的经验值
	float					m_fDamageValue;														// 怪物攻击玩家的时候，玩家收到的伤害值
};

RPG_01_END

#endif // !_MONSTER_H_
