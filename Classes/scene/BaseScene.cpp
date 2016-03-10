#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "ui\CocosGUI.h"

#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"


#include "BaseScene.h"
#include "../../CommonClass/Util.h"
#include "../PathManager.h"
#include "../Controller.h"

#include "Chapter_1_Scene.h"
#include "Chapter_2_Scene.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Util.h"
#include "SkillAction.h"
#include "Skill.h"
#include "SkillManager.h"
#include "EquipmentManager.h"
#include "Config.h"
#include "PlayerManager.h"


USING_NS_CC;
using namespace cocos2d::ui;

#define _USE_PC_

RPG_01_BEGIN

BaseScene::BaseScene()
{
	m_pBackgroundLayer = 0;
	m_pEntityLayer = 0;
	m_pUILayer = 0;
	m_pPlayer = 0;

	m_bCanMove = false;
	m_nDirection = right_direction;
	m_pSelectCircleLight = Sprite::create(Game()->GetConfig()->GetSelfIndicatorFileName());//tray_self

}

BaseScene::~BaseScene()
{
	this->unscheduleUpdate();  
}

Scene* BaseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BaseScene::create();

	scene->addChild(layer);

	return scene;
}

bool BaseScene::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	m_bSkill_Q_ButtonPressed = false;							// 开始的时候Q、W、E、R没有按下
	m_bSkill_W_ButtonPressed = false;
	m_bSkill_E_ButtonPressed = false;
	m_bSkill_R_ButtonPressed = false;

	m_pBackgroundLayer = Layer::create();						// 创建三个layer
	m_pEntityLayer = Layer::create();
	m_pUILayer = Layer::create();

	addChild(m_pBackgroundLayer);								// 添加背景层
	addChild(m_pEntityLayer);											// 添加实体层（玩家、怪物、Boss、装备所在的层）
	addChild(m_pUILayer);												// 添加UI层

	registerMessage();															// 注册消息处理

	LoadBackground();													// 加载背景或地图

	LoadEntity();																// 加载各个实体（玩家、Boss、技能等）

	LoadUI();																	// 加载界面控件

	this->scheduleUpdate();

	return true;
}

/************************************************************************
*  注册事件
************************************************************************/
void BaseScene::registerMessage()
{

#ifdef _USE_PC_ // 使用电脑的时候
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BaseScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	auto _mouseListener = EventListenerMouse::create();
	// 鼠标右键消息
	_mouseListener->onMouseUp = [=](Event *event)
	{
		EventMouse* e = (EventMouse*)event;
		onMouseUp(e);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener,this);//addMessageListenerWithSceneGraphPriority(_mouseListener,this);
#else
	auto listener = MessageListenerTouchOneByOne::create();

	listener->setSwallowTouches(false);

	listener->onTouchBegan = CC_CALLBACK_2(BaseScene::touchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(BaseScene::touchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseScene::touchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(BaseScene::touchCancelled,this);
	_eventDispatcher->addMessageListenerWithFixedPriority(listener,-255);
#endif // _US_PC_
}


/************************************************************************
*  鼠标右键的处理函数
************************************************************************/
void BaseScene::onMouseUp(EventMouse* event)
{
	// 鼠标点击的坐标
	m_DestPoint =Point(event->getCursorX(),event->getCursorY());

	// 判断是哪个鼠标键点击了屏幕

	// 鼠标右键
	if (event->getMouseButton() == RIGHT_MOUSE_BUTTON)
	{
		m_pSelectCircleLight->setVisible(true);
		m_pSelectCircleLight->setPosition(Point(m_DestPoint.x ,m_DestPoint.y ));
		//m_pSelectCircleLight->setPosition(Point(m_DestPoint.x + 10,m_DestPoint.y - 20));//10,-20
		Game()->HandleRightClick(m_DestPoint);
	}

	// 鼠标左键
	if (event->getMouseButton() == LEFT_MOUSE_BUTTON)
	{
		// 如果Q键按下，那么处理按键Q对应的技能
		if (m_bSkill_Q_ButtonPressed)
		{
			SkillHandler_Q();
		}
		else
		// 如果W键按下，那么处理按键W对应的技能
		if (m_bSkill_W_ButtonPressed)
		{
			SkillHandler_W();
		}
		else
		// 如果E键按下，那么处理按键E对应的技能
		if (m_bSkill_E_ButtonPressed)
		{
			SkillHandler_E();
		}
		else
		// 如果R键按下，那么处理按键R对应的技能
		if (m_bSkill_R_ButtonPressed)
		{
			SkillHandler_R();
		}
		else
		{

		}
		m_bSkill_Q_ButtonPressed = false;
		m_bSkill_W_ButtonPressed = false;
		m_bSkill_E_ButtonPressed = false;
		m_bSkill_R_ButtonPressed = false;

	}
}


/************************************************************************
*  加载背景或地图：需要在子类中实现
************************************************************************/
void BaseScene::LoadBackground()
{
}

/************************************************************************
*  加载UI
************************************************************************/
void BaseScene::LoadUI()
{
	// 加载UI
	auto pUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(Game()->GetConfig()->GetUIFileName().c_str());
	pUI->setPosition(Point(0, 0));
	m_pUILayer->addChild(pUI);

	// 获取技能按钮
	m_pSkillButton_Q = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_1"));  
	m_pSkillButton_W = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_2"));  
	m_pSkillButton_E = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_3"));  
	m_pSkillButton_R = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_4"));  

	// 获取血条、魔法条、经验条
	m_pBloodProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Blood"));  
	m_pMagicProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Magic"));  
	m_pEmpiricalProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Empirical"));  

	m_pMonsterBloodProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Monster_Blood"));  
	m_pMonsterBloodProgressBar->setPercent(0);

	// 开始的时候经验是0
	m_pEmpiricalProgressBar->setPercent(0);

	// 增加按钮的点击事件处理函数
	m_pSkillButton_Q->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_Q, this));
	m_pSkillButton_W->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_W, this));
	m_pSkillButton_E->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_E, this));
	m_pSkillButton_R->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_R, this));
}


