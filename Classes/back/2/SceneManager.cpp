#include "SceneManager.h"
#include "./scene/Chapter_1_Scene.h"
#include "./scene/Chapter_2_Scene.h"
#include "./scene/Chapter_3_Scene.h"
#include "./scene/Chapter_4_Scene.h"
#include "./scene/BaseScene.h"
RPG_01_BEGIN

SceneManager* SceneManager::m_pInstance = 0;

SceneManager* SceneManager::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new SceneManager;
	}

	return m_pInstance;
}

SceneManager::SceneManager()
{
	m_pCurrentScene = 0;
	m_nSceneID = INVALID_SCENE;
}

/************************************************************************
*  ��ȡ��ǰ�ĳ���
************************************************************************/
BaseScene* SceneManager::GetCurrentScene()
{
	return m_pCurrentScene;
}

/************************************************************************
*  ���õ�ǰ�ĳ���
************************************************************************/
void SceneManager::SetCurrentScene(BaseScene* pScene)
{
	m_pCurrentScene = pScene;
}

/************************************************************************
*  �������
************************************************************************/
void SceneManager::ChangeScene(int nChapterID)
{
	static bool bFirstRun = true;

	Scene* scene = 0;
	
	if (nChapterID == CHAPTER_1)
	{
		scene = Chapter_1_Scene::createScene();
	}

	if (nChapterID == CHAPTER_2)
	{
		scene = Chapter_2_Scene::createScene();
	}

	if (nChapterID == CHAPTER_3)
	{
		scene = Chapter_3_Scene::createScene();
	}

	if (nChapterID == CHAPTER_4)
	{
		scene = Chapter_4_Scene::createScene();
	}

	if (scene == 0)
	{
		return;
	}

	if (bFirstRun)
	{

		Director::getInstance()->runWithScene(scene);
		bFirstRun = false;

		// add for ��������½�һ�Ĵ����Ż��Զ���ʧ ��bug begin
		ChangeScene(CHAPTER_1);
		// add for ��������½�һ�Ĵ����Ż��Զ���ʧ ��bug end
	}
	else
	{
		Director::getInstance()->replaceScene(scene);
	}
}

/************************************************************************
*  �����������Ļ�Ϸ���Ѫ��
************************************************************************/
void SceneManager::SetBloodProgress(float persent)
{
	if (m_pCurrentScene == 0)
	{
		return;
	}

	m_pCurrentScene->GetBloodProgressBar()->setPercent(persent);
}

/************************************************************************
*  ������ҵľ�����
************************************************************************/
void SceneManager::SetEmpiricalProgress(float persent)
{
	if (m_pCurrentScene == 0)
	{
		return;
	}

	m_pCurrentScene->GetEmpiricalProgressBar()->setPercent(persent);
}

/************************************************************************
*  ������ҵ�ħ����
************************************************************************/
void SceneManager::SetMagicProgress(float persent)
{
	if (m_pCurrentScene == 0)
	{
		return;
	}

	m_pCurrentScene->GetMagicProgressBar()->setPercent(persent);
}

/************************************************************************
*  ���ù�������Ļ�Ϸ���Ѫ��
************************************************************************/
void SceneManager::SetMonsterBloodProgress(float persent)
{
	if (m_pCurrentScene == 0)
	{
		return;
	}

	if (persent == -1)
	{
		m_pCurrentScene->GetMonsterBloodProgressBar()->setPercent(0);
	}
	else
	{
		m_pCurrentScene->GetMonsterBloodProgressBar()->setPercent(persent);
	}
	
}

RPG_01_END