#include "LoginScene.h"
#include "NetworkModule.h"
#include "Controller.h"
#include "Config.h"
#include "Player.h"

Scene* LoginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoginScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	RPG_01::Game()->GetNetworkModule()->ConnectToServer(RPG_01::Game()->GetConfig()->GetServerIP().c_str(),RPG_01::Game()->GetConfig()->GetServerPort());

	m_pLoginSceneUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("RPG_Resource/xUi/Connect2Server/Connect2Server.ExportJson");

	addChild(m_pLoginSceneUI,5);

	initButton();
}

void LoginScene::initButton()
{
	connectButton[0] = (Button*)Helper::seekWidgetByTag(m_pLoginSceneUI,530);

	connectButton[1] = (Button*)Helper::seekWidgetByTag(m_pLoginSceneUI,533);

	connectButton[0]->addTouchEventListener(this,toucheventselector(LoginScene::Login));

	connectButton[1]->addTouchEventListener(this,toucheventselector(LoginScene::Cancel));

	input[0] = (TextField*)Helper::seekWidgetByTag(m_pLoginSceneUI, 526);

	input[1] = (TextField*)Helper::seekWidgetByTag(m_pLoginSceneUI, 528);

}

bool LoginScene::Login(Ref*item, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		{
			
			string strID = input[0]->getStringValue();
			string strPsd = input[1]->getStringValue();
	
			if (RPG_01::Game()->GetNetworkModule()->Login(strID,strPsd))
			{
				RPG_01::Game()->Init(strID,strPsd,true);

				return true;
			}
			else
			{
				return false;
			}
		}
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	}
}

void LoginScene::Cancel(Ref*item, TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		{
			//Director::getInstance()->end();

			string strID = input[0]->getStringValue();
			string strPsd = input[1]->getStringValue();
			RPG_01::Game()->Init(strID,strPsd,false);

			break;
		}

	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	}
}
