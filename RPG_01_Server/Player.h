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

	float m_fSpeed ;											// �ٶȣ����ŵȼ���ߣ���Ӧ��ֵҲ������

	int m_nDirection;										// �ƶ����ܶ��ķ���
	float m_fDestPointX ;										// �ƶ�ʱ��Ŀ�ĵ�
	float m_fDestPointY ;
	float m_fCurrentPointX ;										// �ƶ�ʱ��Ŀ�ĵ�
	float m_fCurrentPointY ;

	int m_nMsgCode ;									// ��������

	int m_nPreDirection ;									// ǰһ���ƶ��ķ���
	int m_nPreMsgCode ;								// ǰһ����������

	float m_fBloodValue ;										// ��ǰѪ�������ŵȼ���ߣ���Ӧ��ֵҲ������
	float m_fMaxBloodValue ;

	float m_fMagicValue ;									// ��ǰħ���������ŵȼ���ߣ���Ӧ��ֵҲ������
	float m_fMaxMagicValue ;

	float m_fEmpiricalValue ;								// ��ǰ����ֵ��ÿ�������������
	float m_fMaxEmpiricalValue ;							// ÿһ���������ֵ��������ֵ�ﵽ���������ʱ��ͻ������������ŵȼ���ߣ���Ӧ��ֵҲ������

	int m_nLevel ;												// ��ǰ�ĵȼ�����ʼʱ����ҵĵȼ�Ϊ1

	float m_fDamageValue ;									// ��ҵ��˺�ֵ����������ʱ�Թ�����ɵ��˺������ŵȼ���ߣ���Ӧ��ֵҲ������

	int m_nCurrentSkill ;

};
#endif