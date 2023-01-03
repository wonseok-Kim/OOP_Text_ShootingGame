#include "stdafx.h"

#include <locale.h>

#include "ShootingGame.h"
#include "SceneTitle.h"
#include "Sprite.h"

static void MakeSprite();

int wmain()
{
	MakeSprite();

	timeBeginPeriod(1);
	_wsetlocale(LC_ALL, L"");

	auto game = new ShootingGame(new SceneTitle);
	game->Run();

	delete game;
	timeEndPeriod(1);
	return 0;
}

static void MakeSprite()
{
	//Sprite player{ 5, 1 };
	//player.SetGlyph(0, 0, L'<');
	//player.SetGlyph(1, 0, L'-');
	//player.SetGlyph(2, 0, L'*');
	//player.SetGlyph(3, 0, L'-');
	//player.SetGlyph(4, 0, L'>');
	//player.Save(L"Resources/Sprite/player.sp");

	//Sprite enemy1{ 5, 1 };
	//enemy1.SetGlyph(0, 0, L'[');
	//enemy1.SetGlyph(1, 0, L'-');
	//enemy1.SetGlyph(2, 0, L'|');
	//enemy1.SetGlyph(3, 0, L'-');
	//enemy1.SetGlyph(4, 0, L']');
	//enemy1.Save(L"Resources/Sprite/enemy1.sp");

	//Sprite playerBullet{ 1, 1 };
	//playerBullet.SetGlyph(0, 0, L'.');
	//playerBullet.Save(L"Resources/Sprite/player_bullet.sp");

}

