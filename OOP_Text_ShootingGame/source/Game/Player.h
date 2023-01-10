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
    Player(PlayerInfo* pInfo);

    virtual ~Player() override = default;

    virtual void Update() override;
    virtual void Render(Renderer* renderer) override;

    virtual void OnCollision(ObjectBase* other) override;

    void SetState(PlayerState state) { m_State |= state; }

    void AttachGameInfo(GameInfo* gameInfo) { m_GameInfo = gameInfo; }

private:
    static constexpr DWORD m_InvicibleFrames = 60;

    UINT m_State = 0;

    int m_HP = 3;
    int m_Life = 3;

    DWORD m_HittedFrame = 0;
    bool m_bInvicible = false;

    ShotInfo* m_ShotInfo = nullptr;
    GameInfo* m_GameInfo = nullptr;
};

