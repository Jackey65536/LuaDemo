/*
    lgc.h
*/

#ifndef lgc_h
#define lgc_h

#include "lobject.h"

/*
    Possible states of the Garbage Collector
*/
#define GCSpause        0
#define GCSpropagate    1
#define GCSsweepstring  2
#define GCSsweep        3
#define GCSfinalize     4

#endif /* lgc_h */
