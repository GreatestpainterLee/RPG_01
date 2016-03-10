#ifndef _RPG_01_PROTOCOL_H_
#define _RPG_01_PROTOCOL_H_
 
#include "common.h"
#include "GamePackage.pb.h"
#include "PackageHead.h"

class GameProtocol
{
public:
	GameProtocol()
	{
		m_Head.Clean();
		Clean();
	}

	void							SetMsgCode(int code)
	{
		m_Head.SetMsgCode(code);
	}

	void							SetPackageType(int type)
	{
		m_Head.SetPackageType(type);
	}

	int							GetMsgCode()
	{
		return m_Head.GetMsgCode();
	}

	int							GetPackageType()
	{
		return m_Head.GetPackageType();
	}

	int							GetPackageLength()
	{
		return m_Head.GetPackageLength();
	}

	void							DeserializeHeadFromByteArray(char* pData)
	{
		m_Head.DeserializeFromByteArray(pData);
	}

	void							DeserializePackFromByteArray(char* pData,int len)
	{
		m_Pack.ParseFromArray(pData,len);
	}

	void							SetPackData(char* pData)
	{
		memset(m_PackTempBuffer,0,SZ_1024_LENGTH);
		memmove(m_PackTempBuffer,pData,m_Head.GetPackageLength());
	}

	char*						GetPackData()
	{
		return m_PackTempBuffer;
	}

	int							SerializeToByteArray(char*& pBuf)
	{
		m_Head.SetPackageLength(m_Pack.ByteSize());

		memmove(m_Buffer,m_Head.Serialize2ByteArray(),m_Head.HeadLength);

		m_Pack.SerializeToArray(m_Buffer + m_Head.HeadLength,SZ_1024_LENGTH - m_Head.HeadLength);

		pBuf = m_Buffer;

		return (m_Head.HeadLength + m_Pack.ByteSize());
	}
	
	GamePackage_Player* AddPlayer()
	{
		return m_Pack.add_playerlist();
	}

	GamePackage_Monster* AddMonster()
	{
		return m_Pack.add_monsterlist();
	}

	const GamePackage_Player& GetPlayer(int i)
	{
		return m_Pack.playerlist(i);
	}

	const GamePackage_Monster& GetMonster(int i)
	{
		return m_Pack.monsterlist(i);
	}

	const int GetPlayerNum()
	{
		return m_Pack.playerlist_size();
	}

	const int GetMonsterNum()
	{
		return m_Pack.monsterlist_size();
	}


	PackageHead& GetHead()
	{
		return m_Head;
	}

	void					Print()
	{
		fprintf(stdout,"Package Length = %d\n",GetPackageLength());
		fprintf(stdout,"%s",m_Pack.Utf8DebugString().c_str());
		fprintf(stdout,"\n\n");
	}

	void					Clean()
	{
		memset(m_Buffer,0,SZ_1024_LENGTH);
		memset(m_PackTempBuffer,0,SZ_1024_LENGTH);
		m_Pack.Clear();
		m_Head.Clean();
	}

private:
	char							m_Buffer[SZ_1024_LENGTH];
	char							m_PackTempBuffer[SZ_1024_LENGTH];
	PackageHead			m_Head;
	GamePackage			m_Pack;
};

#endif