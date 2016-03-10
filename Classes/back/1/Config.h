#ifndef _RPG_01_CONFIG_H_
#define _RPG_01_CONFIG_H_

#include "define.h"
#include "../CommonClass/common.h"
#include <cocos2d.h>
USING_NS_CC;

RPG_01_BEGIN
/*
** 游戏配置类：使用Lua配置文件
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

	string					m_strPlayerActionConfigFile;				// 玩家动作的配置文件
	string					m_strMonsterActionConfigFile;			// 怪物动作的配置文件
	string					m_strSkillActionConfigFile;				// 技能动作的配置文件

	string					m_strRoleName;								// 玩家的名称

	float 					m_fProcessInterval;							// 各个管理器处理事务的时间间隔

	float 					m_fPlayerSpeed;								// 初始的玩家速度
	float 					m_fPlayerSpeedIncrement;				// 每升一级玩家速度增量

	float 					m_fPlayerDamageValue;					// 初始的玩家伤害值
	float 					m_fPlayerDamageValueIncrement;	// 升级时玩家伤害值增加的多少

	float						m_fPlayerBloodReturnValue;				// 玩家什么都不做的时候的回血量
	float						m_fPlayerMagicReturnValue;			// 玩家什么都不做的时候的回魔量

	float 					m_fMonsterSpeed;							// 怪物的初始速度
	float 					m_fMonsterSpeedIncrement;			// 升级时候怪物速度的增加量

	float 					m_fMonsterDamageValue;				// 初始时候怪物对人的伤害值
	float 					m_fMonsterDamageValueIncrement;// 升级的时候怪物的伤害值的增加量

	float 					m_fMonsterEmpiricalValue;				// 怪物所拥有的经验值（即玩家杀死该怪物之后得到的经验值）
	float 					m_fMonsterEmpiricalValueIncrement;// 怪物升级的时候经验值的增加量

	float						m_fMonsterBloodReturnValue;			// 怪物的单位时间内的回血量
	int						m_nMonsterMaxCount;					// 怪物的最大数量

	int						m_nEquipmentBloodMaxCount;		// 血瓶（掉在地上的）的最大数量
	int						m_nEquipmentMagicMaxCount;		// 魔瓶（掉在地上的）的最大数量

	float						m_fEquipmentBloodReturnValue;		// 吃掉一个血瓶之后回复的血量
	float						m_fEquipmentMagicReturnValue;		// 吃掉一个魔瓶之后回复的魔法量

	string					m_strEquipmentBloodPicName;		// 血瓶图片资源的路径
	string					m_strEquipmentMagicPicName;		// 魔瓶图片资源的路径

	float						m_fPlayerPosition_X;							// 玩家起始的横坐标
	float						m_fPlayerPosition_Y;							// 玩家的其实位置

	float						m_fBossPosition_X;							// Boss的起始位置
	float						m_fBossPosition_Y;							// Boss的其实位置

	string					m_strSelfIndicatorFileName;				// 指示玩家（或怪物）被选中时候显示的光圈的图片资源的路径
	string					m_strUIFileName;								// UI资源路径
	string					m_strMap1FileName;						// 章节1的地图的路径
	string					m_strMap2FileName;						// 章节2的地图的路径
	string					m_strMap3FileName;						// 章节3的地图的路径
	string					m_strMap4FileName;						// 章节4的地图的路径

	float						m_fPortalPosition_X;							// 传送门位置
	float						m_fPortalPosition_Y;							// 传送门位置

	string					m_strServerIP;
	int						m_nServerPort;
	bool						m_bNetworkMode;

	string					m_strPlayerID;

};

RPG_01_END
#endif