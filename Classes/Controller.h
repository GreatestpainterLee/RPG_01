#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <cocos2d.h>
#include "define.h"

USING_NS_CC;


RPG_01_BEGIN
class Player;
class Monster;
class MonsterAI;
class Boss;
class SceneManager;
class EquipmentManager;
class MonsterManager;
class SkillManager;
class PathManager;
class Skill;
class Config;
class MainLogic;
class MonsterLogic;
class PlayerLogic;
class PlayerManager;
class NetworkModule;
class RecvDataLogic;
/*
** ��Ϸ�߼���
*/
class Controller
{
public:
	~Controller();
	static Controller*			GetInstance();

	SceneManager*				GetSceneManager();

	EquipmentManager*			GetEquipmentManager();

	MonsterManager*			GetMonsterManager();

	SkillManager*					GetSkillManager();

	PathManager*					GetPathManager();

	Config*								GetConfig();

	MonsterAI*						GetMonsterAI();

	NetworkModule*				GetNetworkModule();

	PlayerManager*				GetPlayerManager();

	PlayerLogic*						GetPlayerLogic();

	MonsterLogic*					GetMonsterLogic();

	RecvDataLogic*				GetRecvDataLogic();

public:
	void									Init(const string& strID,const string& strPsd,bool bNetMode);

	void									StartGame();																		// ��ʼ��Ϸ

	void									Handle(int nMessage);

	void									LoopGame(float delt);														// ��Ϸ����ѭ��

	void									ChangeChapter(int nChapterID);										// ���³���ת��

	int									GetCurrentChapter();														// ��Ϸ�½�ת��

	void									StopGame();																		// ֹͣ��Ϸ

	void									SuspendGame();																// ��ͣ��Ϸ

	void									ContinueGame();																// ������Ϸ

	bool									IsRunning();																		// �ж���Ϸ�Ƿ�������

	bool									IsNetGame();																	// �Ƿ�����

	void									IsNetGame(bool v);															// �Ƿ�����

	bool									CheckPlayerIsInPortal();													// �������Ƿ��ڴ����ŵ�λ��		

	//====================ҵ���߼����� begin=============================================
	void									HandleRightClick(Point& destPoint);									// ��������Ҽ������Ļ���¼�

	void									HandleLeftClick(Point& destPoint,Skill* pSkill);					// �����������¼�

	//====================ҵ���߼����� end=============================================

	void									SetCurrentSelectedMonster();

	Monster*							GetBoss();

	Monster*							GetCurrentSelectedMonster(){return m_pCurrentSelectedMonster;}


	string&								GetMyPlayerID(){return m_strMyPlayerID;}
	void									SetMyPlayerInfo(const string& strID,const string& strPsd);

	Player*								GetMyPlayer();

	void									SendPlayerState();
private:
	Controller();

	static Controller*			m_pInstance;

	Monster*						m_pCurrentSelectedMonster;						// ��ǰ��ѡ�еĹ���

	Monster*						m_pBoss;														// ��ǰ�½ڵ�Boss

	int								m_nCurrentChapter;										// ��ǰ��Ϸ�½�

	bool								m_bLoopGame;											// ��Ϸ��ѭ����ѭ����־

	bool								m_bIsNetGame;											// �Ƿ�Ϊ������Ϸ

	string							m_strMyPlayerID;

	Player*							m_pMyPlayer;
};

// ȫ�ֺ��� Game��Ŀ����Ϊ�˱���������дController::GetInstance()�����Ĵ���
Controller*							Game();
MainLogic*							GameLogic();

RPG_01_END

#endif // !_GAME_LOGIC_H_
