#pragma once

#include "Engine/GameBase.h"

#include "ResourceLoader.h"
#include "GameDefine.h"

class ShootingGame : public GameBase
{
public:
	ShootingGame(SceneBase* firstScene)
		: GameBase(firstScene, GAME_WIDTH, GAME_HEIGHT + 1)
	{
	}

	bool Init()
	{
		return ResourceLoader::Load();
	}

	virtual ~ShootingGame() override
	{}
};
