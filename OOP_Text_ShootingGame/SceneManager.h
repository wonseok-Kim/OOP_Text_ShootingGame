#pragma once

#include "GlobalObjectManager.h"
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

	void Run()
	{
		if (m_NextScene)
		{
			delete m_CurrentScene;
			m_CurrentScene = m_NextScene;
			m_NextScene = nullptr;
		}

		Assert(m_CurrentScene, "GameBase �����ڿ��� ���� �� �ް� LoadScene()���� �־���");

		auto& globalObjectManager = GlobalObjectManager::Instance();

		m_CurrentScene->Update();
		globalObjectManager.Update();

		m_CurrentScene->Render();
		globalObjectManager.Render();
	}

	void LoadScene(SceneBase* nextScene)
	{
		// TODO: ���߿� �̷� ��찡 �ִ��� Ȯ���ϱ�
		Assert(m_NextScene == nullptr, "(�׽�Ʈ ��) �̹� Scene�� �ٲ�µ� �� �ٲٷ��� �õ��ϴ� ��찡 ������?");

		m_NextScene = nextScene;
	}

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

private:
	SceneManager() {}

private:
	SceneBase* m_CurrentScene = nullptr;
	SceneBase* m_NextScene = nullptr;
};

