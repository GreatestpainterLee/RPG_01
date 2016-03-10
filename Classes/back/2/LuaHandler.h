#ifndef _LUA_HANDLER_H_
#define _LUA_HANDLER_H_

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};
/*
** Lua������
*/
class LuaHandler
{
public:

	// ���캯��
	LuaHandler()
	{
		// ��lua�����
		m_pLuaState = lua_open();

		// ��lua�����Ŀ�
		luaopen_base(m_pLuaState);

		// ��lua����ѧ��
		luaopen_math(m_pLuaState);

		// ��lua�ַ�����
		luaopen_string(m_pLuaState);
	}

	// ��������
	~LuaHandler()
	{
		// �ر�lua�����
		lua_close(m_pLuaState);
	}

	// ����lua�ļ�
	void				LoadFile(const char* filename)
	{
		int nRet = luaL_dofile(m_pLuaState,filename);
		if (nRet != 0)
		{
			throw exception("can not open lua file!");
		}
	}

	// ��ȡȫ���ַ���
	string			GetGlobalString(const char* varName)
	{
		lua_getglobal(m_pLuaState,varName);
		
		int nRet = lua_isstring(m_pLuaState,-1);
		if (nRet == 0)
		{
			throw exception("there is not a string!");
			return "";
		}

		return lua_tostring(m_pLuaState,-1);
	}

	// ����lua��ջ����
	void				SetTop(int v)
	{
		lua_settop(m_pLuaState,v);
	}

	// ��ȡȫ����ֵ�ͱ���
	double			GetGlobalNum(const char* varName)
	{
		lua_getglobal(m_pLuaState,varName);

		int nRet = lua_isnumber(m_pLuaState,-1);
		if (nRet == 0)
		{
			throw exception("there is not a number!");
			return 0;
		}

		return lua_tonumber(m_pLuaState,-1);
	}

	lua_State*		GetLuaState()
	{
		return m_pLuaState;
	}

private:
	lua_State*			m_pLuaState;
};
#endif

