#include "SkillAction.h"
#include "SkillCommand.h"
#include "Entity.h"
#include "cocos2d.h"
#include "Controller.h"
#include "Config.h"

RPG_01_BEGIN
SkillAction* SkillAction::m_pInstance = 0;

SkillAction* SkillAction::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new SkillAction;
	}
	return m_pInstance;
}

SkillAction::SkillAction()
{
	m_strSkillActionConfigFile = Game()->GetConfig()->GetSkillActionConfigFile();
}

SkillAction::~SkillAction()
{

}

/************************************************************************
*  技能1
************************************************************************/
Animation* SkillAction::LoadSkillAnimation1()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill1"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;
		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 24;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;
		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation1 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation1->setLoops(1);
	m_pSkillAnimation1->setDelayPerUnit(0.1);
	return m_pSkillAnimation1;
}

/************************************************************************
*  技能2
************************************************************************/
Animation* SkillAction::LoadSkillAnimation2()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill2"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 14;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation2 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation2->setLoops(1);
	m_pSkillAnimation2->setDelayPerUnit(0.1);
	return m_pSkillAnimation2;
}


/************************************************************************
*  技能3
************************************************************************/
Animation* SkillAction::LoadSkillAnimation3()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill3"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 24;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation3 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation3->setLoops(1);
	m_pSkillAnimation3->setDelayPerUnit(0.1);
	return m_pSkillAnimation3;
}

/************************************************************************
*  技能4
************************************************************************/
Animation* SkillAction::LoadSkillAnimation4()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill4"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 29;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation4 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation4->setLoops(1);
	m_pSkillAnimation4->setDelayPerUnit(0.1);
	return m_pSkillAnimation4;
}

/************************************************************************
*  技能5
************************************************************************/
Animation* SkillAction::LoadSkillAnimation5()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill5"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 32;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation5 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation5->setLoops(1);
	m_pSkillAnimation5->setDelayPerUnit(0.1);
	return m_pSkillAnimation5;
}

/************************************************************************
*  技能6
************************************************************************/
Animation* SkillAction::LoadSkillAnimation6()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill6"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 24;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation6 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation6->setLoops(1);
	m_pSkillAnimation6->setDelayPerUnit(0.1);
	return m_pSkillAnimation6;
}

/************************************************************************
*  技能7
************************************************************************/
Animation* SkillAction::LoadSkillAnimation7()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill7"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10; i < 18;++i)
	{
		string tmp = StringUtils::format("_%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation7 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation7->setLoops(1);
	m_pSkillAnimation7->setDelayPerUnit(0.1);
	return m_pSkillAnimation7;
}

/************************************************************************
*  技能8
************************************************************************/
Animation* SkillAction::LoadSkillAnimation8()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["skill8"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 0; i < 10;++i)
	{
		string tmp = StringUtils::format("_0%d.png",i);;
		string path = strPicName + tmp;

		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	m_pSkillAnimation8 = Animation::createWithSpriteFrames(frameList);
	m_pSkillAnimation8->setLoops(1);
	m_pSkillAnimation8->setDelayPerUnit(0.1);
	return m_pSkillAnimation8;
}

/************************************************************************
*  传送门的动画
************************************************************************/
Animation* SkillAction::LoadSkillPortal()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["portal"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 1; i < 10;++i)
	{
		string tmp = StringUtils::format("-000%d.png",i);;
		string path = strPicName + tmp;
		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10 ; i < 19;++i)
	{
		string tmp = StringUtils::format("-00%d.png",i);;
		string path = strPicName + tmp;
		frame = frameCache->getSpriteFrameByName((path));
		frameList.pushBack(frame);
	}

	m_pSkillPortal = Animation::createWithSpriteFrames(frameList);
	m_pSkillPortal->setLoops(-1);
	m_pSkillPortal->setDelayPerUnit(0.1);
	return m_pSkillPortal;
}

/************************************************************************
*  回血的动画
************************************************************************/
Animation* SkillAction::LoadSkillBloodReturn()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile(m_strSkillActionConfigFile); 
	auto dict = strings["blood_return"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;


	frameList.clear();
	for (int i = 4; i < 10;++i)
	{
		string tmp = StringUtils::format("-000%d.png",i);;
		string path = strPicName + tmp;
		frame = frameCache->getSpriteFrameByName((path));

		frameList.pushBack(frame);
	}

	for (int i = 10 ; i < 46;++i)
	{
		string tmp = StringUtils::format("-00%d.png",i);;
		string path = strPicName + tmp;
		frame = frameCache->getSpriteFrameByName((path));
		frameList.pushBack(frame);
	}

	m_pSkillBloodReturn = Animation::createWithSpriteFrames(frameList);
	m_pSkillBloodReturn->setLoops(1);
	m_pSkillBloodReturn->setDelayPerUnit(0.1);
	return m_pSkillBloodReturn;
}

/************************************************************************
*  执行技能动画
************************************************************************/
void SkillAction::Execute(Command* pCmd)
{

	SkillCommand* skillCmd = dynamic_cast<SkillCommand*>(pCmd);
	if (skillCmd == 0)
	{
		return;
	}
	m_SkillCommand = *skillCmd;

	m_SkillCommand.GetReceiver()->GetSprite()->stopAllActions();

	m_SkillCommand.GetReceiver()->GetSprite()->setVisible(true);

	Sequence* seq = 0;
	switch (m_SkillCommand.GetSkillID())
	{
	case SKILL_1_ID:
		{
			LoadSkillAnimation1();
			seq = Sequence::create(Animate::create(m_pSkillAnimation1),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_2_ID:
		{
			LoadSkillAnimation2();
			seq = Sequence::create(Animate::create(m_pSkillAnimation2),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_3_ID:
		{
			LoadSkillAnimation3();
			seq = Sequence::create(Animate::create(m_pSkillAnimation3),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_4_ID:
		{
			LoadSkillAnimation4();
			seq = Sequence::create(Animate::create(m_pSkillAnimation4),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_5_ID:
		{
			LoadSkillAnimation5();
			seq = Sequence::create(Animate::create(m_pSkillAnimation5),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_6_ID:
		{
			LoadSkillAnimation6();
			seq = Sequence::create(Animate::create(m_pSkillAnimation6),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_7_ID:
		{
			LoadSkillAnimation7();
			seq = Sequence::create(Animate::create(m_pSkillAnimation7),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	case SKILL_8_ID:
		{
			LoadSkillAnimation8();
			seq = Sequence::create(Animate::create(m_pSkillAnimation8),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;

	case SKILL_BLOOD_RETURN_ID:
		{
			LoadSkillBloodReturn();
			seq = Sequence::create(Animate::create(m_pSkillBloodReturn),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;

	case SKILL_PORTAL_ID:
		{
			LoadSkillPortal();
			seq = Sequence::create(Animate::create(m_pSkillPortal),CallFunc::create(CC_CALLBACK_0(SkillAction::ActionEndCallback,this)),NULL);	
		}
		break;
	}

	if (seq == 0)
	{
		return;
	}

	m_SkillCommand.GetReceiver()->GetSprite()->runAction(seq);
}

/************************************************************************
*  动画播放完成的回调函数
************************************************************************/
void SkillAction::ActionEndCallback()
{
	m_SkillCommand.GetReceiver()->GetSprite()->stopAllActions();
	m_SkillCommand.GetReceiver()->GetSprite()->setVisible(false);
}

RPG_01_END