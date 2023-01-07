#pragma once

#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/SceneBase.h"
#include "Engine/Sprite.h"

#include "Bullet.h"
#include "ObjectType.h"
#include "Stage.h"

class Enemy : public ObjectBase
{
public:
    Enemy(SceneBase* scene, EnemyInfo* pInfo)
        : ObjectBase(scene, ObjectType_Enemy, pInfo->startCoord.X, pInfo->startCoord.Y)
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
        m_Duration++;

        if (m_Duration % m_CurPattern->moveInterval == 0)
        {
            m_X += m_CurPattern->moveTo.X;
            m_Y += m_CurPattern->moveTo.Y;
        }

        if (m_Duration % m_CurPattern->shotInterval == 0)
        {
            ShotInfo* shotInfo = m_CurPattern->shotInfo;
            for (int i = 0; i < shotInfo->shotCount; ++i)
            {
                m_Scene->AddObject(new Bullet(m_Scene, m_X, m_Y, shotInfo->sprite, shotInfo->dir[i]));
            }
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
    Sprite* m_Sprite;
    PatternList::iterator m_CurPatternIter;
    Pattern* m_CurPattern;
    PatternList* m_PatternList;
    int m_Duration = 0;
    bool m_bLoopPatern;
};

