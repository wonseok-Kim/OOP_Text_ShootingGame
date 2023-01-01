#include "stdafx.h"
#include "GameBase.h"

#include "Renderer.h"
#include "SceneManager.h"

GameBase::GameBase(SceneBase* firstScene, int width, int height)
{
	if (firstScene == nullptr)
	{
		PrintError("firstScene must not be null.");
		abort();
	}

	SceneManager::Instance().LoadScene(firstScene);

	m_Renderer = new Renderer(width, height);
}

GameBase::~GameBase()
{
	delete m_Renderer;
}

void GameBase::Run()
{
	auto& sceneManager = SceneManager::Instance();

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	LARGE_INTEGER t1;
	QueryPerformanceCounter(&t1);
	LARGE_INTEGER t2;
	QueryPerformanceCounter(&t2);

	while (true)
	{
		QueryPerformanceCounter(&t2);
		LONGLONG elapsed = t2.QuadPart - t1.QuadPart;
		t1 = t2;
		float fElapsedTime = (float)elapsed / freq.QuadPart;

		sceneManager.Run(m_Renderer);

		wchar_t s[256];
		swprintf_s(s, 256, L"FPS: %3.2f", 1.0f / fElapsedTime);
		SetConsoleTitleW(s);
	}
}
