#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "ui\CocosGUI.h"

#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

using namespace cocostudio::timeline;

#include "MainScene.h"
#include "define.h"
#include "Util.h"

// 使用lua
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};


Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	/*lua_State* pL = m_LuaHandler.GetLuaState();

	lua_register(pL, "cpp_GetNum", cpp_GetNum);
	luaL_dofile(pL, "call_by_cpp.lua");

	// UseLua();
	auto pUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("login_1.ExportJson");
	pUI->setPosition(Point(0, 0));
	this->addChild(pUI);

	Button* pLoginButton = (Button*)(Helper::seekWidgetByName(pUI,"Login_Button"));
	pLoginButton->addTouchEventListener(this, toucheventselector(MainScene::onClick));*/

	TMXTiledMap* pMap = TMXTiledMap::create("LFR/other/map/map1.tmx");//LFR/other/map/
	this->addChild(pMap);

	auto b = pMap->getLayer("barrier");
	int til = 0;
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			til = b->getTileGIDAt(Point(i,j));
			if (til == 0)
			{
				continue;
			}
			Value pro = pMap->getPropertiesForGID(til);
			Value v = pro.asValueMap().at("Collidable");
		}
	}

	
	

	TMXObjectGroup* objG = pMap->getObjectGroup("objects");
	ValueMap vm = objG->getObject("g1");
	float x = vm.at("x").asFloat();

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile("RPG_Resource/texture_figure/char_11001.plist","RPG_Resource/texture_figure/char_11001.png");

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	// char_11001_1_%d_0%d.png 转向
	// char_11001_2_%d_0%d.png 走路
	// char_11001_2_%d_0%d.png 奔跑
	// char_11001_4_%d_0%d.png 攻击
	// char_11001_5_%d_0%d.png 投掷
	// char_11001_6_%d_0%d.png 看不出是什么
	// char_11001_7_%d_0%d.png 从地上爬起来
	// char_11001_8_%d_0%d.png 受伤了

	for (int i = 2; i <=2; ++i)
	{
		for (int j = 0; j < 2;++j)
		{
			frame = frameCache->getSpriteFrameByName(StringUtils::format("char_11001_8_%d_0%d.png",i,j));//char_11001_2_%d_0%d.png
			frameList.pushBack(frame);
		}

	/*	for (int j = 10; j < 16;++j)
		{
			frame = frameCache->getSpriteFrameByName(StringUtils::format("char_11001_4_%d_%d.png",i,j));//char_11001_2_%d_0%d.png
			frameList.pushBack(frame);
		}*/
	}
	
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1);

	Animate* animate = Animate::create(animation);

	auto sprite = Sprite::create();
	this->addChild(sprite);
	sprite->setPosition(Point(100,200));
	sprite->runAction(animate);


	Texture2D* pTexture = NULL;
	Vector<SpriteFrame*> vec;
	pTexture = TextureCache::getInstance()->addImage(("RPG_Resource/1-1.png"));

	for(int i = 1;i < (4); ++i)
	{
		SpriteFrame* sf = SpriteFrame::createWithTexture(pTexture,Rect(0,i * (64),(64),(64)));
		vec.pushBack(sf);
	}

	animation = Animation::createWithSpriteFrames(vec,(0.1));
	animation->setLoops(-1);
	animate = Animate::create(animation);
	auto sp1 = Sprite::create();
	sp1->setPosition(Point(100,300));
	addChild(sp1);

	sp1->runAction(animate);
	return true;
}

void MainScene::UseLua()
{
	lua_State* pL = lua_open();

	luaopen_base(pL);

	luaopen_math(pL);

	luaopen_string(pL);

	int err = luaL_dofile(pL,"call_by_cpp.lua");

	CCLOG("open:%d\n",err);

	lua_settop(pL, 0);
	lua_getglobal(pL, "myName");

	err = lua_isstring(pL, 1);
	CCLOG("isstr:%d\n", err);

	if (err != 0)
	{
		string str = lua_tostring(pL, 1);
		CCLOG(str.c_str());
	}

	lua_getglobal(pL, "myTable");
	lua_pushstring(pL, "id");
	lua_gettable(pL,-2);
	string str = lua_tostring(pL, -1);
	if (err != 0)
	{
	}

	lua_close(pL);
}

