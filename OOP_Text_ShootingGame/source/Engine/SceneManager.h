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

