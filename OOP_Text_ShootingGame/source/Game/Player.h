#pragma once

#include "Engine/ObjectBase.h"

#include "ObjectType.h"
#include "ResourceManager.h"

class Sprite;

typedef union
{
    struct
    {
        bool up;
        bool down;
        bool left;
        bool right;
        bool attack;
    };
    bool keys[5];
} PlayerKeyState;

class Player : public ObjectBase
{
public:
    Player(PlayerInfo* pInfo)
        :ObjectBase(ObjectType_Player, pInfo->startCoord.X, pInfo->startCoord.Y)
        , m_Sprite{ pInfo->sprite }
    {
    }

    virtual ~Player() override = default;

    virtual void Update(DWORD framesCount) override;
    virtual void Render(Renderer* renderer) override;

    PlayerKeyState& SetState() { return m_KeyState; }

private:
    Sprite* m_Sprite;
    PlayerKeyState m_KeyState{};
};

