#include "MonsterAction.h"
#include "Monster.h"
#include "MonsterCommand.h"
#include "Controller.h"
#include "Config.h"

RPG_01_BEGIN

MonsterAction* MonsterAction::m_pInstance = 0;

MonsterAction* MonsterAction::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new MonsterAction;
	}

	return m_pInstance;
}

MonsterAction::MonsterAction()
{
	m_DirectionMap.insert(make_pair(1,right_up_direction));
	m_DirectionMap.insert(make_pair(2,right_direction));
	m_DirectionMap.insert(make_pair(3,right_down_direction));
	m_DirectionMap.insert(make_pair(4,down_direction));

	m_strMonsterActionConfigFile = Game()->GetConfig()->GetMonsterActionConfigFile();

	m_pWalkUpAnimation			= 0;
	m_pWalkDownAnimation		= 0;
	m_pWalkLeftAnimation			= 0;
	m_pWalkRightAnimation		= 0;


	m_pRunRightAnimation		= 0;
	m_pRunDownAnimation		= 0;
	m_pRunLeftAnimation			= 0;
	m_pRunUpAnimation			= 0;

}

/************************************************************************
*  计算路径
************************************************************************/
MoveBy* MonsterAction::CalculatePath(Point srcPoint,Point destPoint)
{
	Point durPoint(destPoint - srcPoint);
	MoveBy* mb = MoveBy::create(3,durPoint);
	return mb;
}

/************************************************************************
*  加载妖怪站立不动的动画
************************************************************************/
void MonsterAction::LoadStaticAnimation(string monsterName)
{

	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["static"].asValueMap();

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

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pStaticRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticRightAnimation;
		}



		if (m_DirectionMap[direction] == right_direction)
		{
			m_pStaticDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticDownAnimation;
		}



		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pStaticLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pStaticUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pStaticUpAnimation;
		}

		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载妖怪走动的动画
************************************************************************/
void MonsterAction::LoadWalkAnimation(string monsterName)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["walk"].asValueMap();

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
		for (int i = 0; i < 8;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;
			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pWalkRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkRightAnimation;
		}

		if (m_DirectionMap[direction] == right_direction)
		{
			m_pWalkDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pWalkLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pWalkUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pWalkUpAnimation;
		}
		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载妖怪跑动的动画
************************************************************************/
void MonsterAction::LoadRunAnimation(string monsterName)
{

	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["run"].asValueMap();

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
		for (int i = 0; i < 8;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;
			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pRunRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunRightAnimation;
		}

		if (m_DirectionMap[direction] == right_direction)
		{
			m_pRunDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pRunLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pRunUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pRunUpAnimation;
		}
		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载妖怪攻击的动画
************************************************************************/
void MonsterAction::LoadAttackAnimation(string monsterName)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["attack"].asValueMap();

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
		int num = 7;
		if (strcmp(monsterName.c_str(),"monster4") == 0)
		{
			num = 6;
		}
		for (int i = 0; i < num;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;
			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pAttackRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackRightAnimation;
		}


		if (m_DirectionMap[direction] == right_direction)
		{
			m_pAttackDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pAttackLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pAttackUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pAttackUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}


/************************************************************************
*  加载妖怪吼叫的动画
************************************************************************/
void MonsterAction::LoadBellowAnimation(string monsterName)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["bellow"].asValueMap();

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

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pBellowRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellowRightAnimation;
		}


		if (m_DirectionMap[direction] == right_direction)
		{
			m_pBellowDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellowDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pBellowLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellowLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pBellowUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellowUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载妖怪吼叫2的动画
************************************************************************/
void MonsterAction::LoadBellow2Animation(string monsterName)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["bellow2"].asValueMap();

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

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pBellow2RightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellow2RightAnimation;
		}


		if (m_DirectionMap[direction] == right_direction)
		{
			m_pBellow2DownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellow2DownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pBellow2LeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellow2LeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pBellow2UpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pBellow2UpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载妖怪死亡的动画
************************************************************************/
void MonsterAction::LoadDieAnimation(string monsterName)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["die"].asValueMap();

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
		for (int i = 0; i < 8;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;
			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pDieRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieRightAnimation;
		}


		if (m_DirectionMap[direction] == right_direction)
		{
			m_pDieDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pDieLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pDieUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pDieUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  加载妖怪测试的动画
************************************************************************/
void MonsterAction::LoadTestAnimation(string monsterName)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strMonsterActionConfigFile); 
	auto monster = strings[monsterName.c_str()].asValueMap();
	auto dict = monster["test"].asValueMap();

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
		for (int i = 0; i < 9;++i)
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

		if (m_DirectionMap[direction] == right_up_direction)
		{
			m_pTestRightAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestRightAnimation;
		}


		if (m_DirectionMap[direction] == right_direction)
		{
			m_pTestDownAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
			m_pTestLeftAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
			m_pTestUpAnimation  = Animation::createWithSpriteFrames(frameList);
			pTempAnimation = m_pTestUpAnimation;
		}
		pTempAnimation->setLoops(1);
		pTempAnimation->setDelayPerUnit(0.1);
	}
}

