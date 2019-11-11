/*
    lstring.h
 */

#ifndef lstring_h
#define lstring_h

#include "lgc.h"
#include "lobject.h"
#include "lstate.h"

LUAI_FUNC void luaS_resize (lua_State *L, int newsize);

#endif /* lstring_h */
