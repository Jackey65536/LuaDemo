/*
 *  Global State
 */

#ifndef lstate_h
#define lstate_h

#include "lua.h"

#include "lobject.h"
#include "ltm.h"
#include "lzio.h"

struct lua_longjmp; /* defined in ldo.c */

/* table of globals */
#define gt(L)   (&L->l_gt)

/* registry */
#define registry(L) (&G(L)->l_registry)

/* extra stack space to handle TM calls and some other extras */
#define EXTRA_STACK 5

#define BASIC_CI_SIZE   8

#define BASIC_STACK_SIZE    (2*LUA_MINSTACK)

/*
    专门用于存放字符串的散列数组
 */
typedef struct stringtable {
    GCObject **hash;
    lu_int32 nuse;  /* number of elements */
    int size;       /* hash 桶数组大小*/
} stringtable;

/*
    informations about a call
 */
typedef struct CallInfo {
    StkId base; /* base for this function */
    StkId func; /* function index in the stack */
    StkId top;  /* top for this function */
    const Instruction *savedpc;
    int nresults;   /* expected number of results from this function */
    int tailcalls;  /* number of tail calls lost under this entry */
} CallInfo;

#define curr_func(L)    (clvalue(L->ci->func))
#define ci_func(ci)     (clvalue((ci)->func))
#define f_isLua(ci)     (!ci_func(ci)->c.isC)
#define isLua(ci)       (ttisfunction((ci)->func) && f_isLua(ci))

/*
    `global state`, shared by all threads of this state
 */
typedef struct global_State {
    /* 所有字符串都房子strt中 */
    stringtable strt;   /* hash table for strings */
    lua_Alloc frealloc; /* function to reallocate memory */
    void *ud;           /* auxiliary(辅助的) data to `frealloc` */
    lu_byte currentwhite;
    lu_byte gcstate;    /* state of garbage collector */
    int sweepstrgc;     /* position of sweep in `strt` */
    GCObject *rootgc;   /* list of all collecctable objects */
    GCObject **sweepgc; /* position of sweep in `rootgc` */
    GCObject *gray;     /* list of gray objects */
    GCObject *grayagain;/* list of objects to be traversed atomically */
    GCObject *weak;     /* list of weak tables (to be cleared) */
    /* 所有的GC方法的udata，都放在tmudata链表中 */
    GCObject *tmudata;  /* last element of list of userdata to be GC */
    Mbuffer buff;       /* temporary buffer for string concatentation */
    lu_mem GCthreshold; /* 一个阈值，当totalbytes大于这个阈值时进行自动GC */
    lu_mem totalbytes;  /* 当前分配的总内存数量*/
    lu_mem estimate;    /* an estimate(估算值) of number of bytes actually in use */
    /* 当前待 GC 的数据大小，其实就是累加totalbytes和GCthreshold的差值*/
    lu_mem gcdept;      /* how much GC is `behind schedule` */
    /* 可以配置的一个值，不是计算出来的，根据这个计算GCthreshold，以此来控制下一次GC触发的时间 */
    int gcpause;        /* size of pause between successive GCs */
    /* 每次进行GC操作回收的数据比例，见lgc.c/luaC_step函数*/
    int gcstepmul;      /* GC `granularity` */
    lua_CFunction panic;/* to be called in unprotected errors */
    TValue l_registry;
    struct lua_State *mainthread;
    UpVal uvhead;       /* head of double-linked list of all open upvalues */
    struct Table *mt[NUM_TAGS]; /* metatables for basic types */
    TString *tmname[TM_N];  /* array with tag-method names */
} global_State;

struct lua_State {
    CommonHeader;
    lu_byte status;
    StkId top;          /* first free slot in the stack */
    StkId base;         /* base of current function */
    global_State *l_G;
    CallInfo *ci;       /* call info for current function */
    const Instruction *savedpc; /* `savedpc` of current function */
    StkId stack_last;   /* last free slot in the stack */
    StkId stack;        /* stack base */
    CallInfo *end_ci;   /* points after end of ci array */
    CallInfo *base_ci;  /* array of CallInfo's */
    int stacksize;
    int size_ci;        /* size of array `base_ci` */
    unsigned short nCcalls; /* number of nested C calls */
    unsigned short baseCcalls;  /* nested C calls when resuming coroutine */
    lu_byte hookmask;
    lu_byte allowhook;
    int basehookcount;
    int hookcount;
    lua_Hook hook;
    TValue l_gt;        /* table of globals */
    TValue env;         /* temporary place for environments */
    GCObject *openupval;/* list of open upvalues in this stack */
    GCObject *gclist;
    struct lua_longjmp *errorJmp;   /* current error recover point */
    ptrdiff_t errfunc;  /* current error handling function (stack index) */
};

#define G(L)    (L->l_G)

/*
 将所有需要进行GC的数据类型囊括起来
 */
union GCObject {
    GCheader gch;
    union TString ts;
    union Udata u;
    union Closure cl;
    struct Table h;
    struct Proto p;
    struct UpVal uv;
    struct lua_State th;
};

#endif /* lstate_h */
