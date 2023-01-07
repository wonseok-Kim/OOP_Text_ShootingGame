#include "stdafx.h"
#include "SceneGame.h"

#include "Engine/Input.h"

#include "Enemy.h"
#include "Player.h"
#include "ResourceManager.h"

SceneGame::SceneGame(int curStage)    
{
	m_CurrentStageInfo = ResourceManager::Instance()->GetStage(curStage);
	
	m_Player = new Player(this, &m_CurrentStageInfo->player);
	m_ObjectList.push_back(m_Player);

	for (int i = 0; i < m_CurrentStageInfo->enemiesCount; ++i)
	{
		m_ObjectList.push_back(new Enemy(this, &m_CurrentStageInfo->enemies[i]));
	}
}

SceneGame::~SceneGame()
{
}

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
	if (input->GetKey(VK_SPACE).held)
	{
		m_Player->SetState(PlayerState::ATTACK);
	}

	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Update(m_FramesCount);
	}

	ObjectList::iterator iter;
	for (iter = m_ObjectList.begin(); iter != m_ObjectList.end(); )
	{
		if (iter->IsRelease())
			iter = m_ObjectList.erase(iter);
		else
			++iter;
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
