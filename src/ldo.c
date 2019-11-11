/*
    ldo.c
    Stack and Call structure of Lua
    函数调用及栈管理
 */

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

#define ldo_c
#define LUA_CORE

#include "lua.h"

#include "ldebug.h"
#include "ldo.h"

