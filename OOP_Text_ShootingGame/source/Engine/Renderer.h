#pragma once

#include "Sprite.h"

class Renderer
{
public:
    Renderer(int width, int height)
        : m_Width{ width }
        , m_Height{ height }
    {
        size_t size = (size_t)(width * height);
        m_ScreenBuffer = new WCHAR[size];
        wmemset(m_ScreenBuffer, L' ', width * height);

        m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // 콘솔 화면 크기를 m_Width * m_Height로 딱 맞추기
        {
            SMALL_RECT rectWindow = { 0, 0, 1, 1 };
            SetConsoleWindowInfo(m_hConsole, TRUE, &rectWindow);

            COORD coord = { (short)width, (short)height };
            SetConsoleScreenBufferSize(m_hConsole, coord);

            m_RectWindow = { 0, 0, (short)(width - 1), (short)(height - 1) };
            SetConsoleWindowInfo(m_hConsole, TRUE, &m_RectWindow);
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
            SetCurrentConsoleFontEx(m_hConsole, false, &cfi);
        }

        // 커서 숨기기
        {
            CONSOLE_CURSOR_INFO stConsoleCursor;
            stConsoleCursor.bVisible = FALSE;
            stConsoleCursor.dwSize = 1;

            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stConsoleCursor);
        }
    }

    ~Renderer()
    {
        delete[] m_ScreenBuffer;
    }

    void Draw(int x, int y, WCHAR wchar)
    {
        if (y >= m_Height || y < 0)
            return;
        if (x >= m_Width || x < 0)
            return;

        m_ScreenBuffer[x + y * m_Width] = wchar;
    }

    void DrawString(int x, int y, const WCHAR* wcs)
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

    void DrawSprite(int x, int y, Sprite* sprite)
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

    void Output()
    {
        DWORD bytesWritten;
        WriteConsoleOutputCharacterW(m_hConsole, m_ScreenBuffer, m_Width * m_Height, { 0, 0 }, &bytesWritten);
    }

    void ClearBuffer()
    {
        wmemset(m_ScreenBuffer, L' ', m_Width * m_Height);
    }

private:
    void MoveCursor(int iPosX, int iPosY)
    {
        COORD stCoord;
        stCoord.X = iPosX;
        stCoord.Y = iPosY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), stCoord);
    }

private:
    WCHAR* m_ScreenBuffer;
    int m_Width;
    int m_Height;

    HANDLE m_hConsole;
    SMALL_RECT m_RectWindow;
};

