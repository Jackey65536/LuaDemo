//
//  lobject.h
//  LuaDemo
//
//  Created by 刘杰 on 2019/11/9.
//  Copyright © 2019 刘杰. All rights reserved.
//

#ifndef lobject_h
#define lobject_h

#include "llimits.h"
#include "lua.h"

/* tags for values visible from Lua */
#define LAST_TAG    LUA_TTHREAD
#define NUM_TAGS    (LAST_TAG+1)

/* Extra tags for non-values */
#define LUA_TPROTO  (LAST_TAG+1)
#define LUA_TUPVAL  (LAST_TAG+2)
#define LUA_TDEADKEY    (LAST_TAG+3)

typedef union GCObject GCObject;

/*
 需要GC的Lua数据类型，都会以CommonHeader作为结构体定义的最开始部分，即继承CommonHeader
 next: 指向下一个GC链表的成员
 tt: 标识数据的类型
 marked: GC相关的标记位
 */
#define CommonHeader GCObject *next; lu_byte tt; lu_byte marked

typedef struct GCheader {
    CommonHeader;
} GCheader;

/*
 Lua中所有的数据类型联合在一起
 */
typedef union {
    GCObject *gc;   /* tt对应值 LUA_TSTRING、LUA_TTABLE、LUA_TFUNCTION、LUA_TUSERDATA、LUA_TTHREAD */
    void *p;        /* tt对应值 LUA_TLIGHTUSERDATA */
    lua_Number n;   /* tt对应值 LUA_TNUMBER */
    int b;          /* tt对应值 LUA_TBOOLEAN */
} Value;

#define TValuefields    Value value; int tt;

/*
 统一表示所有在lua虚拟机中需要保存的数据类型，lua中的任何数据都可以通过该结构体表示
 */
typedef struct lua_TValue {
    TValuefields;
} TValue;

#define ttype(o)        ((o)->tt) /* 获取数据类型 */
/* 测试数据类型的宏定义 */
#define ttisnil(o)      (ttype(o) == LUA_NIL)
#define ttisnumber(o)   (ttype(o) == LUA_TNUMBER)
#define ttisstring(o)   (ttype(o) == LUA_TSTRING)
#define ttistable(o)    (ttype(o) == LUA_TTABLE)
#define ttisfunction(o) (ttype(o) == LUA_TFUNCTION)
#define ttisboolean(o)  (ttype(o) == LUA_TBOOLEAN)
#define ttisuserdata(o) (ttype(o) == LUA_TUSERDATA)
#define ttisthread(o)   (ttype(o) == LUA_TTHREAD)
#define ttislightuserdata(o)    (ttype(o) == LUA_TLIGHTUSERDATA)

#define iscollectable(o) (ttype(o) >= LUA_TSTRING) /* 是否是需要GC的数据 */
/* o = TValue */
#define gcvalue(o)  check_exp(iscollectable(o), (o)->value.gc) /* gc value */
#define pvalue(o)   check_exp(ttislightuserdata(o), (o)->value.p)
#define nvalue(o)   check_exp(ttisnumber(o), (o)->value.n)
/* TString */
#define rawtsvalue(o)   check_exp(ttisstring(o), &(o)->value.gc->ts)
#define tsvalue(o)  (&rawtsvalue(o)->tsv)
/* Udata*/
#define rawuvalue(o)    check_exp(ttisuserdata(o), &(o)->value.gc->u)
#define uvalue(o)   (&rawuvalue(o)->uv)
/* Closure */
#define clvalue(o)  check_exp(ttisfunction(o), &(o)->value.gc->cl)
/* Table */
#define hvalue(o)   check_exp(ttistable(o), &(o)->value.gc->h)
#define bvalue(o)   check_exp(ttisboolean(o), (o)->value.b)
/* lua_State */
#define thvalue(o)  check_exp(ttisthread(o), &(o)->value.gc->th)

#define l_isfalse(o)    (ttisnil(o) || (ttisboolean(o) && bvalue(o) == 0)

typedef TValue *StkId;  /* index to stack elemnts */

typedef union TString {
    L_Umaxalign dummy;
    struct {
        CommonHeader;
        lu_byte reserved;   /* 标识是否是保留字 */
        unsigned int hash;  /* 字符串的散列值*/
        size_t len;
    } tsv;
} TString;

typedef union Udata {
    L_Umaxalign dummy;
    struct {
        CommonHeader;
        // TODO:
    } uv;
} Udata;

/* 存放函数原型的数据结构 */
typedef struct Proto {
    CommonHeader;
    TValue *k;
    // TODO:
} Proto;

#define VARARG_HASARG       1
#define VARARG_ISVARARG     2
#define VARARG_NEEDSARG     4

/* 存放局部变量的结构体 */
typedef struct LocVar {
    TString *vername;
    int startpc; /* first point where variable is active */
    int endpc; /* first point where variable is dead */
} LocVar;

typedef struct UpVal {
    CommonHeader;
    TValue *v;  /* points to stack or to its own value*/
    union {
        /* 当这个upval被close时，保存upval的值，后面可能还会被引用 */
        TValue value;
        /* 当这个upval还在open状态时，以下链表串连在openupval链表中 */
        struct {
            struct UpVal *prev;
            struct UpVal *next;
        } l;
    } u;
} UpVal;

#define ClosureHeader \
    CommonHeader; lu_byte isC; lu_byte nupvalues; GCObject *gclist; \
    struct Table *env

typedef struct CClosure {
    ClosureHeader;
    lua_CFunction f;
    TValue upvalue[1];
} CClosure;

typedef struct LClosure {
    ClosureHeader;
    struct Proto *p;
    UpVal *upvals[1];
} LClosure;

typedef union Closure {
    CClosure c;
    LClosure l;
} Closure;

#define iscfunction(o)  (ttype(o) == LUA_TFUNCTION && clvalue(o)->c.isC)
#define isLfunction(o)  (ttype(o) == LUA_TFUNCTION && !clvalue(o)->c.isC)

typedef union TKey {
    struct {
        TValuefields;
        struct Node *next;
    } nk;
    TValue tvk;
} TKey;

/* 每个节点都有key和val */
typedef struct Node {
    TValue i_val;
    TKey i_key;
} Node;

typedef struct Table {
    CommonHeader;
    lu_byte flags;
    lu_byte lsizenode;
    struct Table *metatable;
    TValue *array;
    Node *node;
    Node *lastfree;
    GCObject *gclist;
    int sizearray;
} Table;

#endif /* lobject_h */
