/*
    llimits.h
    Limits, basic types, and some other `installation-dependent` definitions
*/

#ifndef llimits_h
#define llimits_h

#include <limits.h>
#include <stddef.h>

#include "lua.h"

typedef LUAI_UINT32 lu_int32;

typedef LUAI_UMEM lu_mem;

typedef LUAI_MEM l_mem;

typedef unsigned char lu_byte;

#define MAX_SIZET   ((size_t)(~(size_t)0)-2)

#define MAX_LUMEM   ((lu_mem)(~(lu_mem)0)-2)

#define MAX_INT (INT_MAX-2) /* maximum value of an int (-2 for safety) */

typedef LUAI_USER_ALIGNMENT_T L_Umaxalign;

#ifdef lua_assert
    #define check_exp(c,e)      (lua_assert(c), (e))
    #define api_check(l,e)      lua_assert(e)
#else
    #define lua_assert(c)       ((void)0)
    #define check_exp(c,e)      (e)
    #define api_check           luai_apicheck
#endif

#ifndef UNUSED
#define UNUSED(x)   ((void)(x)) /* to avoid warnings */
#endif

#ifndef cast
#define cast(t, exp)    ((t)(exp))
#endif

#define cast_byte(i)    cast(lu_tye, (i))
#define cast_num(i)     cast(lua_Number, (i))
#define cast_int(i)     cast(int, (i))

/*
    type for virtual-machine instrutions
    must be an unsigned with (at least) 4 bytes (see details in lopcodes.h)
 */
typedef lu_int32 Instruction;

/* maximum stack for a Lua function */
#define MAXSTACK    250

/* minimum size for the string table (must be power of 2) */
#ifndef MINSTRTABSIZE
#define MINSTRTABSIZE   32
#endif

/* minimum size for string buffer */
#ifndef LUA_MINBUFFER
#define LUA_MINBUFFER   32
#endif

#ifndef lua_lock
#define lua_lock(L)     ((void) 0)
#define lua_unlock(L)   ((void) 0)
#endif

#ifndef luai_threadyield
#define luai_threadyield(L)     {lua_unlock(L); lua_lock(L);}
#endif

/* macro to control inclusion of some hard tests on stack reallocation */
#ifndef HARDSTACKTESTS
#define condhardstacktests(x)   ((void)0)
#else
#define condhardstacktests(x)   x
#endif

#endif /* llimits_h */
