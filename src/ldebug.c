/*
    ldebug.c
    调试库
 */

#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#define ldebug_c
#define LUA_CORE

#include "lua.h"

#include "ldebug.h"


void luaG_runerror (lua_State *L, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt); /* 获取可变参数列表的第一个参数的地址 */
    // TODO:
}
