#pragma once

#include "Sprite.h"
#include "ResourceManager.h"
#include "StageParser.h"

class ResourceLoader
{
public:
    static bool Load()
    {
        if (!LoadSprite())
            return false;

        if (!LoadShotInfo())
            return false;

        if (!LoadPattern())
            return false;

        if (!LoadStage())
            return false;

        return true;
    }

    static bool LoadSprite()
    {
        FILE* file = nullptr;
        _wfopen_s(&file, L"Resources/Sprite/sprites.txt", L"r");
        if (file == nullptr)
        {
            PrintError(L"fopen err");
            return false;
        }

        int spritesCount;
        int result = fwscanf_s(file, L"%d", &spritesCount);
        if (result != 1)
        {
            PrintError(L"fscanf err");
            fclose(file);
            return false;
        }

        WCHAR filename[MAX_PATH];
        for (int i = 0; i < spritesCount; ++i)
        {
            result = fwscanf_s(file, L"%s", filename, (unsigned)_countof(filename));
            if (result != 1)
            {
                PrintError(L"fscanf err");
                fclose(file);
                return false;
            }

            if (!ResourceManager::Instance().AddSprite(filename))
            {
                PrintError(L"sprite load err");
                return false;
            }
        }

        return true;
    }

    static bool LoadShotInfo()
    {
        FILE* file = nullptr;
        _wfopen_s(&file, L"Resources/ShotInfo/shot_infos.txt", L"r");
        if (file == nullptr)
        {
            PrintError(L"fopen err");
            return false;
        }

        int shotInfosCount;
        int result = fwscanf_s(file, L"%d", &shotInfosCount);
        if (result != 1)
        {
            PrintError(L"fscanf err");
            fclose(file);
            return false;
        }

        WCHAR filename[MAX_PATH];
        for (int i = 0; i < shotInfosCount; ++i)
        {
            result = fwscanf_s(file, L"%s", filename, (unsigned)_countof(filename));
            if (result != 1)
            {
                PrintError(L"fscanf err");
                fclose(file);
                return false;
            }

            if (!ResourceManager::Instance().AddShotInfo(filename))
            {
                PrintError(L"shotInfo load err");
                return false;
            }
        }

        return true;
    }

    static bool LoadPattern()
    {
        FILE* file = nullptr;
        _wfopen_s(&file, L"Resources/Pattern/patterns.txt", L"r");
        if (file == nullptr)
        {
            PrintError(L"fopen err");
            return false;
        }

        int patternsCount;
        int result = fwscanf_s(file, L"%d", &patternsCount);
        if (result != 1)
        {
            PrintError(L"fscanf err");
            fclose(file);
            return false;
        }

        WCHAR filename[MAX_PATH];
        for (int i = 0; i < patternsCount; ++i)
        {
            result = fwscanf_s(file, L"%s", filename, (unsigned)_countof(filename));
            if (result != 1)
            {
                PrintError(L"fscanf err");
                fclose(file);
                return false;
            }

            PatternParser parser;
            parser.InitByFilename(filename);
            parser.Run();
        }

        return true;
    }

    static bool LoadStage()
    {
        return true;
    }
};

