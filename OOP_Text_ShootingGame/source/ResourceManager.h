#pragma once

#include "Container/list.h"

#include "Engine/Sprite.h"

#include "ItemParser.h"
#include "PatternList.h"
#include "PatternParser.h"
#include "Infos.h"

#pragma warning(push)
#pragma warning(disable: 26495) // 멤버 변수 초기화 경고

class ResourceManager
{
    friend bool PatternParser::ParsePatternsAndAddPatternsToResMgr();

public:
    static ResourceManager* Instance()
    {
        static ResourceManager inst;
        return &inst;
    }

    ~ResourceManager()
    {
        for (int i = 0; i < m_SpritesCount; ++i)
        {
            delete[] m_SpriteFilenames[i];
            delete m_Sprites[i];
        }

        for (int i = 0; i < m_BulletInfosCount; ++i)
        {
            delete[] m_ShotInfoFilenames[i];
        }

        for (int i = 0; i < m_PatternListsCount; ++i)
        {
            for (Pattern* p : m_PatternLists[i])
            {
                delete p;
            }

            delete[] m_PatternFilenames[i];
        }

        for (int i = 0; i < m_StagesCount; ++i)
        {
            delete[] m_Stages[i]->enemies;
            delete m_Stages[i];
        }
    }

    bool AddSprite(const WCHAR* spriteFilename)
    {
        if (m_SpritesCount >= MAX_SPRITES)
        {
            PrintError(L"The sprite storage space is full.");
            return false;
        }
        int newIdx = m_SpritesCount++;

        size_t len = wcslen(spriteFilename);
        m_SpriteFilenames[newIdx] = new WCHAR[len + 1];
        wcscpy_s(m_SpriteFilenames[newIdx], len + 1, spriteFilename);

        m_Sprites[newIdx] = new Sprite;
        bool bResult = m_Sprites[newIdx]->Load(spriteFilename);
        if (!bResult)
        {
            PrintError(L"'%s' sprite file load err", spriteFilename);
            return false;
        }

        return true;
    }

    Sprite* GetSprite(const WCHAR* spriteFilename)
    {        
        int i;
        for (i = 0; i < m_SpritesCount; ++i)
        {
            if (wcscmp(m_SpriteFilenames[i], spriteFilename) == 0)
                break;
        }

        if (i == m_SpritesCount)
            return nullptr;

        return m_Sprites[i];
    }

    bool AddShotInfo(const WCHAR* filename)
    {
        if (m_BulletInfosCount >= MAX_BULLETS)
        {
            PrintError(L"The bullet information storage space is full.");
            return false;
        }
        int newIdx = m_BulletInfosCount++;

        size_t len = wcslen(filename);
        m_ShotInfoFilenames[newIdx] = new WCHAR[len + 1];
        wcscpy_s(m_ShotInfoFilenames[newIdx], len + 1, filename);

        if (!m_ShotInfos[newIdx].Load(filename))
        {
            PrintError(L"bullet info load err");
            return false;
        }

        return true;
    }

    ShotInfo* GetShotInfo(const WCHAR* filename)
    {
        int i;
        for (i = 0; i < m_BulletInfosCount; ++i)
        {
            if (wcscmp(m_ShotInfoFilenames[i], filename) == 0)
                break;
        }

        if (i == m_BulletInfosCount)
        {
            PrintError(L"%s 에 해당하는 ShotInfo가 없다.", filename);
            return nullptr;
        }

        return &m_ShotInfos[i];
    }

    PatternList* GetPatternList(const WCHAR* filename)
    {
        int i;
        for (i = 0; i < m_PatternListsCount; ++i)
        {
            if (wcscmp(m_PatternFilenames[i], filename) == 0)
                break;
        }

        if (i == m_PatternListsCount)
            return nullptr;

        return &m_PatternLists[i];
    }

    bool AddItem(const WCHAR* filename)
    {
        if (m_ItemsCount >= MAX_ITEMS)
        {
            PrintError(L"Stage 최대 저장 개수를 넘어갔다.");
            return false;
        }
                
        int newIdx = m_ItemsCount++;

        size_t len = wcslen(filename);
        m_ItemFilenames[newIdx] = new WCHAR[len + 1];
        wcscpy_s(m_ItemFilenames[newIdx], len + 1, filename);

        ItemParser parser;
        if (!parser.Init(filename))
        {
            PrintError(L"'%s' 파서 초기화하다 오류", filename);
            return false;
        }
        if (!parser.ParseItem(&m_Items[newIdx]))
        {
            PrintError(L"'%s' 파싱하다 오류", filename);
            return false;
        }

        return true;
    }

    ItemInfo* GetItem(const WCHAR* filename)
    {
        int i;
        for (i = 0; i < m_ItemsCount; ++i)
        {
            if (wcscmp(m_ItemFilenames[i], filename) == 0)
                break;
        }

        if (i == m_ItemsCount)
            return nullptr;

        return &m_Items[i];
    }

    bool AddStage(Stage* stage)
    {
        if (m_StagesCount >= MAX_STAGES)
        {
            PrintError(L"Stage 최대 저장 개수를 넘어갔다.");
            return false;
        }

        m_Stages[m_StagesCount++] = stage;
        return true;
    }

    Stage* GetStage(int stage)
    {
        return m_Stages[stage];
    }

    int GetStagesCount() { return m_StagesCount; }

private:
    ResourceManager() = default;

private:
    static constexpr int MAX_SPRITES = 10;
    static constexpr int MAX_BULLETS = 10;
    static constexpr int MAX_PATTERN_LISTS = 10;
    static constexpr int MAX_ITEMS = 10;
    static constexpr int MAX_STAGES = 10;

    Sprite* m_Sprites[MAX_SPRITES]{};
    WCHAR* m_SpriteFilenames[MAX_SPRITES]{};
    int m_SpritesCount = 0;

    ShotInfo m_ShotInfos[MAX_BULLETS];
    WCHAR* m_ShotInfoFilenames[MAX_BULLETS]{};
    int m_BulletInfosCount = 0;

    PatternList m_PatternLists[MAX_PATTERN_LISTS];
    WCHAR* m_PatternFilenames[MAX_PATTERN_LISTS]{};
    int m_PatternListsCount = 0;

    ItemInfo m_Items[MAX_ITEMS];
    WCHAR* m_ItemFilenames[MAX_ITEMS]{};
    int m_ItemsCount = 0;

    Stage* m_Stages[MAX_STAGES]{};
    int m_StagesCount = 0;
};

#pragma warning(pop)

