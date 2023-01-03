#pragma once

#pragma comment(lib, "Winmm.lib")

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <wchar.h>
#include <windows.h>
#include <timeapi.h>

#define PrintError(msg, ...) do \
{ \
    fprintf(stderr, "\nFILE: %s\nFUNC: %s\nLINE: %d\nMSG: ", __FILE__, __FUNCTION__, __LINE__); \
    fwprintf(stderr, msg, __VA_ARGS__); \
} while (false)


#ifdef _DEBUG

#define Assert(expr, msg) do \
{ \
    if (!(expr)) \
    { \
        wprintf((msg)); \
        assert((expr)); \
    } \
} while (false)

#else

#define Assert(expr, msg) ((void)0)

#endif // _DEBUG