/************************************************************************
*  执行妖怪的动作（就是播放动画）
************************************************************************/
void MonsterAction::Execute(Command* pCmd)
{

	MonsterCommand* pMonsterCmd = dynamic_cast<MonsterCommand*>(pCmd);
	if (pMonsterCmd == 0)
	{
		return;
	}

	m_MonsterCommand = *pMonsterCmd;

	if (pMonsterCmd == 0)
	{
		return;
	}

	if (m_MonsterCommand.GetMsg()== CodeMsg::code_monster_walk)
	{
		LoadWalkAnimation(m_MonsterCommand.GetMonsterName());

		Point srcPoint = m_MonsterCommand.GetReceiver()->getPosition();
		Point destPoint = m_MonsterCommand.GetDestPoint();

		MoveBy* mb = CalculatePath(srcPoint,destPoint);

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkRightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkDownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkLeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pWalkUpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;

	}

	if (m_MonsterCommand.GetMsg()== CodeMsg::code_monster_run)
	{
		LoadRunAnimation(m_MonsterCommand.GetMonsterName());

		Point srcPoint = m_MonsterCommand.GetReceiver()->getPosition();
		Point destPoint = m_MonsterCommand.GetDestPoint();

		MoveBy* mb = CalculatePath(srcPoint,destPoint);

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunRightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunDownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunLeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pRunUpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		if (seq == 0)
		{
			return;
		}

		return;

	}

	if (m_MonsterCommand.GetMsg() == CodeMsg::code_monster_static)
	{
		ActionEndCallback();
		return;
	}

	if (m_MonsterCommand.GetMsg() == CodeMsg::code_monster_attack)
	{
		LoadAttackAnimation(m_MonsterCommand.GetMonsterName());

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackRightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackDownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}



		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackLeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pAttackUpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_MonsterCommand.GetMsg() == CodeMsg::code_monster_bellow)
	{
		LoadBellowAnimation(m_MonsterCommand.GetMonsterName());

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellowRightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellowDownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}



		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellowLeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellowUpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_MonsterCommand.GetMsg() == CodeMsg::code_monster_bellow2)
	{
		LoadBellow2Animation(m_MonsterCommand.GetMonsterName());

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellow2RightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellow2DownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}



		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellow2LeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pBellow2UpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}


		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_MonsterCommand.GetMsg() == CodeMsg::code_monster_dying)
	{
		LoadDieAnimation(m_MonsterCommand.GetMonsterName());

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieRightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieDownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}



		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieLeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pDieUpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}

	if (m_MonsterCommand.GetMsg() == CodeMsg::code_monster_test)
	{
		LoadTestAnimation(m_MonsterCommand.GetMonsterName());

		m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

		//Spawn* spw = 0;
		Sequence* seq = 0;


		if (m_MonsterCommand.GetDirection() == right_up_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestRightAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == right_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestDownAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}



		if (m_MonsterCommand.GetDirection() == right_down_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestLeftAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}


		if (m_MonsterCommand.GetDirection() == down_direction)
		{
			seq = Sequence::create(Animate::create(m_pTestUpAnimation),CallFunc::create(CC_CALLBACK_0(MonsterAction::ActionEndCallback,this)),NULL);
		}

		if (seq == 0)
		{
			return;
		}

		m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

		return;
	}
}

/************************************************************************
*  动画播放结束后的回调函数
************************************************************************/
void MonsterAction::ActionEndCallback()
{
	Monster* pMonster = dynamic_cast<Monster*>(m_MonsterCommand.GetReceiver());

	if (pMonster == 0)
	{
		return;
	}

	m_MonsterCommand.GetReceiver()->GetSprite()->stopAllActions();

	if (pMonster->GetBloodValue() <= 0 || m_MonsterCommand.GetMsg() == CodeMsg::code_monster_dying)
	{
		pMonster->SetMsg(CodeMsg::code_monster_die);
		return ;
	}

	LoadStaticAnimation(m_MonsterCommand.GetMonsterName());


	Sequence* seq = 0;

	//pMonster
	

	if (m_MonsterCommand.GetDirection() == right_up_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticRightAnimation),NULL);
	}



	if (m_MonsterCommand.GetDirection() == right_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticDownAnimation),NULL);
	}



	if (m_MonsterCommand.GetDirection() == right_down_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticLeftAnimation),NULL);
	}



	if (m_MonsterCommand.GetDirection() == down_direction)
	{
		seq = Sequence::create(Animate::create(m_pStaticUpAnimation),NULL);
	}

	m_MonsterCommand.GetReceiver()->GetSprite()->runAction(seq);

	pMonster->SetMsg(CodeMsg::code_monster_static);
}


RPG_01_END