#ifndef _PATH_MANAGER_H_
#define _PATH_MANAGER_H_


#include <cocos2d.h>

#include "define.h"

USING_NS_CC;

RPG_01_BEGIN

/*
** 路径以及方向的管理类
*/
class PathManager
{
public:
	static PathManager* GetInstance();
	virtual ~PathManager(){};

	int			GetDirection(Point srcPoint,Point destPoint);

	bool			IsInRect(Rect& rect,Point& pont);

	float			GetDistance(Point& srcPoint,Point& destPoint,int& direction);

	Point		GetRandomPoint();

	Point		GetRandomPoint(Point leftdown,Point rightup);

	int			GetRandomDirection();
	
private:
	PathManager();
	static PathManager*			m_pInstance;
};

RPG_01_END

#endif

