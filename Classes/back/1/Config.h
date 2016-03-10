#ifndef _RPG_01_CONFIG_H_
#define _RPG_01_CONFIG_H_

#include "define.h"
#include "../CommonClass/common.h"
#include <cocos2d.h>
USING_NS_CC;

RPG_01_BEGIN
/*
** ��Ϸ�����ࣺʹ��Lua�����ļ�
*/
class Config
{
public:
	static Config*		GetInstance();
	void						LoadConfig();
	
	string&					GetRandomID();
	string&					GetPlayerActionConfigFile();
	string&					GetMonsterActionConfigFile();
	string&					GetSkillActionConfigFile();
	string&					GetRoleName();

	

	float						GetProcessInterval(){return m_fProcessInterval;}
	float						GetPlayerSpeed(){return m_fPlayerSpeed;}
	float						GetPlayerSpeedIncrement(){return m_fPlayerSpeedIncrement;}
	float						GetPlayerDamageValue(){return m_fPlayerDamageValue;}
	float						GetPlayerDamageValueIncrement(){return m_fPlayerDamageValueIncrement;}
	float						GetMonsterSpeed(){return m_fMonsterSpeed;}
	float						GetMonsterSpeedIncrement(){return m_fMonsterSpeedIncrement;}
	float						GetMonsterDamageValue(){return m_fMonsterDamageValue;}
	float						GetMonsterDamageValueIncrement(){return m_fMonsterDamageValueIncrement;}
	float						GetMonsterEmpiricalValue(){return m_fMonsterEmpiricalValue;}
	float						GetMonsterEmpiricalValueIncrement(){return m_fMonsterEmpiricalValueIncrement;}
	float						GetPlayerBloodReturnValue(){return m_fPlayerBloodReturnValue;}
	float						GetPlayerMagicReturnValue(){return m_fPlayerMagicReturnValue;}
	float						GetMonsterBloodReturnValue(){return m_fMonsterBloodReturnValue;}
	int						GetMonsterMaxCount(){return m_nMonsterMaxCount;}
	int						GetEquipmentBloodMaxCount(){return m_nEquipmentBloodMaxCount;}
	int						GetEquipmentMagicMaxCount(){return m_nEquipmentMagicMaxCount;}
	float						GetEquipmentBloodReturnValue(){return m_fEquipmentBloodReturnValue;}
	float						GetEquipmentMagicReturnValue(){return m_fEquipmentMagicReturnValue;}

	string&					GetEquipmentBloodPicName(){return m_strEquipmentBloodPicName;}
	string&					GetEquipmentMagicPicName(){return m_strEquipmentMagicPicName;}

	float						GetPlayerPosition_X(){return m_fPlayerPosition_X;}
	float						GetPlayerPosition_Y(){return m_fPlayerPosition_Y;}
	float						GetBossPosition_X(){return m_fBossPosition_X;}
	float						GetBossPosition_Y(){return m_fBossPosition_Y;}

	string&					GetSelfIndicatorFileName(){return m_strSelfIndicatorFileName;}
	string&					GetUIFileName(){return m_strUIFileName;}
	string&					GetMap1FileName(){return m_strMap1FileName;}
	string&					GetMap2FileName(){return m_strMap2FileName;}
	string&					GetMap3FileName(){return m_strMap3FileName;}
	string&					GetMap4FileName(){return m_strMap4FileName;}
	
	float						GetPortalPosition_X(){return m_fPortalPosition_X;}
	float						GetPortalPosition_Y(){return m_fPortalPosition_Y;}

	string&					GetServerIP(){return m_strServerIP;}
	int						GetServerPort(){return m_nServerPort;}
	bool						IsNetworkMode(){return m_bNetworkMode;}
protected:
private:
	static Config*		m_pInstance;
	Config();

	string					m_strPlayerActionConfigFile;				// ��Ҷ����������ļ�
	string					m_strMonsterActionConfigFile;			// ���ﶯ���������ļ�
	string					m_strSkillActionConfigFile;				// ���ܶ����������ļ�

	string					m_strRoleName;								// ��ҵ�����

	float 					m_fProcessInterval;							// �������������������ʱ����

	float 					m_fPlayerSpeed;								// ��ʼ������ٶ�
	float 					m_fPlayerSpeedIncrement;				// ÿ��һ������ٶ�����

	float 					m_fPlayerDamageValue;					// ��ʼ������˺�ֵ
	float 					m_fPlayerDamageValueIncrement;	// ����ʱ����˺�ֵ���ӵĶ���

	float						m_fPlayerBloodReturnValue;				// ���ʲô��������ʱ��Ļ�Ѫ��
	float						m_fPlayerMagicReturnValue;			// ���ʲô��������ʱ��Ļ�ħ��

	float 					m_fMonsterSpeed;							// ����ĳ�ʼ�ٶ�
	float 					m_fMonsterSpeedIncrement;			// ����ʱ������ٶȵ�������

	float 					m_fMonsterDamageValue;				// ��ʼʱ�������˵��˺�ֵ
	float 					m_fMonsterDamageValueIncrement;// ������ʱ�������˺�ֵ��������

	float 					m_fMonsterEmpiricalValue;				// ������ӵ�еľ���ֵ�������ɱ���ù���֮��õ��ľ���ֵ��
	float 					m_fMonsterEmpiricalValueIncrement;// ����������ʱ����ֵ��������

	float						m_fMonsterBloodReturnValue;			// ����ĵ�λʱ���ڵĻ�Ѫ��
	int						m_nMonsterMaxCount;					// ������������

	int						m_nEquipmentBloodMaxCount;		// Ѫƿ�����ڵ��ϵģ����������
	int						m_nEquipmentMagicMaxCount;		// ħƿ�����ڵ��ϵģ����������

	float						m_fEquipmentBloodReturnValue;		// �Ե�һ��Ѫƿ֮��ظ���Ѫ��
	float						m_fEquipmentMagicReturnValue;		// �Ե�һ��ħƿ֮��ظ���ħ����

	string					m_strEquipmentBloodPicName;		// ѪƿͼƬ��Դ��·��
	string					m_strEquipmentMagicPicName;		// ħƿͼƬ��Դ��·��

	float						m_fPlayerPosition_X;							// �����ʼ�ĺ�����
	float						m_fPlayerPosition_Y;							// ��ҵ���ʵλ��

	float						m_fBossPosition_X;							// Boss����ʼλ��
	float						m_fBossPosition_Y;							// Boss����ʵλ��

	string					m_strSelfIndicatorFileName;				// ָʾ��ң�������ѡ��ʱ����ʾ�Ĺ�Ȧ��ͼƬ��Դ��·��
	string					m_strUIFileName;								// UI��Դ·��
	string					m_strMap1FileName;						// �½�1�ĵ�ͼ��·��
	string					m_strMap2FileName;						// �½�2�ĵ�ͼ��·��
	string					m_strMap3FileName;						// �½�3�ĵ�ͼ��·��
	string					m_strMap4FileName;						// �½�4�ĵ�ͼ��·��

	float						m_fPortalPosition_X;							// ������λ��
	float						m_fPortalPosition_Y;							// ������λ��

	string					m_strServerIP;
	int						m_nServerPort;
	bool						m_bNetworkMode;

	string					m_strPlayerID;

};

RPG_01_END
#endif