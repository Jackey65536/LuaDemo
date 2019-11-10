//
//  luaconf.h
//  LuaDemo
//
//  Created by 刘杰 on 2019/11/9.
//  Copyright © 2019 刘杰. All rights reserved.
//

#ifndef luaconf_h
#define luaconf_h

#include <limits.h>
#include <stddef.h>

#if defined(__STRICT_ANSI__)
#define LUA_ANSI
#endif

#if !defined(LUA_ANSI) && defined(_WIN32)
#define LUA_WIN
#endif

#if defined(LUA_USE_LINUX)
#define LUA_USE_POSIX
#define LUA_USE_DLOPEN      /* needs an extra library: -ldl */
#define LUA_USE_READLINE    /* needs some extra libraries */
#endif

#if defined(LUA_USE_MACOSX)
#define LUA_USE_POSIX
#define LUA_DL_DYLD     /* does not need extra library */
#endif

/*
 @@ LUA_USE_POSIX includes all functionallity listed as X/Open System
 @* Interfaces Extension (XSI).
 ** CHANGE it (define it) if your system is XSI compatible.
 */
#if defined(LUA_USE_POSIX)
#define LUA_USE_MKSTEMP
#define LUA_USE_ISATTY
#define LUA_USE_POPEN
#define LUA_USE_ULONGJMP
#endif

/*
 @@ LUA_PATH and LUA_CPATH are the names of the environment variables that
 @* Lua check to set its paths
 @@ LUA_INIT is the name of the environment variable that Lua
 @* checks fo initialization code.
 ** CHANGE them if you want diffent names.
 */
#define LUA_PATH    "LUA_PATH"
#define LUA_CPATH   "LUA_CPATH"
#define LUA_INIT    "LUA_INIT"

/*
 @@ LUA_PATH_DEFAULT is the default path that Lua uses to look fo Lua libraries.
 @@ LUA_CPATH_DEFAULT is the default path that Lua uses to look for C libraries.
 ** CHANGE them if your machine has a non-conventional directory
 ** hierarchy or if you want to install your libraries in
 ** non-conventional directories.
 */
#if defined(_WIN32)
/*
** In Windows, any exclamation mark ('!') in the path is replaced by the
** path of the directory of the executable file of the current process.
*/
#define LUA_LDIR    "!\\lua\\"
#define LUA_CDIR    "!\\"
#define LUA_PATH_DEFAULT    \
    ".\\?.lua;" LUA_LDIR"?.lua;" LUA_LDIR"?\\init.lua;" \
                LUA_CDIR"?.lua;" LUA_CDIR"?\\init.lua"
#define LUA_CPATH_DEFAULT   \
    ".\\?.dll;" LUA_CDIR"?.dll;" LUA_CDIR"loadall.dll"

#else

#define LUA_ROOT    "/usr/local"
#define LUA_LDIR    LUA_ROOT "share/lua/5.1/"
#define LUA_CDIR    LUA_ROOT "lib/lua/5.1/"
#define LUA_PATH_DEFAULT \
    "./?.lua;"  LUA_LDIR"?.lua;" LUA_LDIR"?/init.lua;" \
                LUA_CDIR"?.lua;" LUA_CDIR"?/init.lua"
#define LUA_CPATH_DEFAULT \
    "./?.so;"   LUA_CDIR"?.so;" LUA_CDIR"loadall.so"
#endif

/*
 @@ LUA_DIRSEP is the directory separator (for submodules).
 ** CHANGE it if your machine does not use "/" as the directory separator
 ** and is not Windows. (On Windows Lua automatically uses "\".)
 */
#if defined(_WIN32)
#define LUA_DIRSEP "\\"
#else
#define LUA_DIRSEP "/"
#endif

/*
@@ LUA_PATHSEP is the character that separates templates in a path.
@@ LUA_PATH_MARK is the string that marks the substitution points in a
@* template.
@@ LUA_EXECDIR in a Windows path is replaced by the executable's
@* directory.
@@ LUA_IGMARK is a mark to ignore all before it when bulding the
@* luaopen_ function name.
** CHANGE them if for some reason your system cannot use those
** characters. (E.g., if one of those characters is a common character
** in file/directory names.) Probably you do not need to change them.
*/
#define LUA_PATHSEP ";"
#define LUA_PATH_MARK "?"
#define LUA_EXECDIR "!"
#define LUA_IGMARK "-"

/*
 @@ LUA_INTEGER is the integral type used by lua_pushinteger/lua_tointeger.
 ** CHANGE that if ptrdiff_t is not adequate on your machine. (On most
 ** machines, ptrdiff_t gives a good choice between int or long.)
 */
#define LUA_INTEGER ptrdiff_t

/*
 @@ LUA_API is a mark for all core API functions.
 @@ LUALIB_API is a mark for all standard library functions.
 ** CHANGE them if you need to define those functions in some special way.
 ** For instance, if you want to create one Windows DLL with the core and
 ** the libraries, you may want to use the following definition (define
 ** LUA_BUILD_AS_DLL to get it).
 */
#if defined(LUA_BUILD_AS_DLL)

#if defined(LUA_CORE) || defined(LUA_LIB)
#define LUA_API __declspec(dllexport)
#else
#define LUA_API __declspec(dllimport)
#endif

#else

#define LUA_API     extern

#endif

/* more often than not the libs go together with the core */
#define LUALIB_API  LUA_API

/*
 @@ LUAI_FUNC is a mark for all extern functions that are not to be
 @* exported to outside modules.
 @@ LUAI_DATA is a mark for all extern (const) variables that are not to
 @* be exported to outside moudles.
 ** CHANGE them if you need to mark them in some special way. Elf/gcc
 ** (versions 3.2 and later) mark them as "hidden" to optimize access
 ** when Lua is compiled as a shared library.
 */
