#ifndef NETACHIVE_H
#define NETACHIVE_H

#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*
** 网络序列（反序列化）包
** 将每一个基础的数据类型格式化成字符串
** 然后再将格式化之后的字符串放到网络上传输
** 从网上获取到的字符串经过该类进行反序列化得到相应的数据
*/
class NetAchive
{
public:
	// 保存模式（序列化）
	const static int SAVE_MODE = 0;
	// 读取模式（反序列化）
	const static int LOAD_MODE = 1;

	// 构造函数
	// buf:外部的字符串或者缓冲区
	// len：buf的长度
	// mode：模式，序列化还是反序列化
	// cSpilitChar：数据之间的分隔符
	NetAchive(char* buf,int len,int mode,char cSpilitChar = '|')
	{
		Reset(buf,len,mode,cSpilitChar);
	}

	// 清理函数
	void        Clean()
	{
		m_pBuffer = 0;
		m_nBufferLen = 0;
		m_nPosition = 0;
		m_cSpilitChar = '|';
	}

	// 对字符串序列化
	void        Save_string(const string& str)
	{
		string strTemp = str;
		if (str.size() == 0)
		{
			strTemp = "";
		}
		
		strTemp += m_cSpilitChar;
		m_nBufferLen += strTemp.size();
		memcpy(m_pBuffer + m_nPosition,strTemp.c_str(),strTemp.size());
		m_nPosition += strTemp.size();
	}

	// 反序列化一个字符串
	string      Load_string()
	{
		char buf[1024 * 8] = {0};
		int index = 0;
		while(m_nPosition < m_nBufferLen)
		{
			if(m_pBuffer[m_nPosition] != m_cSpilitChar)
			{
				buf[index++] = m_pBuffer[m_nPosition];
				m_nPosition++;
			}
			else
			{
				m_nPosition++;
				break;
			}
		}

		return buf;
	}

	// 反序列化一个指定长度的字符串
	string      Load_string(int len)
	{
		if (len <= 0)
		{
			return "";
		}

		
		char buf[1024 * 8] = {0};
		int index = 0;
		while(m_nPosition < m_nBufferLen && index < len)
		{
			buf[index++] = m_pBuffer[m_nPosition];
			
			m_nPosition++;
			
		}

		return buf;
	}

	// 序列化一个整形数
	void        Save_int(int v)
	{
		char buf[16] = {0};
		sprintf(buf,"%d",v);
		string strTemp = buf;
		strTemp += m_cSpilitChar;
		m_nBufferLen += strTemp.size();
		memcpy(m_pBuffer + m_nPosition,strTemp.c_str(),strTemp.size());
		m_nPosition += strTemp.size();
	}

	// 反序列化一个整形数
	int         Load_int()
	{
		string str = Load_string();
		return atoi(str.c_str());
	}

	// 序列化一个bool类型数据
	void		Save_bool(bool v)
	{
		if (v == true)
		{
			Save_int(1);
		}
		else
		{
			Save_int(0);
		}
	}

	// 反序列化一个bool类型的数据
	bool		Load_bool()
	{
		int v = Load_int();
		if (1 == v)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 序列化一个浮点型数据
	void		Save_float(float v)
	{
		char buf[64] = {0};
		sprintf(buf,"%f",v);
		string strTemp = buf;
		strTemp += m_cSpilitChar;
		m_nBufferLen += strTemp.size();
		memcpy(m_pBuffer + m_nPosition,strTemp.c_str(),strTemp.size());
		m_nPosition += strTemp.size();
	}

	// 反序列化一个浮点型数据
	float		Load_float()
	{
		string str = Load_string();
		return atof(str.c_str());
	}

	// 获取序列化缓冲区的长度
	int        GetBufferLength()
	{
		return m_nBufferLen;
	}

	// 重置
	void        Reset(char* buf,int len,int mode,char cSpilitChar = '|')
	{
		Clean();

		m_cSpilitChar = cSpilitChar;

		if(LOAD_MODE == mode)
			m_nBufferLen = len;

		m_pBuffer = buf;
	}

private:
	char*       m_pBuffer;			// 缓冲区，保存格式化之后的数据
	int         m_nBufferLen;		// 缓冲区长度
	int         m_nPosition;		// 缓冲区的当前位置
	char		m_cSpilitChar;		// 分隔符，每个数据之间用该分隔符进行分隔
};

#endif
