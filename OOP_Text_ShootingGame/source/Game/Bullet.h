#pragma once

#include "Engine/ObjectBase.h"

#include "Resource/Infos.h"

#include "GameDefine.h"
#include "ObjectType.h"

class Renderer;

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

    virtual void Update() override;
    virtual void Render(Renderer* renderer) override;

    int GetWhoShot() { return m_WhoShot; }

private:
    COORD m_Dir;
    int m_WhoShot;
};

