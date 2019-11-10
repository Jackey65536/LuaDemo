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
    // TODO: 
}
