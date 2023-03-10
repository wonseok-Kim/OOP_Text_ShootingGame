#include "stdafx.h"
#include "GameBase.h"

#include "Renderer.h"
#include "SceneManager.h"

GameBase::GameBase(SceneBase* firstScene, int width, int height)
{
	if (firstScene == nullptr)
	{
		PrintError(L"firstScene must not be null.");
		abort();
	}

	SceneManager::Instance()->LoadScene(firstScene);

	m_Renderer = new Renderer(width, height);
}

GameBase::~GameBase()
{
	delete m_Renderer;
}

void GameBase::Run()
{
	SceneManager* sceneManager = SceneManager::Instance();

	constexpr DWORD framesPerSecond = 50;
	constexpr DWORD ticksPerFrame = 1000 / framesPerSecond;

	DWORD standardTick = timeGetTime(); // 게임의 기준이 되는 시간
	DWORD previousTick = standardTick;
	DWORD elapsedTick = 0;
	DWORD errorTick = 0;  // 오차 누적
	DWORD frameCount = 0;
	DWORD incrementsOf1000ms = 1000;

	bool bGameLoop = true;

	while (bGameLoop)
	{
		DWORD nowTick = timeGetTime();
		elapsedTick += nowTick - previousTick;
		previousTick = nowTick;

		if (elapsedTick >= incrementsOf1000ms)
		{
			wchar_t s[100];
			swprintf_s(s, 100, L"FPS: %3.2f, frameCount: %u errorTick: %u nowTick: %u\n",
				frameCount / (elapsedTick / 1000.f), frameCount, errorTick, elapsedTick);
			// OutputDebugStringW(s);
			SetConsoleTitleW(s);

			incrementsOf1000ms += 1000;
		}

		if (errorTick >= ticksPerFrame)
		{
			bGameLoop = sceneManager->Run(nullptr); // 렌더링 건너띄기

			errorTick -= ticksPerFrame;
		}
		else
		{
			bGameLoop = sceneManager->Run(m_Renderer);

			//Sleep(rand() % 50); 
		}

		standardTick += ticksPerFrame;
		nowTick = timeGetTime();
		if (nowTick < standardTick)
		{
			Sleep(standardTick - nowTick);
		}
		else
		{
			errorTick += nowTick - standardTick;
		}

		frameCount++;
	}
}
