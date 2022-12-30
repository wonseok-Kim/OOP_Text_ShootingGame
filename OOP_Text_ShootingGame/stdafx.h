#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <windows.h>
#include <timeapi.h>

#pragma comment(lib, "Winmm.lib")

#define PrintError(msg, ...) do \
{ \
    fprintf(stderr, "\nFILE: %s\nFUNC: %s\nLINE: %d\nMSG: ", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stderr, msg, __VA_ARGS__); \
} while (false)


#ifdef _DEBUG

#define Assert(expr, msg) do \
{ \
    if (!(expr)) \
    { \
        printf((msg)); \
        assert((expr)); \
    } \
} while (false)

#else

#define Assert(expr, msg) ((void)0)

#endif // _DEBUG