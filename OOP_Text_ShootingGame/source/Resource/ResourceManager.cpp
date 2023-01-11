#include "stdafx.h"
#include "ResourceManager.h"

#include "Engine/Sprite.h"

ResourceManager::~ResourceManager()
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
        delete[] m_Stages[i]->items;
        delete m_Stages[i];
    }
}

bool ResourceManager::AddSprite(const WCHAR* spriteFilename)
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

Sprite* ResourceManager::GetSprite(const WCHAR* spriteFilename)
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

bool ResourceManager::AddShotInfo(const WCHAR* filename)
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

ShotInfo* ResourceManager::GetShotInfo(const WCHAR* filename)
{
    int i;
    for (i = 0; i < m_BulletInfosCount; ++i)
    {
        if (wcscmp(m_ShotInfoFilenames[i], filename) == 0)
            break;
    }

    if (i == m_BulletInfosCount)
    {
        PrintError(L"%s �� �ش��ϴ� ShotInfo�� ����.", filename);
        return nullptr;
    }

    return &m_ShotInfos[i];
}

PatternList* ResourceManager::GetPatternList(const WCHAR* filename)
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

bool ResourceManager::AddStage(Stage* stage)
{
    if (m_StagesCount >= MAX_STAGES)
    {
        PrintError(L"Stage �ִ� ���� ������ �Ѿ��.");
        return false;
    }

    m_Stages[m_StagesCount++] = stage;
    return true;
}
