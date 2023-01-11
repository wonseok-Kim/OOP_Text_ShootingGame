#include "stdafx.h"
#include "ResourceLoader.h"

#include "Engine/Sprite.h"

#include "ResourceManager.h"
#include "StageParser.h"

bool ResourceLoader::Load()
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

bool ResourceLoader::LoadSprite()
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

        if (!ResourceManager::Instance()->AddSprite(filename))
        {
            PrintError(L"sprite load err");
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

bool ResourceLoader::LoadShotInfo()
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

        if (!ResourceManager::Instance()->AddShotInfo(filename))
        {
            PrintError(L"shotInfo load err");
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

bool ResourceLoader::LoadPattern()
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
        goto close_file_and_out_LoadPattern;
    }

    WCHAR filename[MAX_PATH];
    for (int i = 0; i < patternsCount; ++i)
    {
        result = fwscanf_s(file, L"%s", filename, (unsigned)_countof(filename));
        if (result != 1)
        {
            PrintError(L"fscanf err");
            goto close_file_and_out_LoadPattern;
        }

        PatternParser parser;

        if (!parser.Init(filename))
            goto close_file_and_out_LoadPattern;

        if (!parser.ParsePatternsAndAddPatternsToResMgr())
        {
            PrintError(L"'%s' 파싱하다 오류", filename);
            goto close_file_and_out_LoadPattern;
        }
    }

    fclose(file);
    return true;

close_file_and_out_LoadPattern:
    fclose(file);
    return false;
}

bool ResourceLoader::LoadStage()
{
    FILE* file = nullptr;
    _wfopen_s(&file, L"Resources/Stage/stages.txt", L"r");
    if (file == nullptr)
    {
        PrintError(L"fopen err");
        return false;
    }

    int stagesCount;
    int result = fwscanf_s(file, L"%d", &stagesCount);
    if (result != 1)
    {
        PrintError(L"fscanf err");
        goto close_file_and_out_LoadStage;
    }

    WCHAR filename[MAX_PATH];
    for (int i = 0; i < stagesCount; ++i)
    {
        result = fwscanf_s(file, L"%s", filename, (unsigned)_countof(filename));
        if (result != 1)
        {
            PrintError(L"fscanf err");
            goto close_file_and_out_LoadStage;
        }

        StageParser parser;

        if (!parser.Init(filename))
            goto close_file_and_out_LoadStage;

        Stage* newStage = new Stage; // delete in ResourceManager::~ResourceManager()
        if (!parser.ParseStage(newStage))
        {
            delete newStage;
            PrintError(L"'%s' 파싱하다 오류", filename);
            goto close_file_and_out_LoadStage;
        }

        if (!ResourceManager::Instance()->AddStage(newStage))
        {
            delete newStage;
            PrintError(L"'%s' 파싱하다 오류", filename);
            goto close_file_and_out_LoadStage;
        }
    }

    fclose(file);
    return true;

close_file_and_out_LoadStage:
    fclose(file);
    return false;
}
