#pragma once

#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/Sprite.h"

#include "ObjectType.h"
#include "Stage.h"

class Enemy : public ObjectBase
{
public:
    Enemy(EnemyInfo* pInfo)
        : ObjectBase(ObjectType_Enemy, pInfo->startCoord.X, pInfo->startCoord.Y)
    {
        m_Sprite = pInfo->sprite;        
        m_bLoopPatern = pInfo->bLoopPatterns;
        m_PatternList = pInfo->pPatternList;
        m_CurPatternIter = m_PatternList->begin();
        m_CurPattern = *m_CurPatternIter;
    }

    virtual ~Enemy() override = default;

    virtual void Update(DWORD framesCount) override
    {
        if (framesCount == 0)
            return;

        m_Duration++;

        if (m_Duration % m_CurPattern->moveInterval == 0)
        {
            m_X += m_CurPattern->moveTo.X;
            m_Y += m_CurPattern->moveTo.Y;
        }

        if (m_Duration % m_CurPattern->shotInterval == 0)
        {
            Shot();
        }

        if (m_Duration % m_CurPattern->duration == 0)
        {
            ++m_CurPatternIter;
            if (m_CurPatternIter == m_PatternList->end())
                m_CurPatternIter = m_PatternList->begin();
            m_CurPattern = *m_CurPatternIter;
            m_Duration = 0;
        }
    }

    virtual void Render(Renderer* renderer)
    {
        renderer->DrawSprite(m_X, m_Y, m_Sprite);
    }

private:
    void Shot()
    {

    }

private:
    Sprite* m_Sprite;
    PatternList::iterator m_CurPatternIter;
    Pattern* m_CurPattern;
    PatternList* m_PatternList;
    int m_Duration = 0;
    bool m_bLoopPatern;
};

