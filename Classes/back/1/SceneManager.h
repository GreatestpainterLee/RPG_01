#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;

#include "define.h"

/*
** ����������
** �������ĳ�ʼ���Լ��л��ȵ�
*/
RPG_01_BEGIN

class BaseScene;

class SceneManager
{
public:
	~SceneManager();

	static SceneManager*	GetInstance();

	void								ChangeScene(int nChapterID);						// ���õ�ǰ�ĳ���

	BaseScene*					GetCurrentScene();										// ��ȡ��ǰ�ĳ���

	void								SetCurrentScene(BaseScene* pScene);

	void								SetBloodProgress(float persent);
	void								SetMagicProgress(float persent);
	void								SetEmpiricalProgress(float persent);
	void								SetMonsterBloodProgress(float persent);

	
private:
	SceneManager();
private:
	static SceneManager*		m_pInstance;
	BaseScene*						m_pCurrentScene;
	int									m_nSceneID;
};

RPG_01_END

#endif // !_SCENE_MANAGER_H_
