#pragma once

#include "Engine/SceneBase.h"

class Player;

class SceneGame : public SceneBase
{
public:
    SceneGame();
    virtual ~SceneGame() override;

    virtual void Update() override;
    virtual void Render(Renderer* renderer) override;

private:
    Player* m_Player;
};

