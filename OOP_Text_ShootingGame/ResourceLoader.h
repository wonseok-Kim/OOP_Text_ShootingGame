#pragma once

#include "Sprite.h"
#include "ResourceManager.h"

class ResourceLoader
{
public:
    static bool Load()
    {
        ///////////////////////////////////////////
        // Sprite 파일 읽어오기 ////////////////////
        ///////////////////////////////////////////
        {
            FILE* file = nullptr;
            _wfopen_s(&file, L"Resources/sprites.txt", L"r");
            if (file == nullptr)
            {
                PrintError("fopen err");
                return false;
            }

            int spritesCount;
            int result = fwscanf_s(file, L"%d", &spritesCount);
            if (result != 1)
            {
                PrintError("fscanf err");
                fclose(file);
                return false;
            }

            WCHAR filename[MAX_PATH];
            for (int i = 0; i < spritesCount; ++i)
            {
                result = fwscanf_s(file, L"%s", filename, _countof(filename));
                if (result != 1)
                {
                    PrintError("fscanf err");
                    fclose(file);
                    return false;
                }

                Sprite* sprite = new Sprite;
                if (!sprite->Load(filename))
                {
                    PrintError("Sprite::Load() err");
                    fclose(file);
                    return false;
                }

                ResourceManager::Instance().AddSprite(sprite);
            }
        }
    }
};

