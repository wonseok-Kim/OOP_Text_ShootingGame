#include "stdafx.h"
#include "SceneGame.h"

#include "Engine/Input.h"

#include "Player.h"

SceneGame::SceneGame()    
{
	m_Player = new Player(0, 0);
	m_ObjectList.push_back(m_Player);
}

SceneGame::~SceneGame()
{
	for (ObjectBase* obj : m_ObjectList)
	{
		delete obj;
	}
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
		obj->Update();
	}
}

void SceneGame::Render(Renderer * renderer)
{
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render(renderer);
	}
}
