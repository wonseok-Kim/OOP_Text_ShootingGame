#pragma once

#include "GlobalObjectManager.h"
#include "Input.h"
#include "Renderer.h"
#include "SceneBase.h"

class SceneManager
{
public:
	static SceneManager& Instance()
	{
		static SceneManager inst;
		return inst;
	}

	~SceneManager()
	{
		delete m_CurrentScene;
		delete m_NextScene;
	}

	void Run(Renderer* rendererOrNull)
	{
		if (m_NextScene)
		{
			delete m_CurrentScene;
			m_CurrentScene = m_NextScene;
			m_NextScene = nullptr;
		}

		Assert(m_CurrentScene, L"GameBase 생성자에서 시작 씬 받고 LoadScene()으로 넣어줌");

		auto& globalObjectManager = GlobalObjectManager::Instance();

		Input::Instance().Handle();

		m_CurrentScene->Update();
		globalObjectManager.Update();

		if (rendererOrNull)
		{
			m_CurrentScene->Render(rendererOrNull);
			globalObjectManager.Render(rendererOrNull);

			rendererOrNull->Output();
			rendererOrNull->ClearBuffer();
		}
	}

	void LoadScene(SceneBase* nextScene)
	{
		// TODO: 나중에 이런 경우가 있는지 확인하기
		Assert(m_NextScene == nullptr, L"(테스트 용) 이미 Scene을 바꿨는데 또 바꾸려고 시도하는 경우가 있을까?");

		m_NextScene = nextScene;
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
};

