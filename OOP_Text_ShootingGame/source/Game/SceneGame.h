#pragma once

#include "Engine/SceneBase.h"

class Player;
struct Stage;

class SceneGame : public SceneBase
{
public:
    SceneGame(int curStage = 0);
    virtual ~SceneGame() override;

    virtual void Update() override;
    virtual void Render(Renderer* renderer) override;

    void OnEnemyDie();

    int GetCurrentStageIdx() { return m_CurStageIdx; }

private:
    int m_CurStageIdx;
    Stage* m_CurrentStageInfo;
    Player* m_Player;
    int m_EnemiesCount;
};

