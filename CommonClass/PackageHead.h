#ifndef _PACKAGE_HEAD_H_
#define _PACKAGE_HEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

/*
** ͨ�Ű�ͷ��
*/
struct PackageHead
{
public:

	// ͷ������
	static const int HeadLength = 10;		

	PackageHead()
	{
		Clean();	
	}

	void						Clean()
	{
		memset(Version,0,4);
		strncpy(Version,"1.0",strlen("1.0"));
		PackageType = -1;
		MessageCode = -1;
		memset(PackageLength,0,4);
		memset(HeadBuffer,0,HeadLength);
	}

	// ���ð汾��
	void						SetVersion(const string& strVesion)
	{
		memset(Version,0,4);
		strncpy(Version,strVesion.c_str(),4);
	}

	// ��ȡ�汾��
	string					GetVersion()
	{
		return Version;
	}

	// ����ͨ�Ű�����
	void						SetPackageLength(unsigned v)
	{
		if (v > 4096 || v <= 0)
		{
			return;
		}
		memset(PackageLength,0,4);
		itoa(v,PackageLength,10);
	}

	// ��ȡͨ�Ű�����
	unsigned					GetPackageLength()
	{
		return atoi(PackageLength);
	}

	// ������Ϣ��
	void							SetMsgCode(int code)
	{
		if (code <= -128 || code > 128)
		{
			return;
		}

		MessageCode = code;
	}

	// ��ȡ��Ϣ��
	int							GetMsgCode()
	{
		return MessageCode;
	}

	// ���ð�����
	void							SetPackageType(int type)
	{
		PackageType = type;
	}

	// ��ȡ������
	int							GetPackageType()
	{
		return PackageType;
	}

	// ��ͷ�����л����ֽ�����
	char*							Serialize2ByteArray()
	{
		memmove(HeadBuffer,Version,4);
		memmove(HeadBuffer + 4,&PackageType,1);
		memmove(HeadBuffer + 4 + 1,&MessageCode,1);
		memmove(HeadBuffer +4+1+1,PackageLength,4);
		return HeadBuffer;
	}

	// ���ֽ������з����л���ͨ�Ű�ͷ��
	void								DeserializeFromByteArray(const char* pData)
	{
		memmove(Version,pData,4);
		memmove(&PackageType,pData + 4,1);
		memmove(&MessageCode,pData + 5,1);
		memmove(PackageLength,pData + 6,4);
	}
private:
	char Version[4];						// �汾
	char PackageType;					// ������
	char MessageCode;					// ��Ϣ��
	char PackageLength[4];			// ������
	char HeadBuffer[HeadLength];

};

#endif
