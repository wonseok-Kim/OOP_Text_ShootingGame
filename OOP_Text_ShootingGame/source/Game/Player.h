#pragma once

#include "Engine/ObjectBase.h"

#include "ObjectType.h"
#include "Stage.h"

class Sprite;
class SceneBase;
class GameInfo;

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
    Player(SceneBase* scene, PlayerInfo* pInfo);

    virtual ~Player() override = default;

    virtual void Update(DWORD framesCount) override;
    virtual void Render(Renderer* renderer) override;

    virtual void OnCollision(ObjectBase* other) override;

    void SetState(PlayerState state) { m_State |= state; }

    void AttachGameInfo(GameInfo* gameInfo) { m_GameInfo = gameInfo; }

private:
    UINT m_State = 0;

    int m_HP = 3;
    int m_Life = 3;

    ShotInfo* m_ShotInfo = nullptr;
    GameInfo* m_GameInfo = nullptr;
};

