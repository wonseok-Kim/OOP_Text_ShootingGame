#include "stdafx.h"
#include "SceneGame.h"

#include "Engine/Input.h"
#include "Engine/SceneManager.h"

#include "Enemy.h"
#include "GameInfo.h"
#include "Player.h"
#include "ResourceManager.h"

class PrintStageInfo : public ObjectBase
{
public:
    PrintStageInfo(int curStageIdx)
        : ObjectBase(ObjectType_StageInfo)
    {
        m_X = 4;
        m_Y = GAME_HEIGHT / 2;

        m_Length = swprintf_s(m_szStageInfo, _countof(m_szStageInfo), m_Format, curStageIdx + 1);
    }

    virtual void Update() override
    {
        DWORD framesCount = m_Scene->GetFrames();

        if (m_StartTick == 0)
        {
            m_StartTick = framesCount;
            return;
        }

        m_PrintIdx = (framesCount - m_StartTick) / 15;
        if (m_PrintIdx > m_Length)
        {
            Destroy(this);
        }
    }

    virtual void Render(Renderer* renderer) override
    {
        int i;
        for (i = 0; i < m_Length; ++i)
        {
            if (i > m_PrintIdx)
                break;

            renderer->Draw(m_X + i, m_Y, m_szStageInfo[i]);
        }
        renderer->Draw(m_X + i, m_Y, L'_');
    }

private:
    const WCHAR* m_Format = L"Stage : %02d";

    WCHAR m_szStageInfo[20];
    int m_Length;

    DWORD m_StartTick = 0;
    int m_PrintIdx = 0;
};

class PrintStageClear : public ObjectBase
{
public:
    PrintStageClear()
        : ObjectBase(ObjectType_StageInfo)
    {
        m_X = 4;
        m_Y = GAME_HEIGHT / 2;
    }

    ~PrintStageClear() = default;

    virtual void Update() override
    {
        DWORD framesCount = m_Scene->GetFrames();

        if (m_StartTick == 0)
        {
            m_StartTick = framesCount;
            return;
        }

        m_PrintIdx = (framesCount - m_StartTick) / 15;
        if (m_PrintIdx > m_Length)
        {
            Destroy(this);
        }
    }

    virtual void Render(Renderer* renderer) override
    {
        int i;
        for (i = 0; i < m_Length; ++i)
        {
            if (i > m_PrintIdx)
                break;

            renderer->Draw(m_X + i, m_Y, m_Format[i]);
        }
        renderer->Draw(m_X + i, m_Y, L'_');
    }

    virtual void OnDestroy() override
    {
        SceneGame* scene = (SceneGame*)m_Scene;

        int curIdx = scene->GetCurrentStageIdx();
        int stagesCount = ResourceManager::Instance()->GetStagesCount();
        if (curIdx >= stagesCount)
        {
            SceneManager::Instance()->SetExit();
        }
        else
        {
            SceneManager::Instance()->LoadScene(new SceneGame(curIdx + 1));
        }
    }

private:
    const WCHAR* m_Format = L"Stage Cleared!";
    int m_Length = wcslen(m_Format);

    DWORD m_StartTick = 0;
    int m_PrintIdx = 0;
};

SceneGame::SceneGame(int curStage)
    : m_CurStageIdx{ curStage }
{

}

SceneGame::~SceneGame()
{}

void SceneGame::Update()
{
    Input* input = Input::Instance();

    if (input->GetKey(VK_LEFT).held)
    {
        m_Player->SetState(PlayerState::MOVE_LEFT);
    }
    if (input->GetKey(VK_RIGHT).held)
    {
        m_Player->SetState(PlayerState::MOVE_RIGHT);
    }
    if (input->GetKey(VK_UP).held)
    {
        m_Player->SetState(PlayerState::MOVE_UP);
    }
    if (input->GetKey(VK_DOWN).held)
    {
        m_Player->SetState(PlayerState::MOVE_DOWN);
    }
    if (input->GetKey(VK_SPACE).pressed)
    {
        m_Player->SetState(PlayerState::ATTACK);
    }
    if (input->GetKey(VK_ESCAPE).pressed)
    {
        SceneManager::Instance()->SetExit();
    }

    for (int i = 0; i < m_CurrentStageInfo->enemiesCount; ++i)
    {
        if (GetFrames() == m_CurrentStageInfo->enemies[i].spawnFrame)
        {
            AddObject(new Enemy(&m_CurrentStageInfo->enemies[i]));
        }
    }
}

void SceneGame::Render(Renderer* renderer)
{}

bool SceneGame::OnInit()
{
    m_CurrentStageInfo = ResourceManager::Instance()->GetStage(m_CurStageIdx);
    if (!m_CurrentStageInfo)
    {
        PrintError(L"잘못된 Stage 인덱스가 들어왔습니다.");
        return false;
    }

    m_Player = new Player(&m_CurrentStageInfo->player);
    AddObject(m_Player);

    /*for (int i = 0; i < m_CurrentStageInfo->enemiesCount; ++i)
    {
        AddObject(new Enemy(&m_CurrentStageInfo->enemies[i]));
    }*/
    m_EnemiesCount = m_CurrentStageInfo->enemiesCount;

    GameInfo* pGameInfo = new GameInfo;
    if (!pGameInfo->Init(3, 3))
        return false;

    AddObject(pGameInfo);
    m_Player->AttachGameInfo(pGameInfo);

    AddObject(new PrintStageInfo(m_CurStageIdx));

    return true;
}

void SceneGame::OnEnemyDie()
{
    m_EnemiesCount--;
    if (m_EnemiesCount == 0)
    {
        //m_ObjectManager.AddObject(new PrintStageClear(this));
        AddObject(new PrintStageClear());
    }
}
