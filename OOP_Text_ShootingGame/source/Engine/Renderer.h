#pragma once

class Sprite;

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer() { delete[] m_ScreenBuffer; }

    void Draw(int x, int y, WCHAR wchar)
    {
        if (y >= m_Height || y < 0)
            return;
        if (x >= m_Width || x < 0)
            return;

        m_ScreenBuffer[x + y * m_Width] = wchar;
    }

    void DrawString(int x, int y, const WCHAR* wcs);
    void DrawSprite(int x, int y, Sprite* sprite);

    void Flip()
    {
        DWORD bytesWritten;
        WriteConsoleOutputCharacterW(m_hConsole, m_ScreenBuffer, m_Width * m_Height, { 0, 0 }, &bytesWritten);

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

