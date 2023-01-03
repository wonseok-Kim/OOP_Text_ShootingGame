#pragma once

class Sprite
{
public:
    Sprite() = default;

    Sprite(int width, int height)
    {
        Init(width, height);
    }

    Sprite(const WCHAR* filename)
    {
        Load(filename);
    }

    ~Sprite()
    {
        delete[] m_Glyphs;
    }

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

    // TODO: 에러 성의 있게 고치기
    bool Save(const WCHAR* filename)
    {
        FILE* file = nullptr;
        _wfopen_s(&file, filename, L"wb");
        if (file == nullptr)
            return false;

        if (fwrite(&m_Width, sizeof(int), 1, file) != 1)
            PrintError(L"fwrite err");

        if (fwrite(&m_Height, sizeof(int), 1, file) != 1)
            PrintError(L"fwrite err");

        size_t size = (size_t)(m_Width * m_Height);
        if (fwrite(m_Glyphs, sizeof(WCHAR), size, file) != size)
            PrintError(L"fwrite err");

        fclose(file);
        return true;
    }

    bool Load(const WCHAR* filename)
    {
        delete[] m_Glyphs;
        m_Width = 0;
        m_Height = 0;

        size_t size;
        bool success = true;
        FILE* file = nullptr;
        _wfopen_s(&file, filename, L"rb");
        if (file == nullptr)
            return false;

        size_t result = fread(&m_Width, sizeof(int), 1, file);
        if (result != 1 || m_Width < 1)
        {
            success = false;
            goto close_and_out;
        }

        result = fread(&m_Height, sizeof(int), 1, file);
        if (result != 1 || m_Height < 1)
        {
            success = false;
            goto close_and_out;
        }

        Init(m_Width, m_Height);

        size = m_Width * m_Height; 
        result = fread(m_Glyphs, sizeof(WCHAR), size, file);
        if (result != size)
        {
            success = false;
        }

    close_and_out:
        fclose(file);
        return success;
    }

    void Init(int width, int height)
    {
        m_Glyphs = new WCHAR[width * height];
        wmemset(m_Glyphs, L' ', width * height);

        m_Width = width;
        m_Height = height;
    }

private:
    WCHAR* m_Glyphs = nullptr;
    int m_Width = 0;
    int m_Height = 0;
};

