#include "Entity.h"
#include "./widget/ProgressView.h"
#include "FlowWord.h"

RPG_01_BEGIN

	Entity::Entity()
{

	m_strID = "";
	m_pSprite = 0;												// ��ʾʵ��ľ���
	m_pCircleLight = 0;										// ��ʵ��ײ���ʾ�Ĺ�Ȧ����ʾ��ѡ�У���ѡ��ʱ����ʾ��
	m_pBloodProgress = 0;									// Ѫ������һЩ��Ʒ����Ѫƿ�������ȿ��ܲ���Ҫ�����Խ�������
	m_fScopeWidth = 0;										// ��ʵ���˽����ء�����ȣ��������������ǻᷢ��һЩ��Ϊ���繥����
	m_fScopeHeight = 0;										// ͬ�ϣ��߶�

	init();
}

/************************************************************************
*  ����ʼ������
************************************************************************/
bool Entity::init()
{
	m_pSprite = Sprite::create();

	// ��ʼ��Ѫ��
	m_pBloodProgress =  ProgressView::create();
	m_pBloodProgress->InitProgress("RPG_Resource/ui/blood_box.png","RPG_Resource/ui/blood_in.png",1.0);
	m_pBloodProgress->setScale(0.2);
	m_pBloodProgress->setPosition(6,90);
	this->addChild(m_pBloodProgress);

	// ��ʼ����ѡ��ʱ��ʾ�Ĺ�Ȧ
	m_pCircleLight =Sprite::create("RPG_Resource/ui/tray_self.png");

	m_pCircleLight->setScale(0.6);
	m_pCircleLight->setPosition(10,-20);

	this->addChild(m_pCircleLight);
	this->addChild(m_pSprite);

	m_pCircleLight->setVisible(false);

	m_pBloodProgress->setVisible(false);

	// ����Ĭ�ϵ����
	SetScope(128,128);

	return true;
}

/************************************************************************
*  ��ȡ��ʾʵ��ľ���
************************************************************************/
Sprite* Entity::GetSprite()
{
	return m_pSprite;
}

/************************************************************************
*  ������ʵ���Ƿ�ѡ�У���ѡ������ʾ��Ȧ
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
*  ����ʵ������
************************************************************************/
void Entity::SetScope(float nWidth,float high)
{
	Rect rect(getPosition().x-nWidth/2,getPosition().y-high/2,nWidth,high);

	m_fScopeWidth = nWidth;
	m_fScopeHeight = high;

}

/************************************************************************
*  ���ʵ�����أ������ĸ��˿ռ䣩
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