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
** �������ࣺӵ�и���������ͬ�Ķ���
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
	void								registerMessage();													// ע���¼�

	// ʹ�õ��Ե�ʱ������ü��̽��п���

#ifdef _USE_PC_ 
	virtual void					onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void					onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void					onMouseUp(EventMouse* e);
#endif 

	virtual void					LoadBackground();												// ���ر���ͼƬ (����ʲô���ı�����Ҫ��������ʵ��)
	virtual void					LoadUI();																// ����UI�ȵȣ�����ʲô����UI����Ҫ��������ʵ�֣�

	void								LoadEntity();															// ��������Լ�����

	void								ShowDestPoint(bool v);											// ����Ŀ�ĵ�

	void								SkillHandler_Q();														// ����1
	void								SkillHandler_W();														// ����2
	void								SkillHandler_E();														// ����3
	void								SkillHandler_R();														// ����4


	Layer*							GetBackgroundLayer();											// ��ȡ������
	Layer*							GetEntityLayer();													// ��ȡʵ���
	Layer*							GetUILayer();														// ��ȡUI��

	Button*						GetSkillButton_Q(){return m_pSkillButton_Q;}			// ��ȡ����1�İ�ť
	Button*						GetSkillButton_W(){return m_pSkillButton_W;}			// ��ȡ����2�İ�ť
	Button*						GetSkillButton_E(){return m_pSkillButton_E;}			// ��ȡ����3�İ�ť
	Button*						GetSkillButton_R(){return m_pSkillButton_R;}			// ��ȡ����4�İ�ť

	LoadingBar*					GetBloodProgressBar(){return m_pBloodProgressBar;}				// ��ȡUI��Ѫ����
	LoadingBar*					GetMagicProgressBar(){return m_pMagicProgressBar;}				// ��ȡUI��ħ����
	LoadingBar*					GetEmpiricalProgressBar(){return m_pEmpiricalProgressBar;}		// ��ȡUI�ľ���ֵ��
	LoadingBar*					GetMonsterBloodProgressBar(){return m_pMonsterBloodProgressBar;}				// ��ȡUI��Ѫ����

protected:

	bool								m_bCanMove;															// ���ڿ�����ҵı�־

	int								m_nDirection;															// ����ƶ��ķ���

	Point							m_DestPoint;															// �ƶ���ҵ�ʱ���Ŀ���ַ

	Sprite*							m_pSelectCircleLight;												// �������Ҽ���ʱ����ʾ�Ĺ�Ȧ

	Player*							m_pPlayer;																// ��Ҷ��󣨴�Controller�л�ȡ��

	Layer*							m_pBackgroundLayer;												// ������
	Layer*							m_pEntityLayer;														// �м�������Լ������
	Layer*							m_pUILayer;																// �������UI��

	Button*						m_pSkillButton_Q;													// ���ܰ�ť1
	Button*						m_pSkillButton_W;													// ���ܰ�ť2
	Button*						m_pSkillButton_E;														// ���ܰ�ť3
	Button*						m_pSkillButton_R;														// ���ܰ�ť4

	LoadingBar*					m_pBloodProgressBar;												// UI��Ѫ����
	LoadingBar*					m_pMagicProgressBar;												// UI��ħ����
	LoadingBar*					m_pEmpiricalProgressBar;											// UI�ľ���ֵ��

	LoadingBar*					m_pMonsterBloodProgressBar;									// UI�Ĺ���Ѫ����

	Skill*								m_pSkill_Q;																	// ����1
	Skill*								m_pSkill_W;																	// ����2
	Skill*								m_pSkill_E;																	// ����3
	Skill*								m_pSkill_R;																	// ����4

	bool								m_bSkill_Q_ButtonPressed;											// ����1��ť�Ƿ񱻰��£����˼��ܰ�ťȻ���������������ͷ�ħ����
	bool								m_bSkill_W_ButtonPressed;											// ����2��ť�Ƿ񱻰��£����˼��ܰ�ťȻ���������������ͷ�ħ����
	bool								m_bSkill_E_ButtonPressed;											// ����3��ť�Ƿ񱻰��£����˼��ܰ�ťȻ���������������ͷ�ħ����
	bool								m_bSkill_R_ButtonPressed;											// ����4��ť�Ƿ񱻰��£����˼��ܰ�ťȻ���������������ͷ�ħ����

};
RPG_01_END



#endif //_MAIN_SCENE_H_