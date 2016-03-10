#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "ui\CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"

#include "define.h"

USING_NS_CC;

class ProgressView;
class FlowWord;
RPG_01_BEGIN
/*
** 实体类：玩家、妖怪、boss，血瓶等等都要继承自他
*/
class Entity:public cocos2d::Node
{
public:
	friend class ActionManager;

	Entity();
	virtual ~Entity(){}

	X_CREATE_FUNC(Entity);

	virtual bool		init();

	Sprite*				GetSprite();
	void					SetSelected(bool v);									// 设置该物品是否被选中

	void					SetScope(float nWidth,float high);
	Rect					GetScope();

	void					SetID(const string& strID);
	string&				GetID();
protected:
	string				m_strID;
	Sprite*				m_pSprite;												// 表示实体的精灵
	Sprite*				m_pCircleLight;											// 在实体底部显示的光圈，表示被选中，被选中时候显示它
	ProgressView*	m_pBloodProgress;									// 血条，有一些物品例如血瓶、武器等可能不需要，可以将其隐藏
	float					m_fScopeWidth;										// 该实体的私人领地——宽度，外物进入该领域是会发生一些行为例如攻击等
	float					m_fScopeHeight;										// 同上，高度
private:

};

RPG_01_END
#endif // !_ENTITY_H_
