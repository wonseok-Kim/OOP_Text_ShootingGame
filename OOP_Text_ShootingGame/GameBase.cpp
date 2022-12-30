#include "stdafx.h"
#include "GameBase.h"

#include "SceneManager.h"

GameBase::GameBase(SceneBase* firstScene)
{
	if (firstScene == nullptr)
	{
		PrintError("firstScene must not be null.");
		abort();
	}

	SceneManager::Instance().LoadScene(firstScene);
}

GameBase::~GameBase()
{
}

void GameBase::Run()
{
	auto& sceneManager = SceneManager::Instance();

	while (true)
	{
		sceneManager.Run();
	}
}
