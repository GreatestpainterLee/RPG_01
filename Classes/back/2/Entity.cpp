#include "Entity.h"
#include "./widget/ProgressView.h"
#include "FlowWord.h"

RPG_01_BEGIN

	Entity::Entity()
{

	m_strID = "";
	m_pSprite = 0;												// 表示实体的精灵
	m_pCircleLight = 0;										// 在实体底部显示的光圈，表示被选中，被选中时候显示它
	m_pBloodProgress = 0;									// 血条，有一些物品例如血瓶、武器等可能不需要，可以将其隐藏
	m_fScopeWidth = 0;										// 该实体的私人领地——宽度，外物进入该领域是会发生一些行为例如攻击等
	m_fScopeHeight = 0;										// 同上，高度

	init();
}

/************************************************************************
*  技初始化函数
************************************************************************/
bool Entity::init()
{
	m_pSprite = Sprite::create();

	// 初始化血条
	m_pBloodProgress =  ProgressView::create();
	m_pBloodProgress->InitProgress("RPG_Resource/ui/blood_box.png","RPG_Resource/ui/blood_in.png",1.0);
	m_pBloodProgress->setScale(0.2);
	m_pBloodProgress->setPosition(6,90);
	this->addChild(m_pBloodProgress);

	// 初始化被选中时显示的光圈
	m_pCircleLight =Sprite::create("RPG_Resource/ui/tray_self.png");

	m_pCircleLight->setScale(0.6);
	m_pCircleLight->setPosition(10,-20);

	this->addChild(m_pCircleLight);
	this->addChild(m_pSprite);

	m_pCircleLight->setVisible(false);

	m_pBloodProgress->setVisible(false);

	// 设置默认的领地
	SetScope(128,128);

	return true;
}

/************************************************************************
*  获取表示实体的精灵
************************************************************************/
Sprite* Entity::GetSprite()
{
	return m_pSprite;
}

/************************************************************************
*  技设置实体是否被选中，被选中则显示光圈
************************************************************************/
void Entity::SetSelected(bool v)
{
	if(v)
	{
		m_pCircleLight->setVisible(true);
	}
	else
	{
		m_pCircleLight->setVisible(false);
	}
}

/************************************************************************
*  设置实体的领地
************************************************************************/
void Entity::SetScope(float nWidth,float high)
{
	Rect rect(getPosition().x-nWidth/2,getPosition().y-high/2,nWidth,high);

	m_fScopeWidth = nWidth;
	m_fScopeHeight = high;

}

/************************************************************************
*  获得实体的领地（即它的个人空间）
************************************************************************/
Rect Entity::GetScope()
{
	Rect rect(getPosition().x-m_fScopeWidth/2,getPosition().y-m_fScopeHeight/2,m_fScopeWidth,m_fScopeHeight);
	return rect;
}

void Entity::SetID(const string& strID)
{
	m_strID = strID;
}

string& Entity::GetID()
{
	return m_strID;
}

RPG_01_END