/************************************************************************
*  加载玩家
************************************************************************/
void BaseScene::LoadEntity()
{
	m_pEntityLayer->removeAllChildren();

	// 添加目的地指示的精灵
	m_pEntityLayer->addChild(m_pSelectCircleLight);
	m_pSelectCircleLight->setVisible(false);
	m_pSelectCircleLight->setScale(0.6);

	// 获得玩家
	m_pPlayer = Game()->GetMyPlayer();//Game()->GetPlayerManager()->GetPlayer(Game()->GetConfig()->GetRandomID());

	// 玩家一直是被选中状态
	m_pPlayer->SetSelected(true);

	m_pPlayer->setPosition(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	m_pPlayer->SetDestPoint(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	m_pPlayer->SetDirection(right_direction);
	m_pEntityLayer->addChild(m_pPlayer);

	m_pPlayer->Action(CodeMsg::code_player_static,right_direction);

	// 创建四个技能：技能在这里创建的原因是——技能需要需要在
	m_pSkill_Q = m_pPlayer->GetSkill_Q();//Game()->GetSkillManager()->CreateSkill(SKILL_Q,SKILL_6_ID);
	m_pSkill_W = m_pPlayer->GetSkill_W();//Game()->GetSkillManager()->CreateSkill(SKILL_W,SKILL_2_ID);
	m_pSkill_E = m_pPlayer->GetSkill_E();//Game()->GetSkillManager()->CreateSkill(SKILL_E,SKILL_3_ID);
	m_pSkill_R = m_pPlayer->GetSkill_R();//Game()->GetSkillManager()->CreateSkill(SKILL_R,SKILL_4_ID);
	
	// 
	m_pEntityLayer->addChild(m_pSkill_Q);
	m_pEntityLayer->addChild(m_pSkill_W);
	m_pEntityLayer->addChild(m_pSkill_E);
	m_pEntityLayer->addChild(m_pSkill_R);

	// 获取Boss
	Monster* pBoss = Game()->GetBoss();
	pBoss->setPosition(Point(Game()->GetConfig()->GetBossPosition_X(),Game()->GetConfig()->GetBossPosition_Y()));

	m_pEntityLayer->addChild(pBoss);

	pBoss->setScale(2);

	pBoss->Action(CodeMsg::code_monster_static,down_direction);

	// 是否显示传送门，在章节四（终结章）是没有传送门的
	if (Game()->GetCurrentChapter() != CHAPTER_4)
	{
		Game()->GetSkillManager()->ShowPortal(this);
	}
}


Layer* BaseScene::GetBackgroundLayer()
{
	return m_pBackgroundLayer;
}

Layer* BaseScene::GetEntityLayer()
{
	return m_pEntityLayer;
}

Layer* BaseScene::GetUILayer()
{
	return m_pUILayer;
}

#ifdef _USE_PC_

void BaseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_A:
		{
			m_pBackgroundLayer->removeAllChildren();
			TMXTiledMap* pMap = TMXTiledMap::create("LFR/other/map/map2.tmx");
			m_pBackgroundLayer->addChild(pMap);
		}
		break;
	default:
		break;
	}
}

