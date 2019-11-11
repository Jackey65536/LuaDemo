/*
    lzio.c
    缓存流接口
 */

#include <string.h>

#define lzio_c
#define LUA_CORE

#include "lua.h"

#include "llimits.h"
#include "lmem.h"
#include "lstate.h"
#include "lzio.h"

int luaZ_fill (ZIO *z) {
    size_t size;
    lua_State *L = z->L;
    const char *buff;
    lua_unlock(L);
    buff = z->reader(L, z->data, &size);
    lua_lock(L);
    if (buff == NULL || size == 0) {
        return EOZ;
    }
    z->n = size - 1;
    z->p = buff;
    return char2int(*(z->p++));
}
