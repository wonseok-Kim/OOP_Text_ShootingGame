#pragma once

#include "list.h"

#include "Sprite.h"

#include "BulletInfo.h"
#include "PatternParser.h"

using PatternList = wtl::list<Pattern*>;

#pragma warning(push)
#pragma warning(disable: 26495) // 멤버 변수 초기화 왜 안하냐 경고

class ResourceManager
{
    friend bool PatternParser::Run();

public:
    static ResourceManager& Instance()
    {
        static ResourceManager inst;
        return inst;
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
            delete m_BulletInfoFilenames[i];
        }

        for (int i = 0; i < m_PatternListsCount; ++i)
        {
            for (Pattern* p : m_PatternLists[i])
            {
                delete p;
            }

            delete[] m_PatternFilenames[i];
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
        m_BulletInfoFilenames[newIdx] = new WCHAR[len + 1];
        wcscpy_s(m_BulletInfoFilenames[newIdx], len + 1, filename);

        if (!m_BulletInfos[newIdx].Load(filename))
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
            if (wcscmp(m_BulletInfoFilenames[i], filename) == 0)
                break;
        }

        if (i == m_BulletInfosCount)
            return nullptr;

        return &m_BulletInfos[i];
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

private:
    ResourceManager() = default;

private:
    static constexpr int MAX_SPRITES = 10;
    static constexpr int MAX_BULLETS = 10;
    static constexpr int MAX_PATTERN_LISTS = 10;

    Sprite* m_Sprites[MAX_SPRITES];
    WCHAR* m_SpriteFilenames[MAX_SPRITES];
    int m_SpritesCount = 0;

    ShotInfo m_BulletInfos[MAX_BULLETS];
    WCHAR* m_BulletInfoFilenames[MAX_BULLETS];
    int m_BulletInfosCount = 0;

    PatternList m_PatternLists[MAX_PATTERN_LISTS];
    WCHAR* m_PatternFilenames[MAX_PATTERN_LISTS];
    int m_PatternListsCount = 0;
};

#pragma warning(pop)

