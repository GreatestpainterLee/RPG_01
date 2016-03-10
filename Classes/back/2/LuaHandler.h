#ifndef _LUA_HANDLER_H_
#define _LUA_HANDLER_H_

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};
/*
** Lua处理类
*/
class LuaHandler
{
public:

	// 构造函数
	LuaHandler()
	{
		// 打开lua虚拟机
		m_pLuaState = lua_open();

		// 打开lua基础的库
		luaopen_base(m_pLuaState);

		// 打开lua字数学库
		luaopen_math(m_pLuaState);

		// 打开lua字符串库
		luaopen_string(m_pLuaState);
	}

	// 析构函数
	~LuaHandler()
	{
		// 关闭lua虚拟机
		lua_close(m_pLuaState);
	}

	// 加载lua文件
	void				LoadFile(const char* filename)
	{
		int nRet = luaL_dofile(m_pLuaState,filename);
		if (nRet != 0)
		{
			throw exception("can not open lua file!");
		}
	}

	// 获取全局字符串
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

	// 设置lua堆栈顶部
	void				SetTop(int v)
	{
		lua_settop(m_pLuaState,v);
	}

	// 获取全局数值型变量
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

