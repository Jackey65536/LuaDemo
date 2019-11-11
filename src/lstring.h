/*
    lstring.h
 */

#ifndef lstring_h
#define lstring_h

//#include "lgc.h"
#include "lobject.h"
#include "lstate.h"

LUAI_FUNC void luaS_resize (lua_State *L, int newsize);
LUAI_FUNC Udata *luaS_newudata (lua_State *L, size_t s, Table *e);
LUAI_FUNC TString *luaS_newlstr (lua_State *L, const char *str, size_t l);

#endif /* lstring_h */
