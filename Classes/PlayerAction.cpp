#include "PlayerAction.h"
#include "Player.h"
#include "PlayerCommand.h"
#include "Config.h"
#include "Controller.h"

RPG_01_BEGIN

PlayerAction* PlayerAction::m_pInstance = 0;

PlayerAction* PlayerAction::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new PlayerAction;
	}

	return m_pInstance;
}

PlayerAction::PlayerAction()
{
	m_DirectionMap.insert(make_pair(1,right_direction));
	m_DirectionMap.insert(make_pair(2,down_direction));
	m_DirectionMap.insert(make_pair(3,left_direction));
	m_DirectionMap.insert(make_pair(4,up_direction));

	m_strPlayerActionConfigFile = Game()->GetConfig()->GetPlayerActionConfigFile();

	m_pWalkRightUpAnimation = 0;
	m_pWalkRightAnimation = 0;
	m_pWalkRightDownAnimation = 0;
	m_pWalkDownAnimation = 0;
	m_pWalkLeftDownAnimation = 0;
	m_pWalkLeftAnimation = 0;
	m_pWalkLeftUpAnimation = 0;
	m_pWalkUpAnimation = 0;

	m_pRunRightUpAnimation = 0;
	m_pRunRightAnimation = 0;
	m_pRunRightDownAnimation = 0;
	m_pRunDownAnimation = 0;
	m_pRunLeftDownAnimation = 0;
	m_pRunLeftAnimation = 0;
	m_pRunLeftUpAnimation = 0;
	m_pRunUpAnimation = 0;

	m_pStaticRightUpAnimation = 0;
	m_pStaticRightAnimation = 0;
	m_pStaticRightDownAnimation = 0;
	m_pStaticDownAnimation = 0;
	m_pStaticLeftDownAnimation = 0;
	m_pStaticLeftAnimation = 0;
	m_pStaticLeftUpAnimation = 0;
	m_pStaticUpAnimation = 0;

	m_pAttackRightUpAnimation = 0;
	m_pAttackRightAnimation = 0;
	m_pAttackRightDownAnimation = 0;
	m_pAttackDownAnimation = 0;
	m_pAttackLeftDownAnimation = 0;
	m_pAttackLeftAnimation = 0;
	m_pAttackLeftUpAnimation = 0;
	m_pAttackUpAnimation = 0;

	m_pThrowoffRightUpAnimation = 0;
	m_pThrowoffRightAnimation = 0;
	m_pThrowoffRightDownAnimation = 0;
	m_pThrowoffDownAnimation = 0;
	m_pThrowoffLeftDownAnimation = 0;
	m_pThrowoffLeftAnimation = 0;
	m_pThrowoffLeftUpAnimation = 0;
	m_pThrowoffUpAnimation = 0;

	m_pBeatenRightUpAnimation = 0;
	m_pBeatenRightAnimation = 0;
	m_pBeatenRightDownAnimation = 0;
	m_pBeatenDownAnimation = 0;
	m_pBeatenLeftDownAnimation = 0;
	m_pBeatenLeftAnimation = 0;
	m_pBeatenLeftUpAnimation = 0;
	m_pBeatenUpAnimation = 0;

	m_pDieRightUpAnimation = 0;
	m_pDieRightAnimation = 0;
	m_pDieRightDownAnimation = 0;
	m_pDieDownAnimation = 0;
	m_pDieLeftDownAnimation = 0;
	m_pDieLeftAnimation = 0;
	m_pDieLeftUpAnimation = 0;
	m_pDieUpAnimation = 0;

	//Beaten
	m_pTestRightUpAnimation = 0;
	m_pTestRightAnimation = 0;
	m_pTestRightDownAnimation = 0;
	m_pTestDownAnimation = 0;
	m_pTestLeftDownAnimation = 0;
	m_pTestLeftAnimation = 0;
	m_pTestLeftUpAnimation = 0;
	m_pTestUpAnimation = 0;

}

/************************************************************************
*  计算路径（目前没有用到）
************************************************************************/
MoveBy* PlayerAction::CalculatePath(Point srcPoint,Point destPoint)
{
	Point durPoint(destPoint - srcPoint);
	MoveBy* mb = MoveBy::create(3,durPoint);
	return mb;
}

