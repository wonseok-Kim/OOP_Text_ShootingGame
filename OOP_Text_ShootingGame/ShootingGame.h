#pragma once

#include "GameBase.h"

class ShootingGame : public GameBase
{
public:
	ShootingGame(SceneBase* firstScene)
		: GameBase(firstScene)
	{

	}

	virtual ~ShootingGame() override
	{}
};
