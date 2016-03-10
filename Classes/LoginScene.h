#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_



#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "ui\UIWidget.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class LoginScene :public Layer
{
public:

	virtual bool init();

	static Scene* createScene();

	CREATE_FUNC(LoginScene);

	/*��ʼ������*/
	void initButton();

	/*���ӷ�����*/
	bool Login(Ref*,TouchEventType);

	/*���ؿ�ʼ����*/
	void Cancel(Ref*,TouchEventType);
protected:
	cocos2d::ui::Widget* m_pLoginSceneUI ;
	Button* connectButton[2]; 

	TextField* input[2];
};


#endif