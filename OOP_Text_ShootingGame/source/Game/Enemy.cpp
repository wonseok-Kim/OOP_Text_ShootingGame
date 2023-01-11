#include "stdafx.h"
#include "Enemy.h"

#include "Engine/Renderer.h"
#include "Engine/SceneBase.h"
#include "Engine/Sprite.h"

#include "Bullet.h"
#include "SceneGame.h"

void Enemy::Update()
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

void Enemy::Render(Renderer* renderer)
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

void Enemy::OnCollision(ObjectBase* other)
{
    if (other->GetObjectType() == ObjectType_Bullet)
    {
          Bullet* b = (Bullet*)other;
        if (b->GetWhoShot() != ObjectType_Player)
            return;

        m_HP--;
        if (m_HP == 0)
            Destroy(this, 5);

        Destroy(b);
    }
}

void Enemy::OnDestroy()
{    
    SceneGame* sceneGame = (SceneGame*)m_Scene;
    sceneGame->OnEnemyDie();
}
