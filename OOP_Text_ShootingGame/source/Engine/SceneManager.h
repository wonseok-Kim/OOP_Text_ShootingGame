#pragma once

#include "GlobalObjectManager.h"
#include "Input.h"
#include "Renderer.h"
#include "SceneBase.h"

class SceneManager
{
public:
	static SceneManager* Instance()
	{
		static SceneManager inst;
		return &inst;
	}

	~SceneManager()
	{
		delete m_CurrentScene;
		delete m_NextScene;
	}

	bool Run(DWORD gameFrames, Renderer* rendererOrNull)
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
		globalObjectManager->Update(gameFrames);

		if (rendererOrNull)
		{
			m_CurrentScene->Render(rendererOrNull);
			globalObjectManager->Render(rendererOrNull);

			rendererOrNull->Output();
			rendererOrNull->ClearBuffer();
		}

		return true;
	}

	void LoadScene(SceneBase* nextScene)
	{
		// TODO: ���߿� �̷� ��찡 �ִ��� Ȯ���ϱ�
		Assert(m_NextScene == nullptr, L"(�׽�Ʈ ��) �̹� Scene�� �ٲ�µ� �� �ٲٷ��� �õ��ϴ� ��찡 ������?");

		m_NextScene = nextScene;
	}

	void SetExit()
	{
		m_IsExit = true;
	}

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

private:
	SceneManager() = default;

private:
	SceneBase* m_CurrentScene = nullptr;
	SceneBase* m_NextScene = nullptr;
	bool m_IsExit = false;
};

