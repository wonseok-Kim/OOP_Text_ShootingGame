#pragma once

#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <wchar.h>

#include <windows.h>
#include <timeapi.h>

#define PrintError(msg, ...) do \
{ \
    fprintf(stderr, "\n\nFILE: %s\nFUNC: %s\nLINE: %d\nMSG: ", __FILE__, __FUNCTION__, __LINE__); \
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