#if defined(luaall_c)
#define LUAI_FUNC   static
#define LUAI_DATA   /* empty*/

#elif defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
      defined(__ELF__)
#define LUAI_FUNC   __attribute__((visibility("hidden"))) extern
#define LUAI_DATA   LUAI_FUNC

#else
#define LUAI_FUNC   extern
#define LUAI_DATA   extern
#endif

/*
 @@ LUA_QL describes how error messages quote program elements.
 ** CHANGE it if you want a different appearance.
 */
#define LUA_QL(x)   "'" x "'"
#define LUA_QS      LUA_QL("%s")

/*
 @@ LUA_IDSIZE gives the maximum size for the description of the source
 @* of a function in debug information.
 ** CHANGE it if you want a different size.
 */
#define LUA_IDSIZE  60

#if defined(lua_c) || defined(luaall_c)
/*
@@ lua_stdin_is_tty detects whether the standard input is a 'tty' (that
@* is, whether we're running lua interactively).
** CHANGE it if you have a better definition for non-POSIX/non-Windows
** systems.
*/
#if defined(LUA_USE_ISATTY)
#include <unistd.h>
#define lua_stdin_is_tty() isatty(0)
#elif defined(LUA_WIN)
#include <io.h>
#include <stdio.h>
#define lua_stdin_is_tty()  _isattry(_fileno(stdin))
#else
#define lua_stdin_is_tty()  1   /* assume stdin is a tty*/
#endif

/*
@@ LUA_PROMPT is the default prompt used by stand-alone Lua.
@@ LUA_PROMPT2 is the default continuation prompt used by stand-alone Lua.
** CHANGE them if you want different prompts. (You can also change the
** prompts dynamically, assigning to globals _PROMPT/_PROMPT2.)
*/
#define LUA_PROMPT      "> "
#define LUA_PROMPT2     ">> "

/*
@@ LUA_PROGNAME is the default name for the stand-alone Lua program.
** CHANGE it if your stand-alone interpreter has a different name and
** your system is not able to detect that name automatically.
*/
#define LUA_PROGNAME        "lua"

/*
@@ LUA_MAXINPUT is the maximum length for an input line in the
@* stand-alone interpreter.
** CHANGE it if you need longer lines.
*/
#define LUA_MAXINPUT    512

/*
 @@ lua_readline defines how to show a prompt and then read a line from
 @* the standard input.
 @@ lua_saveline defines how to "save" a read line in a "history".
 @@ lua_freeline defines how to free a line read by lua_readline.
 ** CHANGE them if you want to improve this functionality (e.g., by using
 ** GNU readline and history facilities).
 */
#if defined(LUA_USE_READLINE)
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define lua_readline(L,b,p)    ((void)L, ((b)=readline(p)) != NULL)
#define lua_saveline(L,idx) \
    if (lua_strlen(L,idx) > 0)  /* non-empty line? */ \
      add_history(lua_tostring(L, idx));  /* add it to history */
#define lua_freeline(L,b)    ((void)L, free(b))
#else
#define lua_readline(L,b,p)    \
    ((void)L, fputs(p, stdout), fflush(stdout),  /* show prompt */ \
    fgets(b, LUA_MAXINPUT, stdin) != NULL)  /* get line */
#define lua_saveline(L,idx)    { (void)L; (void)idx; }
#define lua_freeline(L,b)    { (void)L; (void)b; }
#endif

#endif

// TODO:

/*
 @@ LUAI_BITSINT defines the number of bits in an int.
 ** CHANGE here if Lua cannot automatically detect the number of bits of
 ** your machine. Probaly you do not need to change this.
 */
#if INT_MAX-20 < 32760
#define LUAI_BITSINT    16
#elif INT_MAX > 2147483640L
#define LUAI_BITSINT    32
#else
#error "you must define LUA_BITSINT with number of bits in an integer"
#endif

/*
 @@ LUAI_UINT32 is an unsigned integer with at least 32 bits.
 @@ LUAI_INT32 is an signed integer with at least 32 bits.
 @@ LUAI_UMEM is an unsigned integer big enough to count the total
 @* memory used by lua.
 @@ LUAI_MEM is a signed integer big enough to count the total memory
 @* used by lua.
 ** CHANGE here if for some weird reason the default definitions are not
 ** good enough for your machine. (The definitions in the 'else'
 ** part always works, but may waste space on machines with 64-bit
 ** longs.) Probably you do not need to change this.
 */
#if LUAI_BITSINT >= 32
#define LUAI_UINT32 unsigned int
#define LUAI_INT32  int
#define LUAI_MAXINT32   INT_MAX
#define LUAI_UMEM   size_t
#define LUAI_MEM    ptrdiff_t
#else
/* 16-bit ints */
#define LUAI_UINT32 unsigned long
#define LUAI_INT32  long
#define LUAI_MAXINT32   LONG_MAX
#define LUAI_UMEM   unsigned long
#define LUAI_MEM    long
#endif

#define LUA_NUMBER_DOUBLE
#define LUA_NUMBER double

#define LUAI_USER_ALIGNMENT_T union { double u; void *s; long l; }



/*
 @@ LUA_INTFRMLEN is the length modifier for integer conversions
 @* in 'string.format'.
 @@ LUA_INTFRM_T is the integer type correspoding to the previous length
 @* modifier.
 ** CHANGE them if your system supports long long or does not support long.
 */
#if defined(LUA_USELONGLONG)
#define LUA_INTFRMLEN   "ll"
#define LUA_INTFRM_T    long long
#else
#define LUA_INTFRMLEN   "l"
#define LUA_INTFRM_T    long
#endif

#endif /* luaconf_h */
