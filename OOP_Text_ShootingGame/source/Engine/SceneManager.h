#pragma once

class Renderer;
class SceneBase;

class SceneManager
{
public:
	static SceneManager* Instance()
	{
		static SceneManager inst;
		return &inst;
	}

	~SceneManager();

	bool Run(DWORD gameFrames, Renderer* rendererOrNull);

	void LoadScene(SceneBase* nextScene)
	{
		// TODO: 나중에 이런 경우가 있는지 확인하기
		Assert(m_NextScene == nullptr, L"(테스트 용) 이미 Scene을 바꿨는데 또 바꾸려고 시도하는 경우가 있을까?");

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

