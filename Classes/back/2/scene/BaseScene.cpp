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

	m_bSkill_Q_ButtonPressed = false;							// ��ʼ��ʱ��Q��W��E��Rû�а���
	m_bSkill_W_ButtonPressed = false;
	m_bSkill_E_ButtonPressed = false;
	m_bSkill_R_ButtonPressed = false;

	m_pBackgroundLayer = Layer::create();						// ��������layer
	m_pEntityLayer = Layer::create();
	m_pUILayer = Layer::create();

	addChild(m_pBackgroundLayer);								// ��ӱ�����
	addChild(m_pEntityLayer);											// ���ʵ��㣨��ҡ����Boss��װ�����ڵĲ㣩
	addChild(m_pUILayer);												// ���UI��

	registerMessage();															// ע����Ϣ����

	LoadBackground();													// ���ر������ͼ

	LoadEntity();																// ���ظ���ʵ�壨��ҡ�Boss�����ܵȣ�

	LoadUI();																	// ���ؽ���ؼ�

	this->scheduleUpdate();

	return true;
}

/************************************************************************
*  ע���¼�
************************************************************************/
void BaseScene::registerMessage()
{

#ifdef _USE_PC_ // ʹ�õ��Ե�ʱ��
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BaseScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	auto _mouseListener = EventListenerMouse::create();
	// ����Ҽ���Ϣ
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
*  ����Ҽ��Ĵ�����
************************************************************************/
void BaseScene::onMouseUp(EventMouse* event)
{
	// �����������
	m_DestPoint =Point(event->getCursorX(),event->getCursorY());

	// �ж����ĸ������������Ļ

	// ����Ҽ�
	if (event->getMouseButton() == RIGHT_MOUSE_BUTTON)
	{
		m_pSelectCircleLight->setVisible(true);
		m_pSelectCircleLight->setPosition(Point(m_DestPoint.x ,m_DestPoint.y ));
		//m_pSelectCircleLight->setPosition(Point(m_DestPoint.x + 10,m_DestPoint.y - 20));//10,-20
		Game()->HandleRightClick(m_DestPoint);
	}

	// ������
	if (event->getMouseButton() == LEFT_MOUSE_BUTTON)
	{
		// ���Q�����£���ô������Q��Ӧ�ļ���
		if (m_bSkill_Q_ButtonPressed)
		{
			SkillHandler_Q();
		}
		else
		// ���W�����£���ô������W��Ӧ�ļ���
		if (m_bSkill_W_ButtonPressed)
		{
			SkillHandler_W();
		}
		else
		// ���E�����£���ô������E��Ӧ�ļ���
		if (m_bSkill_E_ButtonPressed)
		{
			SkillHandler_E();
		}
		else
		// ���R�����£���ô������R��Ӧ�ļ���
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
*  ���ر������ͼ����Ҫ��������ʵ��
************************************************************************/
void BaseScene::LoadBackground()
{
}

/************************************************************************
*  ����UI
************************************************************************/
void BaseScene::LoadUI()
{
	// ����UI
	auto pUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(Game()->GetConfig()->GetUIFileName().c_str());
	pUI->setPosition(Point(0, 0));
	m_pUILayer->addChild(pUI);

	// ��ȡ���ܰ�ť
	m_pSkillButton_Q = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_1"));  
	m_pSkillButton_W = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_2"));  
	m_pSkillButton_E = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_3"));  
	m_pSkillButton_R = dynamic_cast<Button*>(pUI->getChildByName("Skill_Button_4"));  

	// ��ȡѪ����ħ������������
	m_pBloodProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Blood"));  
	m_pMagicProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Magic"));  
	m_pEmpiricalProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Empirical"));  

	m_pMonsterBloodProgressBar = dynamic_cast<LoadingBar*>(pUI->getChildByName("ProgressBar_Monster_Blood"));  
	m_pMonsterBloodProgressBar->setPercent(0);

	// ��ʼ��ʱ������0
	m_pEmpiricalProgressBar->setPercent(0);

	// ���Ӱ�ť�ĵ���¼�������
	m_pSkillButton_Q->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_Q, this));
	m_pSkillButton_W->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_W, this));
	m_pSkillButton_E->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_E, this));
	m_pSkillButton_R->addClickEventListener(CC_CALLBACK_0(BaseScene::SkillHandler_R, this));
}


/************************************************************************
*  �������
************************************************************************/
void BaseScene::LoadEntity()
{
	m_pEntityLayer->removeAllChildren();

	// ���Ŀ�ĵ�ָʾ�ľ���
	m_pEntityLayer->addChild(m_pSelectCircleLight);
	m_pSelectCircleLight->setVisible(false);
	m_pSelectCircleLight->setScale(0.6);

	// ������
	m_pPlayer = Game()->GetMyPlayer();//Game()->GetPlayerManager()->GetPlayer(Game()->GetConfig()->GetRandomID());

	// ���һֱ�Ǳ�ѡ��״̬
	m_pPlayer->SetSelected(true);

	m_pPlayer->setPosition(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	m_pPlayer->SetDestPoint(Point(Game()->GetConfig()->GetPlayerPosition_X(),Game()->GetConfig()->GetPlayerPosition_Y()));
	m_pPlayer->SetDirection(right_direction);
	m_pEntityLayer->addChild(m_pPlayer);

	m_pPlayer->Action(CodeMsg::code_player_static,right_direction);

	// �����ĸ����ܣ����������ﴴ����ԭ���ǡ���������Ҫ��Ҫ��
	m_pSkill_Q = m_pPlayer->GetSkill_Q();//Game()->GetSkillManager()->CreateSkill(SKILL_Q,SKILL_6_ID);
	m_pSkill_W = m_pPlayer->GetSkill_W();//Game()->GetSkillManager()->CreateSkill(SKILL_W,SKILL_2_ID);
	m_pSkill_E = m_pPlayer->GetSkill_E();//Game()->GetSkillManager()->CreateSkill(SKILL_E,SKILL_3_ID);
	m_pSkill_R = m_pPlayer->GetSkill_R();//Game()->GetSkillManager()->CreateSkill(SKILL_R,SKILL_4_ID);
	
	// 
	m_pEntityLayer->addChild(m_pSkill_Q);
	m_pEntityLayer->addChild(m_pSkill_W);
	m_pEntityLayer->addChild(m_pSkill_E);
	m_pEntityLayer->addChild(m_pSkill_R);

	// ��ȡBoss
	Monster* pBoss = Game()->GetBoss();
	pBoss->setPosition(Point(Game()->GetConfig()->GetBossPosition_X(),Game()->GetConfig()->GetBossPosition_Y()));

	m_pEntityLayer->addChild(pBoss);

	pBoss->setScale(2);

	pBoss->Action(CodeMsg::code_monster_static,down_direction);

	// �Ƿ���ʾ�����ţ����½��ģ��ս��£���û�д����ŵ�
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
	// ������Ҽ������Ļ��ʱ������Ļ����ʾĿ�ĵ�λ�õĹ�꣨һ����ɫ��СԲ�㣩
	m_pSelectCircleLight->setVisible(v);
}

void BaseScene::SkillHandler_Q()
{
	if (m_bSkill_Q_ButtonPressed)
	{
		// ������ҵ�ǰ�ļ���ΪQ����
		m_pPlayer->SetCurrentSkill(m_pSkill_Q);
		// ���ü�����Ҫʩ�ŵĵط�
		m_pSkill_Q->setPosition(m_DestPoint);
		// �˼��ܲ������������������ʩ�ţ�����Action��Ŀ�Ľ��������ö������
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