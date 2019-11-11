/*
    lgc.h
    Garbage Collector
 */
#ifndef lgc_h
#define lgc_h

#include "lobject.h"

/* Possible states of the Gargage Collector */
#define GCSpause        0
#define GCSpropagate    1
#define GCSsweepstring  2
#define GCSsweep        3
#define GCSfinalize     4

/*
    some userful bit tricks
 */
#define resetbits(x,m)  ((x) &= cast(lu_byte, ~(m)))
#define setbits(x,m)    ((x) |= (m))
#define testbits(x,m)   ((x) & (m))
#define bitmask(b)      (1<<(b)) /* 2^b */
#define bit2mask(b1,b2) (bitmask(b1) | bitmask(b2))
#define l_setbit(x,b)   setbits(x, bitmask(b))
#define resetbit(x,b)   resetbits(x, bitmask(b))
#define testbit(x,b)    testbits(x, bitmask(b))
#define set2bits(x,b1,b2)   setbits(x, (bit2mask(b1, b2)))
#define reset2bits(x,b1,b2) resetbits(x, (bit2mask(b1, b2)))
#define test2bits(x,b1,b2)  testbits(x, (bit2mask(b1, b2)))

/*
    Layout for bit use in `marked` field:
    bit 0 - object is white (type 0)
    bit 1 - object is white (type 1)
    bit 2 - object is black
    bit 3 - for userdata: has been finalized
    bit 3 - for tables: has weak keys
    bit 4 - for tables: has weak values
    bit 5 - object is fixd (should not be collected)
    bit 6 - object is "super" fixed (only the main thread)
 */
#define WHITE0BIT       0
#define WHITE1BIT       1
#define BLACKBIT        2
#define FINALIZEDBIT    3
#define KEYWEAKBIT      3   /* 弱key */
#define VALUEWEAKBIT    4   /* 弱值 */
#define FIXEDBIT        5   /* 标记这个GC对象不可回收 */
#define SFIXEDBIT       6

#define WHITEBITS   bit2mask(WHITE0BIT, WHITE1BIT) /* 两种白色的或 */

/* 将mark位与两个白色进行比较，只要其中一个置位就是白色的 */
#define iswhite(x)      test2bits((x)->gch.marked, WHITE0BIT, WHITE1BIT)
/* 将mark位与黑色位进行比较 */
#define isblack(x)      testbit((x)->gch.marked, BLACKBIT)
/* 既不是白色，也不是黑色 */
#define isgray(x)       (!isblack(x) && !iswhite(x))
/* 不是当前的白色 */
#define otherwhite(g)   (g->currentwhite ^ WHITEBITS)

#endif /* lgc_h */
