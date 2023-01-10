#pragma once

#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/SceneBase.h"
#include "Engine/Sprite.h"

#include "Bullet.h"
#include "ObjectType.h"
#include "SceneGame.h"
#include "Infos.h"

class Enemy : public ObjectBase
{
public:
    Enemy(EnemyInfo* pInfo)
        :ObjectBase(ObjectType_Enemy)
    {
        m_Sprite = pInfo->sprite;
        m_X = pInfo->startCoord.X;
        m_Y = pInfo->startCoord.Y;

        m_EnemyInfo = pInfo;
        m_CurPatternIter = pInfo->pPatternList->begin();
        m_CurPattern = *m_CurPatternIter;
        m_HP = pInfo->hp;
    }

    virtual ~Enemy() override = default;

    virtual void Update() override
    {
        if (IsDestroying())
            return;

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
                    /*m_Scene->AddObject(new Bullet(m_Scene, m_X + shotInfo->startCoord[i].X, m_Y + shotInfo->startCoord[i].Y,
                        shotInfo->sprite, shotInfo->dir[i], ObjectType_Enemy));*/

                        // Bullet(int x, int y, Sprite * sprite, COORD dir, int whoShot)

                    m_Scene->AddObject(new Bullet(
                        m_X + shotInfo->startCoord[i].X,
                        m_Y + shotInfo->startCoord[i].Y,
                        shotInfo->sprite, shotInfo->dir[i], ObjectType_Enemy));
                }
            }
        }

        if (m_Duration % m_CurPattern->duration == 0)
        {
            ++m_CurPatternIter;
            if (m_CurPatternIter == m_EnemyInfo->pPatternList->end())
            {
                if (m_EnemyInfo->bLoopPatterns)
                    m_CurPatternIter = m_EnemyInfo->pPatternList->begin();
                else
                    Destroy(this);
            }
            m_CurPattern = *m_CurPatternIter;
            m_Duration = 0;
        }
    }

    virtual void Render(Renderer* renderer)
    {
        if (IsDestroying())
        {
            for (int row = 0; row < m_Sprite->Height(); ++row)
            {
                for (int col = 0; col < m_Sprite->Width(); ++col)
                {
                    renderer->Draw(m_X + col, m_Y + row, L'X');
                }
            }

        }
        else
            renderer->DrawSprite(m_X, m_Y, m_Sprite);
    }

    virtual void OnCollision(ObjectBase* other) override;
    virtual void OnDestroy() override;

private:
    EnemyInfo* m_EnemyInfo;
    PatternList::iterator m_CurPatternIter;
    Pattern* m_CurPattern;
    int m_Duration = 0;
    int m_HP;
};

