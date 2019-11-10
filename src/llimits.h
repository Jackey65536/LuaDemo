//
//  llimits.h
//  LuaDemo
//
//  Created by 刘杰 on 2019/11/9.
//  Copyright © 2019 刘杰. All rights reserved.
//

#ifndef llimits_h
#define llimits_h

#include <limits.h>
#include <stddef.h>

#include "lua.h"

typedef LUAI_UINT32 lu_int32;

typedef LUAI_UMEM lu_mem;

typedef LUAI_MEM l_mem;

typedef unsigned char lu_byte;

typedef LUAI_USER_ALIGNMENT_T L_Umaxalign;

#ifdef lua_assert
    #define check_exp(c,e)      (lua_assert(c), (e))
    #define api_check(l,e)      lua_assert(e)
#else
    #define lua_assert(c)       ((void)0)
    #define check_exp(c,e)      (e)
    #define api_check           luai_apicheck
#endif

/*
    type for virtual-machine instrutions
    must be an unsigned with (at least) 4 bytes (see details in lopcodes.h)
 */
typedef lu_int32 Instruction;

#endif /* llimits_h */
