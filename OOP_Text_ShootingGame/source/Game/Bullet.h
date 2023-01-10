#pragma once

#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/Sprite.h"

#include "GameDefine.h"
#include "ObjectType.h"
#include "Stage.h"

class Bullet : public ObjectBase
{
public:
    Bullet(int x, int y, Sprite* sprite, COORD dir, int whoShot)
        : ObjectBase(ObjectType_Bullet)
    {
        m_Sprite = sprite;
        m_X = x;
        m_Y = y;

        m_Dir = dir;
        m_WhoShot = whoShot;
    }

    virtual void Update() override
    {
        DWORD framesCount = m_Scene->GetFrames();

        if (framesCount % 3 == 0)
        {
            m_X += m_Dir.X;
            m_Y += m_Dir.Y;

            if (m_X < 0 || m_X > GAME_WIDTH - 1)
                Destroy(this);
            if (m_Y < 0 || m_Y > GAME_HEIGHT - 1)
                Destroy(this);
        }
    }

    virtual void Render(Renderer* renderer) override
    {
        renderer->DrawSprite(m_X, m_Y, m_Sprite);
    }

    virtual void OnCollision(ObjectBase* other) override;

    int GetWhoShot() { return m_WhoShot; }

private:
    COORD m_Dir;
    int m_WhoShot;
};

