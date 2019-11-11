/*
    lmem.c
    Interface to Memory Manager
    内存管理
*/

#include "stddef.h"

#define lmem_c
#define LUA_CORE

#include "lua.h"

//#include "ldebug.h"
#include "ldo.h"
#include "lmem.h"
#include "lobject.h"
#include "lstate.h"

#define MINSIZEARRAY    4

void* luaM_growaux_ (lua_State *L, void *block, int *size, size_t size_elems,
                     int limit, const char *errormsg) {
    void* newblock;
    int newsize;
    if (*size >= limit/2) { /* cannot double it? */
        if (*size >= limit) { /* cannot grow even a little? */
            // TODO:
        }
        newsize = limit;    /* still have at least one free place */
    } else {
        newsize = (*size)*2;
        if (newsize < MINSIZEARRAY) {
            newsize = MINSIZEARRAY; /* minimum size */
        }
    }
    newblock = luaM_reallocv(L, block, *size, newsize, size_elems);
    *size = newsize;    /* update only when everything else is OK */
    return newblock;
}

void *luaM_toobig (lua_State *L) {
    // TODO:
    return NULL; /* to avoid warning */
}

/*
    generic allocation routine
*/
void *luaM_realloc_ (lua_State *L, void *block, size_t osize, size_t nsize) {
    global_State *g = G(L);
    lua_assert((osize == 0) == (block == NULL));
    block = (*g->frealloc)(g->ud, block, osize, nsize);
    if (block == NULL && nsize > 0) {
        luaD_throw(L, LUA_ERRMEM);
    }
    lua_assert((nsize == 0) == (block == NULL));
    g->totalbytes = (g->totalbytes - osize) + nsize;
    return block;
}
