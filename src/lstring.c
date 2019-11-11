/*
    lstring.c
 */

#include <string.h>

#define lstring_c
#define LUA_CORE

#include "lua.h"

#include "lobject.h"
#include "lstate.h"
#include "lstring.h"

void luaS_resize (lua_State *L, int newsize) {
    GCObject **newhash;
    stringtable *tb;
    int i;
    /* 如果当前GC处于回收字符串数据的阶段，直接返回，不进行重新散列的操作 */
    if (G(L)->gcstate == GCSsweepstring) {
        return;
    }
    
    
}
