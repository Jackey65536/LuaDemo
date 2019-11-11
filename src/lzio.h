/*
    Buffered streams
 */

#ifndef lzio_h
#define lzio_h

#include "lua.h"

#define EOZ (-1)    /* end of stream*/

typedef struct Zio ZIO;

#define char2int(c) cast(int, cast(unsigned char, (c)))

#define zgetc(z)    ((z)->n--)>0 ? char2int(*(z)->p++) : luaZ_fill(z)

typedef struct Mbuffer {
    char *buffer;
    size_t n;
    size_t buffsize;
} Mbuffer;

/* -------------- Private Part ---------------- */

struct Zio {
    size_t n;       /* bytes still unread */
    const char *p;  /* current position in buffer */
    lua_Reader reader;
    void* data;     /* additional data */
    lua_State *L;   /* Lua state (for reader) */
};

LUAI_FUNC int luaZ_fill (ZIO *z);

#endif /* lzio_h */
