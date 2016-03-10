#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace cocos2d::ui;

#include "define.h"
#include "LuaHandler.h"

USING_NS_CC; 


// 表示游戏中的一个块
struct BLOCK
{
	BLOCK()
	{
		m_pNode = NULL;
		m_nX = -1;
		m_nY = -1;
		m_bVisibale = false;
		m_nValue = 0;
	}

	cocos2d::extension::ControlButton * m_pNode;

	int								m_nX;
	int								m_nY;
	int								m_nValue;
	bool								m_bVisibale;	
};

typedef BLOCK* PBLOCK;

typedef vector<BLOCK*>	 VecBlockIter;

class MainScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

public:

	void											registerEvent();													// 注册事件

	bool virtual								touchBegan(Touch*touch,Event*event);			// 触摸函数
	void virtual								touchMoved(Touch *touch,Event *event);			// 触摸移动函数
	void virtual								touchEnded(Touch *touch,Event *event);			// 触摸结束函数
	void virtual								touchCancelled(Touch*touch,Event *event);


	
#ifdef _USE_PC_ // 使用电脑的时候可以用键盘进行控制
	void											onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void											onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void											onMouseUp(EventMouse* e);
#endif // _USE_PC_


	// test all begin
	void											PlayMusic();
	void											PlayEffect();
	void 								            onClick(Ref * pRef, TouchEventType type);
	void											UseLua();
	static int									UseByLua(int num);
	
	static int									cpp_GetNum(lua_State* pL);
	// test all end
private:

	BLOCK*									GenerateBlock();

	void											LoadBackGround();

	Direction									GetMoveDirection();

	BLOCK*									GetUnUsedBlock();

	void											ShowBlock(BLOCK* pBlock);

	void											ShowScore();

	Point										CalculateBlockPosition(BLOCK* pBlock);

	void											MoveUp();

	void											MoveDown();

	void											MoveLeft();

	void											MoveRight();

	bool											CheckGameCanContinue();

	void											GameOver();

	string										GetPicName(int num);

private:

	BLOCK										m_BlockMap[TOTAL_BLOCK_NUM][TOTAL_BLOCK_NUM];

	vector<BLOCK*>						m_UnUsedBlockList;

	Size											m_WinVisibleSize;

	Point										m_PrePoint;

	Point										m_CurrentPoint;

	Direction									m_nDirection;

	int											m_nUpBoundary;

	int											m_nDownBoundary;

	int											m_nLeftBoundary;

	int											m_nRightBoundary;

	unsigned long long					m_nScore;

	cocos2d::extension::ControlButton*		m_pScoreNode ;

	bool											m_bGameOver;

	LuaHandler								m_LuaHandler;
};

#endif // 
