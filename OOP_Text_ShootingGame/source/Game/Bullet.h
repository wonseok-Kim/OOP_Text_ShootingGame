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
    Bullet(SceneBase* scene, int x, int y, Sprite* sprite, COORD dir, int whoShot)
        : ObjectBase(scene, sprite, ObjectType_Bullet, x, y)
    {
        m_Dir = dir;
        m_WhoShot = whoShot;
    }

    virtual void Update(DWORD framesCount)
    {
        if (framesCount % 3 == 0)
        {
            m_X += m_Dir.X;
            m_Y += m_Dir.Y;

            if (m_X < 0 || m_X > GAME_WIDTH - 1)
                SetRelease();
            if (m_Y < 0 || m_Y > GAME_HEIGHT - 1)
                SetRelease();
        }
    }

    virtual void Render(Renderer* renderer)
    {
        renderer->DrawSprite(m_X, m_Y, m_Sprite);
    }

    virtual void OnCollision(ObjectBase* other) override;

    int GetWhoShot() { return m_WhoShot; }

private:
    COORD m_Dir;
    int m_WhoShot;
};

