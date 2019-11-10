/*
    Buffered streams
 */

#ifndef lzio_h
#define lzio_h

#include "lua.h"

#define EOZ (-1)    /* end of stream*/

typedef struct Mbuffer {
    char *buffer;
    size_t n;
    size_t buffsize;
} Mbuffer;

#endif /* lzio_h */
