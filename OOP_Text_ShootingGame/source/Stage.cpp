#include "stdafx.h"
#include "Stage.h"

#include "ResourceManager.h"

bool ShotInfo::Load(const WCHAR* filename)
{
    FILE* file = nullptr;
    _wfopen_s(&file, filename, L"r");
    if (file == nullptr)
    {
        PrintError(L"'%s' file open err", filename);
        return false;
    }

    int result = fscanf_s(file, "%d", &shotCount);
    if (result != 1)
    {
        PrintError(L"'%s' file scan err", filename);
        return false;
    }

    for (int i = 0; i < shotCount; ++i)
    {
        result = fscanf_s(file, "%hd, %hd", &dir[i].X, &dir[i].Y);
        if (result != 2)
        {
            PrintError(L"'%s' file scan err", filename);
            return false;
        }
    }

    char chfilename[MAX_PATH];
    result = fscanf_s(file, "%s", chfilename, (unsigned)MAX_PATH);
    if (result != 1)
    {
        PrintError(L"'%s' file scan err", filename);
        return false;
    }

    WCHAR wchfilename[MAX_PATH];
    result = MultiByteToWideChar(CP_ACP, 0, chfilename, MAX_PATH, wchfilename, MAX_PATH);
    if (result == 0)
    {
        PrintError(L"MultiByteToWideChar err : %d", GetLastError());
        return false;
    }

    sprite = ResourceManager::Instance().GetSprite(wchfilename);
    if (sprite == nullptr)
    {
        PrintError(L"sprite init err in ShotInfo ");
        return false;
    }

    fclose(file);
    return true;
}
