/*
    lua.h
 */

#ifndef lua_h
#define lua_h

#include <stddef.h>

#include "luaconf.h"

#define LUA_VERSION "Lua 5.1"
#define LUA_RELEASE "Lua 5.1.4"
#define LUA_VERSION_NUM 501
#define LUA_COPYRIGHT   "Copyright (C) 1994-2008 Lua.org, PUC-Rio"
#define LUA_AUTHORS     "R. Ierusalimschy, L. H. de Figueiredo & W. Celes"

/* mark for precompiled code (`<esc>Lua`) */
#define LUA_SIGNATURE   "\033Lua"

/* option for multiple returns in `lua_pacall` and `lua_call` */
#define LUA_MULTRET (-1)

/* pseudo-indices */
#define LUA_REGISTRYINDEX   (-10000)
#define LUA_ENVIRONINDEX    (-10001)
#define LUA_GLOBALSINDEX    (-10002)
#define lua_upvalueindex(i) (LUA_GLOBALSINDEX-(i))

/* thread status; 0 is OK */
#define LUA_YIELD       1
#define LUA_ERRRUN      2
#define LUA_ERRSYNTAX   3
#define LUA_ERRMEM      4
#define LUA_ERRERR      5

typedef struct lua_State lua_State;

typedef int (*lua_CFunction) (lua_State *L);

typedef const char* (*lua_Reader) (lua_State *L, void *ud, size_t *sz);

typedef const char* (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);

/*
    prototype for memory-allocation functions
 */
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);

/*
 Lua 基础类型
 */
#define LUA_TNONE           (-1)    /* 无类型*/
#define LUA_TNIL            0       /* 空类型 */
#define LUA_TBOOLEAN        1       /* 布尔类型 */
#define LUA_TLIGHTUSERDATA  2       /* 指针 => void*，分配释放由Lua外部使用者完成 */
#define LUA_TNUMBER         3       /* 数值 => lua_Number */
/* 以下的数据类型都需要进行GC操作 */
#define LUA_TSTRING         4       /* 字符串 => TString */
#define LUA_TTABLE          5       /* 表 => Table */
#define LUA_TFUNCTION       6       /* 函数 => CClosure、LCLosure */
#define LUA_TUSERDATA       7       /* 指针 => void*，分配释放由Lua内部完成 */
#define LUA_TTHREAD         8       /* Lua虚拟机、协程 => lua_State */

/* minimum Lua stack available to a C function */
#define LUA_MINSTACK    20

typedef LUA_NUMBER lua_Number;

typedef struct lua_Debug lua_Debug; /* activation record */

/* Functions to be called by the debuger in specific events */
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);

LUA_API int lua_getstack (lua_State *L, int level, lua_Debug *ar);
LUA_API int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar);
LUA_API const char *lua_getlocal (lua_State *L, const lua_Debug *ar, int n);
LUA_API const char *lua_setlocal (lua_State *L, const lua_Debug *ar, int n);
LUA_API const char *lua_getupvalue (lua_State *L, int funcindex, int n);
LUA_API const char *lua_setupvalue (lua_State *L, int funcindex, int n);

LUA_API int lua_sethook (lua_State *L, lua_Hook func, int mask, int count);
LUA_API lua_Hook lua_gethook (lua_State *L);
LUA_API int lua_gethookmask (lua_State *L);
LUA_API int lua_gethookcount (lua_State *L);

struct lua_Debug {
    int event;
    const char *name;       /* (n) */
    const char *namewhat;   /* (n) `global`, `local`, `field`, `method` */
    const char *what;       /* (S) `Lua`, `C`, `main`, `tail` */
    const char *source;     /* (S) */
    int currentline;        /* (l) */
    int nups;               /* (u) number of upvalues */
    int linedefined;        /* (S) */
    int lastlinedefined;    /* (S) */
    char short_src[LUA_IDSIZE]; /* (S) */
    int i_ci;               /* active function */
};

#endif /* lua_h */