void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_bSkill_Q_ButtonPressed = false;
	m_bSkill_W_ButtonPressed = false;
	m_bSkill_E_ButtonPressed = false;
	m_bSkill_R_ButtonPressed = false;

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
		if (m_bSkill_Q_ButtonPressed)
		{
			m_bSkill_Q_ButtonPressed = false;
		}
		else
		{
			m_bSkill_Q_ButtonPressed = true;
		}
		break;
	case EventKeyboard::KeyCode::KEY_W:
		if (m_bSkill_W_ButtonPressed)
		{
			m_bSkill_W_ButtonPressed = false;
		}
		else
		{
			m_bSkill_W_ButtonPressed = true;
		}
		break;
	case EventKeyboard::KeyCode::KEY_E:
		if (m_bSkill_E_ButtonPressed)
		{
			m_bSkill_E_ButtonPressed = false;
		}
		else
		{
			m_bSkill_E_ButtonPressed = true;
		}
		break;
	case EventKeyboard::KeyCode::KEY_R:
		if (m_bSkill_R_ButtonPressed)
		{
			m_bSkill_R_ButtonPressed = false;
		}
		else
		{
			m_bSkill_R_ButtonPressed = true;
		}
		break;
	case EventKeyboard::KeyCode::KEY_A:
		Game()->ChangeChapter(CHAPTER_1);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		Game()->ChangeChapter(CHAPTER_2);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		Game()->ChangeChapter(CHAPTER_3);
		break;
	case EventKeyboard::KeyCode::KEY_F:
		Game()->ChangeChapter(CHAPTER_4);
		break;
	case EventKeyboard::KeyCode::KEY_G:
		//m_pPlayer->ShowBloodReturnAnimation();
		Game()->GetEquipmentManager()->TestAnimation();
		break;
	default:
		break;
	}
}

#endif

void BaseScene::ShowDestPoint(bool v)
{
	// 当鼠标右键点击屏幕的时候，在屏幕上显示目的地位置的光标（一个绿色的小圆点）
	m_pSelectCircleLight->setVisible(v);
}

void BaseScene::SkillHandler_Q()
{
	if (m_bSkill_Q_ButtonPressed)
	{
		// 设置玩家当前的技能为Q技能
		m_pPlayer->SetCurrentSkill(m_pSkill_Q);
		// 设置技能需要施放的地方
		m_pSkill_Q->setPosition(m_DestPoint);
		// 此技能并不是真正的由玩家来施放，调用Action的目的仅仅是设置动作标记
		m_pPlayer->Action(CodeMsg::code_player_skillattack,m_pPlayer->GetDirection());
	}

}

void BaseScene::SkillHandler_W()
{
	if (m_bSkill_W_ButtonPressed)
	{
		m_pPlayer->SetCurrentSkill(m_pSkill_W);
		m_pSkill_W->setPosition(m_DestPoint);
		m_pPlayer->Action(CodeMsg::code_player_skillattack,m_pPlayer->GetDirection());
	}

}

void BaseScene::SkillHandler_E()
{
	if (m_bSkill_E_ButtonPressed)
	{
		m_pPlayer->SetCurrentSkill(m_pSkill_E);
		m_pSkill_E->setPosition(m_DestPoint);
		m_pPlayer->Action(CodeMsg::code_player_skillattack,m_pPlayer->GetDirection());
	}
}

void BaseScene::SkillHandler_R()
{
	if (m_bSkill_R_ButtonPressed)
	{
		m_pPlayer->SetCurrentSkill(m_pSkill_R);
		m_pSkill_R->setPosition(m_DestPoint);
		m_pPlayer->Action(CodeMsg::code_player_skillattack,m_pPlayer->GetDirection());
	}
}


RPG_01_END