int MainScene::UseByLua(int num)
{
	return num + 1;
}

int MainScene::cpp_GetNum(lua_State* pL)
{
	int num = (int)lua_tonumber(pL, 1);

	CCLOG("call by lua");
	lua_pushnumber(pL, UseByLua(num));

	return 1;
}

void MainScene::onClick(Ref * pRef, TouchEventType type)
{
	CCLOG("click\n");
}

/************************************************************************
*  注册事件
************************************************************************/
void MainScene::registerEvent()
{

#ifdef _USE_PC_ // 使用电脑的时候
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	auto _mouseListener = EventListenerMouse::create();
	// 鼠标右键消息
	_mouseListener->onMouseUp = [=](Event *event)
	{
		EventMouse* e = (EventMouse*)event;
		onMouseUp(e);
	};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener,this);//addEventListenerWithSceneGraphPriority(_mouseListener,this);
#endif
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(false);

	listener->onTouchBegan = CC_CALLBACK_2(MainScene::touchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(MainScene::touchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(MainScene::touchEnded,this);
	listener->onTouchCancelled = CC_CALLBACK_2(MainScene::touchCancelled,this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener,-255);

}

void MainScene::LoadBackGround()
{
}

BLOCK* MainScene::GenerateBlock()
{
	BLOCK* pBlock = GetUnUsedBlock();

	if (pBlock == 0)
	{
		return 0;
	}

	pBlock->m_bVisibale = true;

	pBlock->m_nValue = 2;

	double probability =  Util::GetProbability();

	if (probability > PROBABILITY_OF_2)
	{
		pBlock->m_nValue = 4;
	}

	ShowBlock(pBlock);

	return pBlock;
}

void MainScene::ShowBlock(BLOCK* pBlock)
{

	string strNum = Util::ConvertToStr(pBlock->m_nValue);

	string strPicName = GetPicName(pBlock->m_nValue);

	cocos2d::ui::Scale9Sprite *	pBlockSprite = cocos2d::ui::Scale9Sprite::create(strPicName);

	LabelTTF * pLabel= LabelTTF::create(strNum, "Arial", 25);

	pBlock->m_pNode = cocos2d::extension::ControlButton::create(pLabel , pBlockSprite);

	pBlock->m_pNode->setPreferredSize(Size(BLOCK_SIZE,BLOCK_SIZE));

	pBlock->m_pNode->setPosition(Vec2((BLOCK_SIZE / 2) + pBlock->m_nX* BLOCK_SIZE,(BLOCK_SIZE / 2)+ pBlock->m_nY * BLOCK_SIZE));

	pBlock->m_pNode->setTag(0);

	this->addChild(pBlock->m_pNode);
}


void MainScene::ShowScore()
{
	this->removeChild(m_pScoreNode);

	string strNum = Util::ConvertToStr((long long)m_nScore);

	cocos2d::ui::Scale9Sprite *	pBlockSprite = cocos2d::ui::Scale9Sprite::create("");

	LabelTTF * pLabel= LabelTTF::create(strNum, "Arial", 40);

	m_pScoreNode = cocos2d::extension::ControlButton::create(pLabel , pBlockSprite);

	m_pScoreNode->setPreferredSize(Size(BLOCK_SIZE,BLOCK_SIZE));

	m_pScoreNode->setPosition(m_WinVisibleSize.width/2,m_WinVisibleSize.height - 30);

	m_pScoreNode->setTag(256);

	this->addChild(m_pScoreNode , 256);
}

BLOCK* MainScene::GetUnUsedBlock()
{
	m_UnUsedBlockList.clear();

	for (int i = 1; i < TOTAL_BLOCK_NUM - 1; ++i)
	{
		for (int j = 1; j < TOTAL_BLOCK_NUM - 1;++j)
		{
			if (m_BlockMap[i][j].m_bVisibale == false)
			{
				m_BlockMap[i][j].m_nX = i;
				m_BlockMap[i][j].m_nY = j;
				m_BlockMap[i][j].m_nValue = 0;
				m_UnUsedBlockList.push_back(&m_BlockMap[i][j]);
			}
		}
	}

	if (m_UnUsedBlockList.size() == 0)
	{
		return 0;
	}

	int index = Util::GetRandomNum(0,m_UnUsedBlockList.size());

	vector<BLOCK*>::iterator it = m_UnUsedBlockList.begin() + index;

	BLOCK* pBlock = (*it);



	m_UnUsedBlockList.erase(it);


	return pBlock;
}

Point MainScene::CalculateBlockPosition(BLOCK* pBlock)
{
	Point point;
	point.x = pBlock->m_nX * BLOCK_SIZE + (BLOCK_SIZE / 2);
	point.y = pBlock->m_nY * BLOCK_SIZE + (BLOCK_SIZE / 2);
	return point;
}

/************************************************************************
*  开始触摸屏幕或者点击鼠标左键，都没有实现，因为这些事件是在摇杆里面进行处理的
************************************************************************/
bool MainScene::touchBegan(Touch*touch,Event*event)
{
	m_PrePoint = touch->getLocation();
	return true;
}

void MainScene::touchMoved(Touch *touch,Event *event)
{
}

void MainScene::touchEnded(Touch *touch,Event *event)
{
	if (m_bGameOver)
	{
		return;
	}

	m_CurrentPoint = touch->getLocation();

	m_nDirection = GetMoveDirection();

	switch (m_nDirection)
	{
	case static_direction:
		log("static_direction");
		break;
	case left_direction:
		MoveLeft();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	case right_direction:
		MoveRight();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	case up_direction:
		MoveUp();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	case down_direction:
		MoveDown();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	default:
		break;
	}
}

Direction MainScene::GetMoveDirection()
{
	int nXDistance = 0;
	int nYDistance = 0;

	if (m_CurrentPoint.x > m_PrePoint.x)
	{
		nXDistance = m_CurrentPoint.x - m_PrePoint.x;

		m_nDirection = right_direction;
	}
	else
	{
		nXDistance = m_PrePoint.x - m_CurrentPoint.x;

		m_nDirection = left_direction;
	}


	Direction tempDirection = static_direction;

	if (m_CurrentPoint.y > m_PrePoint.y)
	{
		nYDistance = m_CurrentPoint.y - m_PrePoint.y;

		tempDirection = up_direction;
	}
	else
	{
		nYDistance = m_PrePoint.y - m_CurrentPoint.y;

		tempDirection = down_direction;
	}

	if (nYDistance > nXDistance)
	{
		m_nDirection = tempDirection;
	}

	return m_nDirection;
}


void MainScene::MoveUp()
{
	for (int x = 1; x < TOTAL_BLOCK_NUM - 1; ++x)
	{
		int nValueArray[TOTAL_BLOCK_NUM] = {0};
		int nValueArrayCount = 0;

		// 将原来的块从屏幕中移除
		// 并记录对应块的值
		for (int y = TOTAL_BLOCK_NUM - 2; y >=  1; --y)
		{
			if(m_BlockMap[x][y].m_bVisibale)
			{
				nValueArray[nValueArrayCount++] = m_BlockMap[x][y].m_nValue;
				m_BlockMap[x][y].m_bVisibale = false;
				removeChild(m_BlockMap[x][y].m_pNode);
				m_BlockMap[x][y].m_nValue = 0;
			}
		}

		if (nValueArrayCount == 0)
		{
			continue;
		}

		if (nValueArrayCount > 1)
		{
			// 如果相邻块的值相同，那么合并
			for (int i = 0; i < nValueArrayCount - 1; ++i)
			{
				if (nValueArray[i] == 0)
				{
					continue;
				}

				if ( nValueArray[i] == nValueArray[i + 1])
				{
					nValueArray[i] *= 2;
					nValueArray[i + 1] = 0;
					m_nScore += nValueArray[i];
				}
			}
		}

		// 存放计算之后的值
		int nRealArray[TOTAL_BLOCK_NUM] = {0};
		int nRealArrayCount = 0;

		for (int i = 0; i < nValueArrayCount; ++i)
		{
			if (nValueArray[i] == 0)
			{
				continue;
			}
			nRealArray[nRealArrayCount++] = nValueArray[i];
		}

		// 重新在屏幕中显示块
		int index = 0;
		int realY = TOTAL_BLOCK_NUM - 2;
		while (index < nRealArrayCount)
		{
			m_BlockMap[x][realY].m_nValue = nRealArray[index];
			m_BlockMap[x][realY].m_bVisibale = true;
			m_BlockMap[x][realY].m_nX = x;
			m_BlockMap[x][realY].m_nY = realY;

			ShowBlock(&m_BlockMap[x][realY]);
			++index;
			--realY;
		}
	}
}

void MainScene::MoveDown()
{
	for (int x = 1; x < TOTAL_BLOCK_NUM - 1; ++x)
	{
		int nValueArray[TOTAL_BLOCK_NUM] = {0};
		int nValueArrayCount = 0;

		// 将原来的块从屏幕中移除
		// 并记录对应块的值
		for (int y = 1; y < TOTAL_BLOCK_NUM - 1; ++y)
		{
			if(m_BlockMap[x][y].m_bVisibale)
			{
				nValueArray[nValueArrayCount++] = m_BlockMap[x][y].m_nValue;
				m_BlockMap[x][y].m_bVisibale = false;
				removeChild(m_BlockMap[x][y].m_pNode);
				m_BlockMap[x][y].m_nValue = 0;
			}
		}

		if (nValueArrayCount == 0)
		{
			continue;
		}

		if (nValueArrayCount > 1)
		{
			// 如果相邻块的值相同，那么合并
			for (int i = 0; i < nValueArrayCount - 1; ++i)
			{
				if (nValueArray[i] == 0)
				{
					continue;
				}

				if ( nValueArray[i] == nValueArray[i + 1])
				{
					nValueArray[i] *= 2;
					nValueArray[i + 1] = 0;
					m_nScore += nValueArray[i];
				}

			}
		}

		// 存放计算之后的值
		int nRealArray[TOTAL_BLOCK_NUM] = {0};
		int nRealArrayCount = 0;

		for (int i = 0; i < nValueArrayCount; ++i)
		{
			if (nValueArray[i] == 0)
			{
				continue;
			}
			nRealArray[nRealArrayCount++] = nValueArray[i];
		}

		// 重新在屏幕中显示块
		int index = 0;
		int realY = 1;
		while (index < nRealArrayCount)
		{
			m_BlockMap[x][realY].m_nValue = nRealArray[index];
			m_BlockMap[x][realY].m_bVisibale = true;
			m_BlockMap[x][realY].m_nX = x;
			m_BlockMap[x][realY].m_nY = realY;

			ShowBlock(&m_BlockMap[x][realY]);

			++index;
			++realY;
		}
	}
}

void MainScene::MoveLeft()
{
	for (int y = 1; y < TOTAL_BLOCK_NUM - 1; ++y)
	{
		int nValueArray[TOTAL_BLOCK_NUM] = {0};
		int nValueArrayCount = 0;

		// 将原来的块从屏幕中移除
		// 并记录对应块的值
		for (int x = 1; x < TOTAL_BLOCK_NUM - 1; ++x)
		{
			if(m_BlockMap[x][y].m_bVisibale)
			{
				nValueArray[nValueArrayCount++] = m_BlockMap[x][y].m_nValue;
				m_BlockMap[x][y].m_bVisibale = false;
				removeChild(m_BlockMap[x][y].m_pNode);
				m_BlockMap[x][y].m_nValue = 0;
			}
		}

		if (nValueArrayCount == 0)
		{
			continue;
		}

		if (nValueArrayCount > 1)
		{
			// 如果相邻块的值相同，那么合并
			for (int i = 0; i < nValueArrayCount - 1; ++i)
			{
				if (nValueArray[i] == 0)
				{
					continue;
				}

				if ( nValueArray[i] == nValueArray[i + 1])
				{
					nValueArray[i] *= 2;
					nValueArray[i + 1] = 0;
					m_nScore += nValueArray[i];
				}
			}
		}

		// 存放计算之后的值
		int nRealArray[TOTAL_BLOCK_NUM] = {0};
		int nRealArrayCount = 0;

		for (int i = 0; i < nValueArrayCount; ++i)
		{
			if (nValueArray[i] == 0)
			{
				continue;
			}
			nRealArray[nRealArrayCount++] = nValueArray[i];
		}

		// 重新在屏幕中显示块
		int index = 0;
		int realX = 1;
		while (index < nRealArrayCount)
		{
			m_BlockMap[realX][y].m_nValue = nRealArray[index];
			m_BlockMap[realX][y].m_bVisibale = true;
			m_BlockMap[realX][y].m_nX = realX;
			m_BlockMap[realX][y].m_nY = y;

			ShowBlock(&m_BlockMap[realX][y]);

			++index;
			++realX;
		}
	}
}

void MainScene::MoveRight()
{
	for (int y = 1; y < TOTAL_BLOCK_NUM - 1; ++y)
	{
		int nValueArray[TOTAL_BLOCK_NUM] = {0};
		int nValueArrayCount = 0;

		// 将原来的块从屏幕中移除
		// 并记录对应块的值
		for (int x = TOTAL_BLOCK_NUM- 2 ; x  >= 1; --x)
		{
			if(m_BlockMap[x][y].m_bVisibale)
			{
				nValueArray[nValueArrayCount++] = m_BlockMap[x][y].m_nValue;
				m_BlockMap[x][y].m_bVisibale = false;
				removeChild(m_BlockMap[x][y].m_pNode);
				m_BlockMap[x][y].m_nValue = 0;
			}
		}

		if (nValueArrayCount == 0)
		{
			continue;
		}

		if (nValueArrayCount > 1)
		{
			// 如果相邻块的值相同，那么合并
			for (int i = 0; i < nValueArrayCount - 1; ++i)
			{
				if (nValueArray[i] == 0)
				{
					continue;
				}

				if ( nValueArray[i] == nValueArray[i + 1])
				{
					nValueArray[i] *= 2;
					nValueArray[i + 1] = 0;
					m_nScore += nValueArray[i];
				}
			}
		}

		// 存放计算之后的值
		int nRealArray[TOTAL_BLOCK_NUM] = {0};
		int nRealArrayCount = 0;

		for (int i = 0; i < nValueArrayCount; ++i)
		{
			if (nValueArray[i] == 0)
			{
				continue;
			}
			nRealArray[nRealArrayCount++] = nValueArray[i];
		}

		// 重新在屏幕中显示块
		int index = 0;
		int realX = TOTAL_BLOCK_NUM - 2;
		while (index < nRealArrayCount)
		{
			m_BlockMap[realX][y].m_nValue = nRealArray[index];
			m_BlockMap[realX][y].m_bVisibale = true;
			m_BlockMap[realX][y].m_nX = realX;
			m_BlockMap[realX][y].m_nY = y;
			ShowBlock(&m_BlockMap[realX][y]);
			++index;
			--realX;
		}
	}
}

void MainScene::touchCancelled(Touch*touch,Event*event)
{
}

/************************************************************************
*  鼠标右键的处理函数
************************************************************************/

#ifdef _USE_PC_

void MainScene::onMouseUp(EventMouse* event)
{
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	m_nDirection = up_direction;
	MoveUp();
	break;
	case EventKeyboard::KeyCode::KEY_D:
	m_nDirection = right_direction;
	MoveRight();
	break;
	case EventKeyboard::KeyCode::KEY_S:
	m_nDirection = down_direction;
	MoveDown();
	break;
	case EventKeyboard::KeyCode::KEY_A:
	m_nDirection = left_direction;
	MoveLeft();
	break;
	default:
	break;
	}*/
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (m_bGameOver)
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		m_nDirection = up_direction;
		MoveUp();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_nDirection = right_direction;
		MoveRight();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_nDirection = down_direction;
		MoveDown();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_nDirection = left_direction;
		MoveLeft();
		ShowScore();
		GenerateBlock();
		if(!CheckGameCanContinue())
		{
			m_bGameOver = true;
			GameOver();
		}
		break;
	default:
		break;
	}
}


