#pragma once

#include "Engine/ObjectBase.h"

#include "ObjectType.h"
#include "Stage.h"

class Sprite;
class SceneBase;

enum PlayerState
{
    MOVE_UP = 0x1,
    MOVE_DOWN = 0x2,
    MOVE_RIGHT = 0x4,
    MOVE_LEFT = 0x8,
    ATTACK = 0x10,
};

class Player : public ObjectBase
{
public:
    Player(SceneBase* scene, PlayerInfo* pInfo)
        :ObjectBase(scene, ObjectType_Player, pInfo->startCoord.X, pInfo->startCoord.Y)
        , m_Sprite{ pInfo->sprite }
    {
    }

    virtual ~Player() override = default;

    virtual void Update(DWORD framesCount) override;
    virtual void Render(Renderer* renderer) override;

    void SetState(PlayerState state) { m_State |= state; }

private:
    Sprite* m_Sprite;
    UINT m_State = 0;
};

