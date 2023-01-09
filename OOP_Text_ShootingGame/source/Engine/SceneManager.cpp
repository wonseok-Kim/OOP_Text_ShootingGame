#include "stdafx.h"
#include "SceneManager.h"

#include "GlobalObjectManager.h"
#include "Input.h"
#include "ObjectBase.h"
#include "Renderer.h"

SceneManager::~SceneManager()
{
	delete m_CurrentScene;
	delete m_NextScene;
}

bool SceneManager::Run(DWORD gameFrames, Renderer* rendererOrNull)
{
	if (m_IsExit)
		return false;

	if (m_NextScene)
	{
		delete m_CurrentScene;
		m_CurrentScene = m_NextScene;
		m_NextScene = nullptr;
	}

	GlobalObjectManager* globalObjectManager = GlobalObjectManager::Instance();

	Input::Instance()->Handle();

	m_CurrentScene->Update();
	m_CurrentScene->m_ObjectManager.Update();
	m_CurrentScene->m_FramesCount++;

	globalObjectManager->Update();
	// TODO: 글로벌에 대해서도 처리해주기

	if (rendererOrNull)
	{
		m_CurrentScene->Render(rendererOrNull);
		m_CurrentScene->m_ObjectManager.Render(rendererOrNull);

		globalObjectManager->Render(rendererOrNull);
		// TODO: 글로벌에 대해서도 처리해주기

		rendererOrNull->Flip();
	}

	return true;
}
