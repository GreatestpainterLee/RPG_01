#ifndef _PACKAGE_HEAD_H_
#define _PACKAGE_HEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

/*
** 通信包头部
*/
struct PackageHead
{
public:

	// 头部长度
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

	// 设置版本号
	void						SetVersion(const string& strVesion)
	{
		memset(Version,0,4);
		strncpy(Version,strVesion.c_str(),4);
	}

	// 获取版本号
	string					GetVersion()
	{
		return Version;
	}

	// 设置通信包长度
	void						SetPackageLength(unsigned v)
	{
		if (v > 4096 || v <= 0)
		{
			return;
		}
		memset(PackageLength,0,4);
		itoa(v,PackageLength,10);
	}

	// 获取通信包长度
	unsigned					GetPackageLength()
	{
		return atoi(PackageLength);
	}

	// 设置消息码
	void							SetMsgCode(int code)
	{
		if (code <= -128 || code > 128)
		{
			return;
		}

		MessageCode = code;
	}

	// 获取消息码
	int							GetMsgCode()
	{
		return MessageCode;
	}

	// 设置包类型
	void							SetPackageType(int type)
	{
		PackageType = type;
	}

	// 获取包类型
	int							GetPackageType()
	{
		return PackageType;
	}

	// 把头部序列化成字节数组
	char*							Serialize2ByteArray()
	{
		memmove(HeadBuffer,Version,4);
		memmove(HeadBuffer + 4,&PackageType,1);
		memmove(HeadBuffer + 4 + 1,&MessageCode,1);
		memmove(HeadBuffer +4+1+1,PackageLength,4);
		return HeadBuffer;
	}

	// 从字节数组中反序列化出通信包头部
	void								DeserializeFromByteArray(const char* pData)
	{
		memmove(Version,pData,4);
		memmove(&PackageType,pData + 4,1);
		memmove(&MessageCode,pData + 5,1);
		memmove(PackageLength,pData + 6,4);
	}
private:
	char Version[4];						// 版本
	char PackageType;					// 包类型
	char MessageCode;					// 消息码
	char PackageLength[4];			// 包长度
	char HeadBuffer[HeadLength];

};

#endif
