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
** ʵ���ࣺ��ҡ����֡�boss��Ѫƿ�ȵȶ�Ҫ�̳�����
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
	void					SetSelected(bool v);									// ���ø���Ʒ�Ƿ�ѡ��

	void					SetScope(float nWidth,float high);
	Rect					GetScope();

	void					SetID(const string& strID);
	string&				GetID();
protected:
	string				m_strID;
	Sprite*				m_pSprite;												// ��ʾʵ��ľ���
	Sprite*				m_pCircleLight;											// ��ʵ��ײ���ʾ�Ĺ�Ȧ����ʾ��ѡ�У���ѡ��ʱ����ʾ��
	ProgressView*	m_pBloodProgress;									// Ѫ������һЩ��Ʒ����Ѫƿ�������ȿ��ܲ���Ҫ�����Խ�������
	float					m_fScopeWidth;										// ��ʵ���˽����ء�����ȣ��������������ǻᷢ��һЩ��Ϊ���繥����
	float					m_fScopeHeight;										// ͬ�ϣ��߶�
private:

};

RPG_01_END
#endif // !_ENTITY_H_
