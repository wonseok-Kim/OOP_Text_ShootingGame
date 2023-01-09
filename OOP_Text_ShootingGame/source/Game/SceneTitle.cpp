#include "stdafx.h"
#include "SceneTitle.h"

#include "Engine/Input.h"
#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/SceneManager.h"

#include "SceneGame.h"

SceneTitle::SceneTitle()
	: SceneBase()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{	
	Input* input = Input::Instance();

	if (input->GetKey(VK_RIGHT).pressed ||
		input->GetKey(VK_UP).pressed)
	{
		m_CurrentMenu++;
		if (m_CurrentMenu >= MAX_MENU)
			m_CurrentMenu = 0;
	}
	if (input->GetKey(VK_LEFT).pressed ||
		input->GetKey(VK_DOWN).pressed)
	{
		m_CurrentMenu--;
		if (m_CurrentMenu < 0)
			m_CurrentMenu = MAX_MENU - 1;
	}
	if (input->GetKey(VK_SPACE).pressed)
	{
		SceneManager* sceneMgr = SceneManager::Instance();
		if (m_CurrentMenu == GAME_START)
			sceneMgr->LoadScene(new SceneGame);
		else if (m_CurrentMenu == GAME_EXIT)
			sceneMgr->SetExit();
		else
			Assert(0, L"Invalid menu");
	}
}

void SceneTitle::Render(Renderer* renderer)
{
	for (int i = 0; i < 19; ++i)
		renderer->DrawString(13, 10 + i, s_TitleScreen[i]);

	if (m_CurrentMenu == GAME_START)
	{
		renderer->Draw(13 + m_SelectCrd[0].X, m_SelectCrd[0].Y + 10, L'>');
		renderer->Draw(13 + m_SelectCrd[0].X + 1, m_SelectCrd[0].Y + 10, L'>');
		renderer->Draw(13 + m_SelectCrd[1].X, m_SelectCrd[1].Y + 10, L'<');
		renderer->Draw(13 + m_SelectCrd[1].X + 1, m_SelectCrd[1].Y + 10, L'<');
	}
	else if (m_CurrentMenu == GAME_EXIT)
	{
		renderer->Draw(13 + m_SelectCrd[2].X, m_SelectCrd[2].Y + 10, L'>');
		renderer->Draw(13 + m_SelectCrd[2].X + 1, m_SelectCrd[2].Y + 10, L'>');
		renderer->Draw(13 + m_SelectCrd[3].X, m_SelectCrd[3].Y + 10, L'<');
		renderer->Draw(13 + m_SelectCrd[3].X + 1, m_SelectCrd[3].Y + 10, L'<');
	}
	else
	{
		Assert(0, L"Invalid menu");
	}
}
