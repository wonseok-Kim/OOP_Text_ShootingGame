#pragma once

#include "Engine/SceneBase.h"

class Player;
struct Stage;

class SceneGame : public SceneBase
{
public:
    SceneGame(int curStage = 0, const Player* prevPlayerInfo = nullptr);
    virtual ~SceneGame() override;

    virtual void Update() override;
    virtual void Render(Renderer* renderer) override;

    virtual bool OnInit() override;
    void OnEnemyDie();

    int GetCurrentStageIdx() { return m_CurStageIdx; }

private:
    int m_CurStageIdx;
    Stage* m_CurrentStageInfo = nullptr;
    Player* m_Player = nullptr;
    int m_TotalEnemiesCount = 0;
    int m_CurrentEnemiesCount = 0;

    const Player* m_prevPlayerInfo;
};

