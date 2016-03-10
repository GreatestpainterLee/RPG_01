#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../CommonClass/common.h"
#include "../CommonClass/GamePackage.pb.h"

class Player
{
public:

	static void ConvertPack2Player(const GamePackage_Player& pack_player,Player& player);
	static void ConvertPlayer2Pack(Player& player,GamePackage_Player& pack_player);

	PROPERTY_INIT(SOCKET,Socket,m_nSocket);
	PROPERTY_INIT(sockaddr_in,Addr,m_Addr);

	void					SetID(const string& strID){m_strID = strID;}
	string&				GetID(){return m_strID;}

	void					SetName(const string& strName){m_strUserName = strName;}
	string&				GetName(){return m_strUserName;}

	void					SetPassword(const string& ps){m_strPassword = ps;}
	string&				GetPassword(){return m_strPassword;}

	PROPERTY_INIT(float,Speed,m_fSpeed);
	PROPERTY_INIT(int,Direction,m_nDirection);
	PROPERTY_INIT(float,DestPointX,m_fDestPointX);
	PROPERTY_INIT(float,DestPointY,m_fDestPointY);
	PROPERTY_INIT(float,CurrentPointX,m_fCurrentPointX);
	PROPERTY_INIT(float,CurrentPointY,m_fCurrentPointY);
	PROPERTY_INIT(int,MsgCode,m_nMsgCode);
	PROPERTY_INIT(int,PreDirection,m_nPreDirection);
	PROPERTY_INIT(int,PreMsgCode,m_nPreMsgCode);
	PROPERTY_INIT(float,BloodValue,m_fBloodValue);
	PROPERTY_INIT(float,MaxBloodValue,m_fMaxBloodValue);
	PROPERTY_INIT(float,MagicValue,m_fMagicValue);
	PROPERTY_INIT(float,MaxMagicValue,m_fMaxMagicValue);
	PROPERTY_INIT(float,EmpiricalValue,m_fEmpiricalValue);
	PROPERTY_INIT(float,MaxEmpiricalValue,m_fMaxEmpiricalValue);
	PROPERTY_INIT(int,Level,m_nLevel);
	PROPERTY_INIT(float,DamageValue,m_fDamageValue);
	PROPERTY_INIT(int,CurrentSkill,m_nCurrentSkill);
private:
	SOCKET			m_nSocket;
	sockaddr_in		m_Addr;
	string				m_strID;

	string m_strUserName ;
	string m_strPassword ;

	float m_fSpeed ;											// 速度：随着等级提高，相应的值也会增加

	int m_nDirection;										// 移动或跑动的方向
	float m_fDestPointX ;										// 移动时的目的地
	float m_fDestPointY ;
	float m_fCurrentPointX ;										// 移动时的目的地
	float m_fCurrentPointY ;

	int m_nMsgCode ;									// 动作类型

	int m_nPreDirection ;									// 前一个移动的方向
	int m_nPreMsgCode ;								// 前一个动作类型

	float m_fBloodValue ;										// 当前血量：随着等级提高，相应的值也会增加
	float m_fMaxBloodValue ;

	float m_fMagicValue ;									// 当前魔法量：随着等级提高，相应的值也会增加
	float m_fMaxMagicValue ;

	float m_fEmpiricalValue ;								// 当前经验值：每次升级都会清空
	float m_fMaxEmpiricalValue ;							// 每一级的最大经验值，当经验值达到这个数量的时候就会升级：：随着等级提高，相应的值也会增加

	int m_nLevel ;												// 当前的等级：初始时候玩家的等级为1

	float m_fDamageValue ;									// 玩家的伤害值，攻击怪物时对怪物造成的伤害：随着等级提高，相应的值也会增加

	int m_nCurrentSkill ;

};
#endif