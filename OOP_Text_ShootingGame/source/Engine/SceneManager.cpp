#include "stdafx.h"
#include "SceneManager.h"

#include "Input.h"
#include "ObjectBase.h"
#include "Renderer.h"

SceneManager::~SceneManager()
{
	delete m_CurrentScene;
	delete m_NextScene;
}

bool SceneManager::Run(Renderer* rendererOrNull)
{
	if (m_IsExit)
		return false;

	if (m_NextScene)
	{
		SceneBase* prevScene = m_CurrentScene;
		m_CurrentScene = m_NextScene;
		m_NextScene = nullptr;
		if (!m_CurrentScene->OnInit())
			return false;
		delete prevScene;
	}

	Input::Instance()->Handle();

	m_CurrentScene->Update();
	m_CurrentScene->m_ObjectManager.Update(m_CurrentScene->m_FramesCount);
	m_CurrentScene->m_FramesCount++;


	if (rendererOrNull)
	{
		m_CurrentScene->Render(rendererOrNull);
		m_CurrentScene->m_ObjectManager.Render(rendererOrNull);

		rendererOrNull->Flip();
	}

	return true;
}

void SceneManager::LoadScene(SceneBase* nextScene)
{
	delete m_NextScene;

	m_NextScene = nextScene;
}
