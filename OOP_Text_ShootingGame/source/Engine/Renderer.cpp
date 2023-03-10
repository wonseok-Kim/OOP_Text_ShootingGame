#include "stdafx.h"
#include "Renderer.h"

#include "Sprite.h"

Renderer::Renderer(int width, int height)
    : m_Width{ width }
    , m_Height{ height }
{
    size_t size = (size_t)(width * height);
    m_ScreenBuffer = new WCHAR[size];
    wmemset(m_ScreenBuffer, L' ', width * height);

    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    BOOL bResult;

    // 콘솔 화면 크기를 m_Width * m_Height로 딱 맞추기
    {
        SMALL_RECT rectWindow = { 0, 0, 1, 1 };
        bResult = SetConsoleWindowInfo(m_hConsole, TRUE, &rectWindow);
        if (!bResult)
        {
            PrintError(L"init failed");
            abort();
        }

        COORD coord = { (short)width, (short)height };
        bResult = SetConsoleScreenBufferSize(m_hConsole, coord);
        if (!bResult)
        {
            PrintError(L"init failed");
            abort();
        }

        m_RectWindow = { 0, 0, (short)(width - 1), (short)(height - 1) };
        bResult = SetConsoleWindowInfo(m_hConsole, TRUE, &m_RectWindow);
        if (!bResult)
        {
            PrintError(L"init failed");
            abort();
        }
    }

    // 폰트 크기 조정하기
    {
        CONSOLE_FONT_INFOEX cfi{ 0, };
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 10;
        cfi.dwFontSize.Y = 15;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;

        wcscpy_s(cfi.FaceName, L"Consolas");
        bResult = SetCurrentConsoleFontEx(m_hConsole, false, &cfi);
        if (!bResult)
        {
            PrintError(L"init failed");
            abort();
        }
    }

    // 커서 숨기기
    {
        CONSOLE_CURSOR_INFO stConsoleCursor;
        stConsoleCursor.bVisible = FALSE;
        stConsoleCursor.dwSize = 1;

        bResult = SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stConsoleCursor);
        if (!bResult)
        {
            PrintError(L"init failed");
            abort();
        }
    }
}

void Renderer::DrawString(int x, int y, const WCHAR* wcs)
{
    Assert(wcs, L"wcs must not be null");

    if (y >= m_Height || y < 0)
        return;
    if (x >= m_Width || x < 0)
        return;

    int len = (int)wcslen(wcs);
    if (x + len - 1 >= m_Width)
    {
        len = m_Width - x;
    }

    for (int i = 0; i < len; ++i)
    {
        m_ScreenBuffer[x + y * m_Width + i] = wcs[i];
    }
}

void Renderer::DrawSprite(int x, int y, Sprite* sprite)
{
    for (int row = 0; row < sprite->Height(); ++row)
    {
        for (int col = 0; col < sprite->Width(); ++col)
        {
            WCHAR glyph = sprite->GetGlyph(col, row);
            if (glyph != L' ')
                Draw(x + col, y + row, glyph);
        }
    }
}
