#pragma once

#include "GameBase.h"

#include "ResourceLoader.h"
#include "GameDefine.h"

class ShootingGame : public GameBase
{
public:
	ShootingGame(SceneBase* firstScene)
		: GameBase(firstScene, GAME_WIDTH, GAME_HEIGHT)
	{
		ResourceLoader::Load();
	}

	virtual ~ShootingGame() override
	{}
};
