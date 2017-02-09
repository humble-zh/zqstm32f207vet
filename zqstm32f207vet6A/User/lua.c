/******************************************************************************
  FileName: lua.c
  Author: Li_Zhihong
  Date: 20170115
******************************************************************************/
#include "lua.h"
#include "lauxlib.h"

/* ���Ե�Lua�����ַ��� */
const char lua_test[] = { 
    "print(\"Hello,I am lua!\\n--this is newline printf\\n\")\n"
    "function foo()\n"
    "  local i = 0\n"
    "  local sum = 1\n"
    "  while i <= 10 do\n"
    "    sum = sum * 2\n"
    "    i = i + 1\n"
    "  end\n"
    "return sum\n"
    "end\n"
    "print(\"sum =\", foo())\n"
    "print(\"and sum = 2^11 =\", 2 ^ 11)\n"
    "print(\"exp(200) =\", math.exp(200))\n"
};

extern lua_State *luaL_newstate (void);
extern void luaL_openlibs (lua_State *L);
extern int luaopen_base (lua_State *L);

/* ����Lua */
void lua_main(void)
{
    lua_State *L;
    
	printf("lua_main\n");
    L = luaL_newstate(); /* ����Lua���л��� */
	printf("1\n");
    luaL_openlibs(L);
	printf("2\n");
    luaopen_base(L);
	printf("3\n");
    luaL_dostring(L, lua_test); /* ����Lua�ű� */
	printf("4\n");
    lua_close(L);
}

