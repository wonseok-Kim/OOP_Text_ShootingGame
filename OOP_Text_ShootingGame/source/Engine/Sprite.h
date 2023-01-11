#pragma once

class Sprite
{
public:
    Sprite() = default;
    Sprite(int width, int height) { Init(width, height); }
    Sprite(const WCHAR* filename) { Load(filename); }
    ~Sprite() { delete[] m_Glyphs; }

    int Width() { return m_Width; }
    int Height() { return m_Height; }

    void SetGlyph(int x, int y, WCHAR ch)
    {
        if (x < 0 || x >= m_Width)
            return;
        if (y < 0 || y >= m_Height)
            return;

        m_Glyphs[x + y * m_Width] = ch;
    }

    WCHAR GetGlyph(int x, int y)
    {
        return m_Glyphs[x + y * m_Width];
    }
        
    void Init(int width, int height)
    {
        delete[] m_Glyphs;

        size_t size = (size_t)(width * height);
        m_Glyphs = new WCHAR[size];
        wmemset(m_Glyphs, L' ', size);

        m_Width = width;
        m_Height = height;
    }

    bool Save(const WCHAR* filename);
    bool Load(const WCHAR* filename);

private:
    WCHAR* m_Glyphs = nullptr;
    int m_Width = 0;
    int m_Height = 0;
};

