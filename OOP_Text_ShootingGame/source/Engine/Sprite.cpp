#include "stdafx.h"
#include "Sprite.h"

bool Sprite::Save(const WCHAR* filename)
{
    FILE* file = nullptr;
    _wfopen_s(&file, filename, L"wb");
    if (file == nullptr)
    {
        PrintError(L"open err %s", filename);
        return false;
    }

    if (fwrite(&m_Width, sizeof(int), 1, file) != 1)
    {
        PrintError(L"fwrite err");
        fclose(file);
        return false;
    }

    if (fwrite(&m_Height, sizeof(int), 1, file) != 1)
    {
        PrintError(L"fwrite err");
        fclose(file);
        return false;
    }

    size_t size = (size_t)(m_Width * m_Height);
    if (fwrite(m_Glyphs, sizeof(WCHAR), size, file) != size)
    {
        PrintError(L"fwrite err");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

bool Sprite::Load(const WCHAR* filename)
{
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

    size = size_t(m_Width * m_Height);
    result = fread(m_Glyphs, sizeof(WCHAR), size, file);
    if (result != size)
    {
        success = false;
    }

close_and_out:
    fclose(file);
    return success;
}
