#include "PathManager.h"
#include "Util.h"

RPG_01_BEGIN

PathManager* PathManager::m_pInstance = 0;

PathManager* PathManager::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new PathManager;
	}

	return m_pInstance;
}

PathManager::PathManager()
{

}

/************************************************************************
*  根据两个点得到目标点相对于源点的方向
************************************************************************/
int PathManager::GetDirection(Point srcPoint,Point destPoint)
{
	if (destPoint.x > srcPoint.x)
	{
		if (destPoint.y > srcPoint.y)
		{
			return right_up_direction;
		}
		else if(destPoint.y == srcPoint.y)
		{
			return right_direction;
		}
		else
		{
			return right_down_direction;
		}
	}

	if (destPoint.x == srcPoint.x)
	{
		if (destPoint.y > srcPoint.y)
		{
			return up_direction;
		}
		else if(destPoint.y == srcPoint.y)
		{
			return static_direction;
		}
		else
		{
			return down_direction;
		}
	}

	if (destPoint.x < srcPoint.x)
	{
		if (destPoint.y > srcPoint.y)
		{
			return left_up_direction;
		}
		else if(destPoint.y == srcPoint.y)
		{
			return left_direction;
		}
		else
		{
			return left_down_direction;
		}
	}

	return static_direction;
}

/************************************************************************
*  判断某一个点是否在矩形区域内
************************************************************************/
bool PathManager::IsInRect(Rect& rect,Point& pont)
{
	if (pont.x < rect.getMinX())
	{
		return false;
	}

	if (pont.x > rect.getMaxX())
	{
		return false;
	}

	if (pont.y < rect.getMinY())
	{
		return false;
	}

	if (pont.y > rect.getMaxY())
	{
		return false;
	}

	return true;
}

/************************************************************************
*  获取目的地点相对于源点的方向以及距离
************************************************************************/
float  PathManager::GetDistance(Point& srcPoint,Point& destPoint,int& direction)
{
	float xDistance = destPoint.x - srcPoint.x;
	if (xDistance < 0)
	{
		xDistance = -xDistance;
	}

	float yDistance = destPoint.y - srcPoint.y;
	if (yDistance < 0)
	{
		yDistance = -yDistance;
	}

	float distance = sqrt(xDistance * xDistance + yDistance * yDistance);

	direction = GetDirection(srcPoint,destPoint);

	return distance;
}

/************************************************************************
*  随机得到一个坐标点
************************************************************************/
Point PathManager::GetRandomPoint()
{
	int xPos = Util::GetRandomNum(0,640);
	int yPos = Util::GetRandomNum(0,960);

	return Point(xPos,yPos);
}

Point PathManager::GetRandomPoint(Point leftdown,Point rightup)
{
	int xPos = Util::GetRandomNum(leftdown.x,rightup.x);
	int yPos = Util::GetRandomNum(leftdown.y,rightup.y);

	return Point(xPos,yPos);
}

/************************************************************************
*  随机取得一个方向
************************************************************************/
int PathManager::GetRandomDirection()
{
	float fPropability = Util::GetProbability();

	int direction = 0;
	if (fPropability < 0.25)
	{
		direction = right_up_direction;
	}

	if (fPropability>= 0.25 && fPropability< 0.5)
	{
		direction = right_direction;
	}

	if (fPropability >= 0.5 && fPropability <= 0.75)
	{
		direction = right_down_direction;
	}

	if (fPropability >= 0.75 && fPropability <= 1)
	{
		direction = down_direction;
	}
	return direction;
}

RPG_01_END