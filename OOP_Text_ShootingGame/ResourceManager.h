#pragma once

#include "Sprite.h"

enum SpriteKind
{
    SpriteKind_Player = 0,
    SpriteKind_Enemy1,
};

class ResourceManager
{
public:
    static ResourceManager& Instance()
    {
        static ResourceManager inst;
        return inst;
    }

    ~ResourceManager()
    {
        for (int i = 0; i < m_SpritesCount; ++i)
            delete m_Sprites[i];
    }

    bool AddSprite(Sprite* sprite)
    {
        // TODO: 예외처리
        m_Sprites[m_SpritesCount++] = sprite;
    }

    Sprite* GetSprite(SpriteKind kind)
    {
        int idx = (int)kind;
        
        if (idx >= m_SpritesCount)
            return nullptr;

        return m_Sprites[idx];
    }

private:
    ResourceManager() = default;

private:
    Sprite* m_Sprites[10]{ nullptr };
    int m_SpritesCount = 0;
};

