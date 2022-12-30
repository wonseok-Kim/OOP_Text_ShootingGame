#include "stdafx.h"

#include <locale.h>

#include "GameBase.h"
#include "SceneTitle.h"

enum ObjectType
{
	Player,
	Enemy,

};

class ShootingGame : public GameBase
{
public:
	ShootingGame(SceneBase* firstScene)
		: GameBase(firstScene)
	{ }

	virtual ~ShootingGame() override 
	{ }
};

int wmain()
{
	timeBeginPeriod(1);
	_wsetlocale(LC_ALL, L"");
	
	auto game = new ShootingGame(new SceneTitle);
	game->Run();

	delete game;
	timeEndPeriod(1);
	return 0;
}