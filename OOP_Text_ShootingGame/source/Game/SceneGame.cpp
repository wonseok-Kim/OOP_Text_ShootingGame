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
    PrintStageInfo(SceneGame* scene, int curStageIdx)
        : ObjectBase(scene, nullptr, ObjectType_StageInfo, 4, GAME_HEIGHT / 2)
    {
        m_Length = swprintf_s(m_szStageInfo, _countof(m_szStageInfo), m_Format, curStageIdx + 1);
    }

    virtual void Update(DWORD framesCount) override
    {        
        if (m_StartTick == 0)
        {
            m_StartTick = framesCount;
            return;
        }


        m_PrintIdx = (framesCount - m_StartTick) / 15;
        if (m_PrintIdx > m_Length)
        {
            SetRelease();
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
    PrintStageClear(SceneGame* scene)
        : ObjectBase(scene, nullptr, ObjectType_StageInfo, 4, GAME_HEIGHT / 2)
    { }

    ~PrintStageClear()
    {
        SceneGame* scene = (SceneGame*)m_Scene;

        int curIdx = scene->GetCurrentStageIdx();

        SceneManager::Instance()->LoadScene(new SceneGame(curIdx + 1));
    }

    virtual void Update(DWORD framesCount) override
    {
        if (m_StartTick == 0)
        {
            m_StartTick = framesCount;
            return;
        }

        m_PrintIdx = (framesCount - m_StartTick) / 15;
        if (m_PrintIdx > m_Length)
        {
            SetRelease();
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

private:
    const WCHAR* m_Format = L"Stage Cleared!";
    int m_Length = wcslen(m_Format);

    DWORD m_StartTick = 0;
    int m_PrintIdx = 0;
};

SceneGame::SceneGame(int curStage)
    : m_CurStageIdx{ curStage }
{
    m_CurrentStageInfo = ResourceManager::Instance()->GetStage(curStage);

    m_Player = new Player(this, &m_CurrentStageInfo->player);
    m_ObjectManager.AddObject(m_Player);

    for (int i = 0; i < m_CurrentStageInfo->enemiesCount; ++i)
    {
        m_ObjectManager.AddObject(new Enemy(this, &m_CurrentStageInfo->enemies[i]));
    }
    m_EnemiesCount = m_CurrentStageInfo->enemiesCount;

    GameInfo* pGameInfo = new GameInfo(this);
    pGameInfo->Init(3, 3); // TODO: Scene에 OnInit 메서드를 만들어 줘야 할까?
    m_ObjectManager.AddObject(pGameInfo);
    m_Player->AttachGameInfo(pGameInfo);

    m_ObjectManager.AddObject(new PrintStageInfo(this, curStage));
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

    m_ObjectManager.Update(m_FramesCount);

    m_FramesCount++;
}

void SceneGame::Render(Renderer* renderer)
{
    m_ObjectManager.Render(renderer);
}

void SceneGame::OnEnemyDie()
{
    m_EnemiesCount--;
    if (m_EnemiesCount == 0)
    {
        m_ObjectManager.AddObject(new PrintStageClear(this));
    }
}
