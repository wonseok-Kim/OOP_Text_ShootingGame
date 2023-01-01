#pragma once

#include "SceneBase.h"

class SceneGame : public SceneBase
{
public:
    SceneGame();
    virtual ~SceneGame() override;

    virtual void Update() override;
    virtual void Render(Renderer* renderer) override;

private:

};