/************************************************************************
*  加载玩家静止不动时候的动画
************************************************************************/
void PlayerAction::LoadStaticAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["static"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	int index = 0;

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 8; ++direction)
	{
		frameList.clear();
		for (int i = index; i <= index;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;
		if (direction == right_up_direction)
		{
			m_pStaticRightUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticRightUpAnimation;

		}

		if (direction == right_direction)
		{
			m_pStaticRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticRightAnimation;
			//m_StaticRightAnimationList = frameList;
		}

		if (direction == right_down_direction)
		{
			m_pStaticRightDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticRightDownAnimation;

		}

		if (direction == down_direction)
		{
			m_pStaticDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticDownAnimation;

		}

		if (direction == left_down_direction)
		{
			m_pStaticLeftDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticLeftDownAnimation;

		}

		if (direction == left_direction)
		{
			m_pStaticLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticLeftAnimation;

		}

		if (direction == left_up_direction)
		{
			m_pStaticLeftUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticLeftUpAnimation;

		}

		if (direction == up_direction)
		{
			m_pStaticUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticUpAnimation;
		}

		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载玩家走动时候的动画
************************************************************************/
void PlayerAction::LoadWalkAnimation()
{

	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["walk"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 8; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 10;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		for (int i = 10; i < 16;++i)
		{
			string tmp = StringUtils::format("_%d_%d_%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;
		if (direction == right_up_direction)
		{
			m_pWalkRightUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkRightUpAnimation;
			//m_WalkRightUpAnimationList = frameList;
		}

		if (direction == right_direction)
		{
			m_pWalkRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkRightAnimation;
			//m_WalkRightAnimationList = frameList;
		}

		if (direction == right_down_direction)
		{
			m_pWalkRightDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkRightDownAnimation;
			//m_WalkRightDownAnimationList = frameList;
		}

		if (direction == down_direction)
		{
			m_pWalkDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkDownAnimation;
			//m_WalkDownAnimationList = frameList;
		}

		if (direction == left_down_direction)
		{
			m_pWalkLeftDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkLeftDownAnimation;
			//m_WalkLeftDownAnimationList = frameList;
		}

		if (direction == left_direction)
		{
			m_pWalkLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkLeftAnimation;
			//m_WalkLeftAnimationList = frameList;
		}

		if (direction == left_up_direction)
		{
			m_pWalkLeftUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkLeftUpAnimation;
			//m_WalkLeftUpAnimationList = frameList;
		}

		if (direction == up_direction)
		{
			m_pWalkUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkUpAnimation;
			//m_WalkUpAnimationList = frameList;
		}
		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载玩家跑动时候的动画
************************************************************************/
void PlayerAction::LoadRunAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["run"].asValueMap();
	
	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 8; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 10;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		for (int i = 10; i < 16;++i)
		{
			string tmp = StringUtils::format("_%d_%d_%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;
		if (direction == right_up_direction)
		{
			m_pRunRightUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunRightUpAnimation;
			//m_RunRightUpAnimationList = frameList;
		}

		if (direction == right_direction)
		{
			m_pRunRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunRightAnimation;
			//m_RunRightAnimationList = frameList;
		}

		if (direction == right_down_direction)
		{
			m_pRunRightDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunRightDownAnimation;
			//m_RunRightDownAnimationList = frameList;
		}

		if (direction == down_direction)
		{
			m_pRunDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunDownAnimation;
			//m_RunDownAnimationList = frameList;
		}

		if (direction == left_down_direction)
		{
			m_pRunLeftDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunLeftDownAnimation;
			//m_RunLeftDownAnimationList = frameList;
		}

		if (direction == left_direction)
		{
			m_pRunLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunLeftAnimation;
			//m_RunLeftAnimationList = frameList;
		}

		if (direction == left_up_direction)
		{
			m_pRunLeftUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunLeftUpAnimation;
			//m_RunLeftUpAnimationList = frameList;
		}

		if (direction == up_direction)
		{
			m_pRunUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunUpAnimation;
			//m_RunUpAnimationList = frameList;
		}
		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载玩家的攻击动画
************************************************************************/
void PlayerAction::LoadAttackAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["attack"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 8; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 8;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}


		Animation* pTempAnimation = 0;
		if (direction == right_up_direction)
		{
			m_pAttackRightUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackRightUpAnimation;
			//m_AttackRightUpAnimationList = frameList;
		}

		if (direction == right_direction)
		{
			m_pAttackRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackRightAnimation;
			//m_AttackRightAnimationList = frameList;
		}

		if (direction == right_down_direction)
		{
			m_pAttackRightDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackRightDownAnimation;
			//m_AttackRightDownAnimationList = frameList;
		}

		if (direction == down_direction)
		{
			m_pAttackDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackDownAnimation;
			//m_AttackDownAnimationList = frameList;
		}

		if (direction == left_down_direction)
		{
			m_pAttackLeftDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackLeftDownAnimation;
			//m_AttackLeftDownAnimationList = frameList;
		}

		if (direction == left_direction)
		{
			m_pAttackLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackLeftAnimation;
			//m_AttackLeftAnimationList = frameList;
		}

		if (direction == left_up_direction)
		{
			m_pAttackLeftUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackLeftUpAnimation;
			//m_AttackLeftUpAnimationList = frameList;
		}

		if (direction == up_direction)
		{
			m_pAttackUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackUpAnimation;
			//m_AttackUpAnimationList = frameList;
		}
		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  玩家施放魔法的时候的手势
************************************************************************/
void PlayerAction::LoadThrowoffAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["throwoff"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 8; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 8;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}


		Animation* pTempAnimation = 0;
		if (direction == right_up_direction)
		{
			m_pThrowoffRightUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffRightUpAnimation;
		}

		if (direction == right_direction)
		{
			m_pThrowoffRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffRightAnimation;
		}

		if (direction == right_down_direction)
		{
			m_pThrowoffRightDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffRightDownAnimation;
		}

		if (direction == down_direction)
		{
			m_pThrowoffDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffDownAnimation;
		}

		if (direction == left_down_direction)
		{
			m_pThrowoffLeftDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffLeftDownAnimation;
		}

		if (direction == left_direction)
		{
			m_pThrowoffLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffLeftAnimation;
		}

		if (direction == left_up_direction)
		{
			m_pThrowoffLeftUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffLeftUpAnimation;
		}

		if (direction == up_direction)
		{
			m_pThrowoffUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pThrowoffUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载玩家被攻击的动画
************************************************************************/
void PlayerAction::LoadBeatenAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["beaten"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 4; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 3;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}


		Animation* pTempAnimation = 0;

		if (m_DirectionMap[direction] == right_direction)
		{
			m_pBeatenRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBeatenRightAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pBeatenDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBeatenDownAnimation;
		}

		if (m_DirectionMap[direction] == left_direction)
		{
			m_pBeatenLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBeatenLeftAnimation;
		}

		if (m_DirectionMap[direction] == up_direction)
		{
			m_pBeatenUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBeatenUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  玩家挂了的时候的动画
************************************************************************/
void PlayerAction::LoadDieAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["die"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 4; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 4;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;


			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}


		Animation* pTempAnimation = 0;

		if (m_DirectionMap[direction] == right_direction)
		{
			m_pDieRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieRightAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pDieDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieDownAnimation;
		}

		if (m_DirectionMap[direction] == left_direction)
		{
			m_pDieLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieLeftAnimation;
		}

		if (m_DirectionMap[direction] == up_direction)
		{
			m_pDieUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}


void PlayerAction::LoadTestAnimation()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strPlayerActionConfigFile); 
	auto role = strings[m_strRole.c_str()].asValueMap();
	auto dict = role["test"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 4; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 3;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;

			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}


		Animation* pTempAnimation = 0;
		/*if (direction == right_up_direction)
		{
			m_pTestRightUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestRightUpAnimation;
		}*/

		if (m_DirectionMap[direction] == right_direction)
		{
			m_pTestRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestRightAnimation;
		}

		/*if (direction == right_down_direction)
		{
			m_pTestRightDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestRightDownAnimation;
		}*/

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pTestDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestDownAnimation;
		}

		/*if (direction == left_down_direction)
		{
			m_pTestLeftDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestLeftDownAnimation;
		}*/

		if (m_DirectionMap[direction] == left_direction)
		{
			m_pTestLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestLeftAnimation;
		}

		/*if (direction == left_up_direction)
		{
			m_pTestLeftUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestLeftUpAnimation;
		}*/

		if (m_DirectionMap[direction] == up_direction)
		{
			m_pTestUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  执行玩家的动作
************************************************************************/
void PlayerAction::Execute(Command* pCmd)
{
	
	PlayerCommand* playerCmd = dynamic_cast<PlayerCommand*>(pCmd);
	if (playerCmd == 0)
	{
		return;
	}
	m_PlayerCommand = *playerCmd;

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_walk)
	{
		LoadWalkAnimation();

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkRightUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkRightAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkRightDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkLeftDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkLeftAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkLeftUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}


		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_PlayerCommand.GetMsg()== CodeMsg::code_player_run)
	{
		LoadRunAnimation();

		Point srcPoint = m_PlayerCommand.GetReceiver()->getPosition();
		Point destPoint = m_PlayerCommand.GetDestPoint();

		MoveBy* mb = CalculatePath(srcPoint,destPoint);

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunRightUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunRightAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunRightDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunLeftDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunLeftAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunLeftUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		
		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;

	}

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_static)
	{
		ActionEndCallback();
		return;
	}

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_attack)
	{
		LoadAttackAnimation();

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackRightUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackRightAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackRightDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackLeftDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackLeftAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackLeftUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}


		if (seq == 0)
		{
			return;
		}

		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_throwoff)
	{
		LoadThrowoffAnimation();

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffRightUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffRightAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffRightDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffLeftDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffLeftAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffLeftUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pThrowoffUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}


		if (seq == 0)
		{
			return;
		}

		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_beaten)
	{
		LoadBeatenAnimation();

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		/*if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenRightUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}*/

		if (m_DirectionMap[m_PlayerCommand.GetDirection()] == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenRightAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		/*if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenRightDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}*/

		if (m_DirectionMap[m_PlayerCommand.GetDirection()] == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		/*if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenLeftDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}*/

		if (m_DirectionMap[m_PlayerCommand.GetDirection()] == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenLeftAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		/*if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenLeftUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}*/

		if (m_DirectionMap[m_PlayerCommand.GetDirection()] == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pBeatenUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}


		if (seq == 0)
		{
			return;
		}

		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_die)
	{
		LoadDieAnimation();

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieRightUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieRightAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieRightDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieLeftDownAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieLeftAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieLeftUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (m_PlayerCommand.GetDirection() == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieUpAnimation),CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_PlayerCommand.GetMsg() == CodeMsg::code_player_test)
	{
		LoadTestAnimation();

		m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;

		if (m_PlayerCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestRightUpAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestRightAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestRightDownAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestDownAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestLeftDownAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestLeftAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == left_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestLeftUpAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (m_PlayerCommand.GetDirection() == up_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestUpAnimation)/*,CallFunc::create(CC_CALLBACK_0(PlayerAction::ActionEndCallback,this))*/,NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

}

/************************************************************************
*  动画播放完成的时的回调函数
************************************************************************/
void PlayerAction::ActionEndCallback()
{
	Player* player = dynamic_cast<Player*>(m_PlayerCommand.GetReceiver());

	if (0 == player)
	{
		return;
	}

	if (player->GetMsg() == CodeMsg::code_player_die)
	{
		return;
	}

	player->SetMsg(CodeMsg::code_player_static);

	LoadStaticAnimation();

	m_PlayerCommand.GetReceiver()->GetSprite()->stopAllActions();

	Sequence* seq = 0;

	if (m_PlayerCommand.GetDirection() == right_up_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticRightUpAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == right_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticRightAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == right_down_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticRightDownAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == down_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticDownAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == left_down_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticLeftDownAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == left_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticLeftAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == left_up_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticLeftUpAnimation),NULL);
	}

	if (m_PlayerCommand.GetDirection() == up_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticUpAnimation),NULL);
	}

	if (seq == 0)
	{
		return;
	}

	m_PlayerCommand.GetReceiver()->GetSprite()->runAction(seq);

}


RPG_01_END