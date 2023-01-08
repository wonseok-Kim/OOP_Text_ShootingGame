#pragma once

#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/SceneBase.h"
#include "Engine/Sprite.h"

#include "Bullet.h"
#include "ObjectType.h"
#include "SceneGame.h"
#include "Stage.h"

class Enemy : public ObjectBase
{
public:
    Enemy(SceneGame* scene, EnemyInfo* pInfo)
        : ObjectBase(scene, pInfo->sprite, ObjectType_Enemy, pInfo->startCoord.X, pInfo->startCoord.Y)
    {
        m_bLoopPatern = pInfo->bLoopPatterns;
        m_PatternList = pInfo->pPatternList;
        m_CurPatternIter = m_PatternList->begin();
        m_CurPattern = *m_CurPatternIter;
        m_HP = pInfo->hp;
    }

    virtual ~Enemy() override
    {
        SceneGame* sceneGame = (SceneGame*)m_Scene;
        sceneGame->OnEnemyDie();
    }

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
                if (rand() % 101 < m_CurPattern->shotChance)
                {
                    m_Scene->AddObject(new Bullet(m_Scene, m_X + shotInfo->startCoord[i].X, m_Y + shotInfo->startCoord[i].Y,
                        shotInfo->sprite, shotInfo->dir[i], ObjectType_Enemy));
                }
            }
        }

        if (m_Duration % m_CurPattern->duration == 0)
        {
            ++m_CurPatternIter;
            if (m_CurPatternIter == m_PatternList->end())
            {
                if (m_bLoopPatern)
                    m_CurPatternIter = m_PatternList->begin();
                else
                    SetRelease();
            }
            m_CurPattern = *m_CurPatternIter;
            m_Duration = 0;
        }
    }

    virtual void Render(Renderer* renderer)
    {
        renderer->DrawSprite(m_X, m_Y, m_Sprite);
    }

    virtual void OnCollision(ObjectBase* other) override;

private:
    PatternList::iterator m_CurPatternIter;
    Pattern* m_CurPattern;
    PatternList* m_PatternList;
    int m_Duration = 0;
    int m_HP;
    bool m_bLoopPatern;
};

