#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_

#include "define.h"
#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;
#define _USE_PC_



class Controller;

RPG_01_BEGIN

/*
** 场景基类：拥有各个场景共同的东西
*/
class BaseScene:public cocos2d::Layer
{
public:
	BaseScene();

	virtual ~BaseScene();

	CREATE_FUNC(BaseScene);

	static cocos2d::Scene* createScene();

	virtual bool					init();


public:
	void								registerMessage();													// 注册事件

	// 使用电脑的时候可以用键盘进行控制

#ifdef _USE_PC_ 
	virtual void					onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void					onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void					onMouseUp(EventMouse* e);
#endif 

	virtual void					LoadBackground();												// 加载背景图片 (加载什么样的背景需要在子类中实现)
	virtual void					LoadUI();																// 加载UI等等（加载什么样的UI，需要在子类中实现）

	void								LoadEntity();															// 加载玩家以及技能

	void								ShowDestPoint(bool v);											// 设置目的地

	void								SkillHandler_Q();														// 技能1
	void								SkillHandler_W();														// 技能2
	void								SkillHandler_E();														// 技能3
	void								SkillHandler_R();														// 技能4


	Layer*							GetBackgroundLayer();											// 获取背景层
	Layer*							GetEntityLayer();													// 获取实体层
	Layer*							GetUILayer();														// 获取UI层

	Button*						GetSkillButton_Q(){return m_pSkillButton_Q;}			// 获取技能1的按钮
	Button*						GetSkillButton_W(){return m_pSkillButton_W;}			// 获取技能2的按钮
	Button*						GetSkillButton_E(){return m_pSkillButton_E;}			// 获取技能3的按钮
	Button*						GetSkillButton_R(){return m_pSkillButton_R;}			// 获取技能4的按钮

	LoadingBar*					GetBloodProgressBar(){return m_pBloodProgressBar;}				// 获取UI的血量条
	LoadingBar*					GetMagicProgressBar(){return m_pMagicProgressBar;}				// 获取UI的魔法条
	LoadingBar*					GetEmpiricalProgressBar(){return m_pEmpiricalProgressBar;}		// 获取UI的经验值条
	LoadingBar*					GetMonsterBloodProgressBar(){return m_pMonsterBloodProgressBar;}				// 获取UI的血量条

protected:

	bool								m_bCanMove;															// 用于控制玩家的标志

	int								m_nDirection;															// 玩家移动的方向

	Point							m_DestPoint;															// 移动玩家的时候的目标地址

	Sprite*							m_pSelectCircleLight;												// 点击鼠标右键的时候显示的光圈

	Player*							m_pPlayer;																// 玩家对象（从Controller中获取）

	Layer*							m_pBackgroundLayer;												// 背景层
	Layer*							m_pEntityLayer;														// 中间的人物以及怪物层
	Layer*							m_pUILayer;																// 最上面的UI层

	Button*						m_pSkillButton_Q;													// 技能按钮1
	Button*						m_pSkillButton_W;													// 技能按钮2
	Button*						m_pSkillButton_E;														// 技能按钮3
	Button*						m_pSkillButton_R;														// 技能按钮4

	LoadingBar*					m_pBloodProgressBar;												// UI的血量条
	LoadingBar*					m_pMagicProgressBar;												// UI的魔法条
	LoadingBar*					m_pEmpiricalProgressBar;											// UI的经验值条

	LoadingBar*					m_pMonsterBloodProgressBar;									// UI的怪物血量条

	Skill*								m_pSkill_Q;																	// 技能1
	Skill*								m_pSkill_W;																	// 技能2
	Skill*								m_pSkill_E;																	// 技能3
	Skill*								m_pSkill_R;																	// 技能4

	bool								m_bSkill_Q_ButtonPressed;											// 技能1按钮是否被按下（按了技能按钮然后点击鼠标左键才能释放魔法）
	bool								m_bSkill_W_ButtonPressed;											// 技能2按钮是否被按下（按了技能按钮然后点击鼠标左键才能释放魔法）
	bool								m_bSkill_E_ButtonPressed;											// 技能3按钮是否被按下（按了技能按钮然后点击鼠标左键才能释放魔法）
	bool								m_bSkill_R_ButtonPressed;											// 技能4按钮是否被按下（按了技能按钮然后点击鼠标左键才能释放魔法）

};
RPG_01_END



#endif //_MAIN_SCENE_H_