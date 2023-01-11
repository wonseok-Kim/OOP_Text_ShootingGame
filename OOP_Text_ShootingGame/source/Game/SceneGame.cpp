#include "stdafx.h"
#include "SceneGame.h"

#include "Engine/Input.h"
#include "Engine/SceneManager.h"

#include "Resource/ResourceManager.h"

#include "CurStageDisplayer.h"
#include "Enemy.h"
#include "GameDefine.h"
#include "InGameUI.h"
#include "Item.h"
#include "Player.h"
#include "SceneTitle.h"

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

	DWORD frames = GetFrames();
	int i;
	for (i = 0; i < m_CurrentStageInfo->enemiesCount; ++i)
	{
		if (frames == m_CurrentStageInfo->enemies[i].spawnFrame)
		{
			AddObject(new Enemy(&m_CurrentStageInfo->enemies[i]));
			m_CurrentEnemiesCount++;
		}
	}

	for (i = 0; i < m_CurrentStageInfo->itemsCount; ++i)
	{
		if (frames == m_CurrentStageInfo->items[i].spawnFrame)
		{
			AddObject(new Item(&m_CurrentStageInfo->items[i]));
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

	m_TotalEnemiesCount = m_CurrentStageInfo->enemiesCount;

	InGameUI* pUI = new InGameUI;
	if (!pUI->Init(MAX_PLAYER_HP))
		return false;

	AddObject(pUI);
	m_Player->AttachGameUI(pUI);

	AddObject(new CurStageDisplayer(m_CurStageIdx));

	return true;
}

void SceneGame::OnEnemyDie()
{
	m_TotalEnemiesCount--;
	if (m_TotalEnemiesCount == 0)
	{
		AddObject(new CurStageDisplayer(m_CurStageIdx, true));
	}
}
