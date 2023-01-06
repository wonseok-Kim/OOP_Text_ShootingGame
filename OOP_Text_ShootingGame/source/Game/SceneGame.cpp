#include "stdafx.h"
#include "SceneGame.h"

#include "Engine/Input.h"

#include "Player.h"
#include "Enemy.h"

SceneGame::SceneGame(int curStage)    
{
	m_CurrentStageInfo = ResourceManager::Instance().GetStage(curStage);
	
	m_Player = new Player(&m_CurrentStageInfo->player);
	m_ObjectList.push_back(m_Player);

	for (int i = 0; i < m_CurrentStageInfo->enemiesCount; ++i)
	{
		m_ObjectList.push_back(new Enemy(&m_CurrentStageInfo->enemies[i]));
	}
}

SceneGame::~SceneGame()
{
}

void SceneGame::Update()
{	
	auto& input = Input::Instance();
	PlayerKeyState& playerKeyState = m_Player->SetState();

	if (input.GetKey(VK_LEFT).held)
	{
		playerKeyState.left = true;
	}
	if (input.GetKey(VK_RIGHT).held)
	{
		playerKeyState.right = true;
	}
	if (input.GetKey(VK_UP).held)
	{
		playerKeyState.up = true;
	}
	if (input.GetKey(VK_DOWN).held)
	{
		playerKeyState.down = true;
	}

	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Update(m_FramesCount);
	}

	m_FramesCount++;
}

void SceneGame::Render(Renderer * renderer)
{
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render(renderer);
	}
}