void MainScene::GameOver()
{
	cocos2d::ui::Scale9Sprite *	pBlockSprite = cocos2d::ui::Scale9Sprite::create("");

	LabelTTF * pLabel= LabelTTF::create("Game Over!", "Arial", 50);

	auto pNode = cocos2d::extension::ControlButton::create(pLabel , pBlockSprite);

	pNode->setPreferredSize(Size(BLOCK_SIZE,BLOCK_SIZE));

	pNode->setPosition(Vec2(m_WinVisibleSize.width/2,m_WinVisibleSize.height / 2));

	pNode->setTag(0);

	this->addChild(pNode);
}

bool MainScene::CheckGameCanContinue()
{
	for (int x = 1; x < TOTAL_BLOCK_NUM - 1; ++x)
	{
		for (int y = 1; y < TOTAL_BLOCK_NUM - 1; ++y)
		{
			if (m_BlockMap[x][y].m_nValue == 0)
			{
				return true;
			}
			

			if (x == 1)		// 左边界
			{
				if (y == 1) // 左下角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x + 1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y +1].m_nValue)
					{
						return true;
					}
				}
				else if (y == TOTAL_BLOCK_NUM - 2) // 左上角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x][y - 1].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x + 1][y].m_nValue
						)
					{
						return true;
					}
				}
				else // 普通左边界
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x+1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y+1].m_nValue ||
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y-1].m_nValue
						)
					{
						return true;
					}
				}				
			}

			if (x == TOTAL_BLOCK_NUM - 2) // 右边界
			{
				if (y == 1) // 右下角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue ||
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y + 1].m_nValue
						)
					{
						return true;
					}

				}
				else if (y == TOTAL_BLOCK_NUM - 2) // 右上角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y - 1].m_nValue
						)
					{
						return true;
					}

				}
				else // 普通右边界
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y + 1].m_nValue ||
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y - 1].m_nValue)
					{
						return true;
					}
				}
			}
		
			//////

			if (y == 1)		// 下边界
			{
				if (x == 1) // 左下角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x + 1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y +1].m_nValue)
					{
						return true;
					}
				}
				else if (x == TOTAL_BLOCK_NUM - 2) // 左上角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x][y - 1].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x + 1][y].m_nValue
						)
					{
						return true;
					}
				}
				else // 普通下边界
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x+1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue ||
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y +1].m_nValue
						)
					{
						return true;
					}
				}				
			}

			if (y == TOTAL_BLOCK_NUM - 2) // 上边界
			{
				if (x == 1) // 右下角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue ||
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y + 1].m_nValue
						)
					{
						return true;
					}

				}
				else if (x == TOTAL_BLOCK_NUM - 2) // 右上角
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y - 1].m_nValue
						)
					{
						return true;
					}

				}
				else // 普通上边界
				{
					if (m_BlockMap[x][y].m_nValue == m_BlockMap[x - 1][y].m_nValue || 
						m_BlockMap[x][y].m_nValue == m_BlockMap[x + 1][y ].m_nValue ||
						m_BlockMap[x][y].m_nValue == m_BlockMap[x][y - 1].m_nValue)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

string MainScene::GetPicName(int num)
{
	
	if (num == 2)
	{
		return "image/2.png";
	}

	if (num == 4)
	{
		return "image/4.png";
	}

	if (num == 8)
	{
		return "image/8.png";
	}

	if (num == 16)
	{
		return "image/16.png";
	}

	if (num == 32)
	{
		return "image/32.png";
	}

	if (num == 64)
	{
		return "image/64.png";
	}

	if (num == 128)
	{
		return "image/128.png";
	}

	if (num == 256)
	{
		return "image/256.png";
	}

	if (num == 512)
	{
		return "image/512.png";
	}

	if (num == 1024)
	{
		return "image/1024.png";
	}

	if (num == 2048)
	{
		return "image/2048.png";
	}
}
#endif