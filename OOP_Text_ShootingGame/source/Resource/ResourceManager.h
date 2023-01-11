#pragma once

#include "PatternList.h"
#include "Infos.h"

class Sprite;

#pragma warning(push)
#pragma warning(disable: 26495) // 멤버 변수 초기화 경고

class ResourceManager
{
public:
    static ResourceManager* Instance()
    {
        static ResourceManager inst;
        return &inst;
    }

    ~ResourceManager();

    bool AddSprite(const WCHAR* spriteFilename);
    Sprite* GetSprite(const WCHAR* spriteFilename);

    bool AddShotInfo(const WCHAR* filename);
    ShotInfo* GetShotInfo(const WCHAR* filename);

    bool AddPatternList(const WCHAR* filename);
    PatternList* GetPatternList(const WCHAR* filename);

    bool AddStage(const WCHAR* filename);
    Stage* GetStage(int stage) 
    { 
        if (stage < 0 || stage >= m_StagesCount)
            return nullptr;

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

    Stage* m_Stages[MAX_STAGES]{};
    int m_StagesCount = 0;
};

#pragma warning(pop)

