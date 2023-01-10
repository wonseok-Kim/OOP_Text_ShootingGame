#include "stdafx.h"

#include <locale.h>

#include "Engine/Sprite.h"

#include "Game/ShootingGame.h"
#include "Game/SceneTitle.h"

#ifdef _DEBUG
#include "Engine/GlobalObjectManager.h"
#include "Engine/SceneManager.h"
#include "ResourceManager.h"
#endif

static void MakeSprite();

int wmain()
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    MakeSprite();

    timeBeginPeriod(1);
    _wsetlocale(LC_ALL, L"");

    auto game = new ShootingGame(new SceneTitle);
    if (game->Init())
    {
        game->Run();
    }

    delete game;
    timeEndPeriod(1);

#ifdef _DEBUG
    GlobalObjectManager::Instance()->~GlobalObjectManager();
    SceneManager::Instance()->~SceneManager();
    ResourceManager::Instance()->~ResourceManager();
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    ExitProcess(0);
#endif

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

    //Sprite enemy2{ 6, 1 };
    //enemy2.SetGlyph(0, 0, L'[');
    //enemy2.SetGlyph(1, 0, L'W');
    //enemy2.SetGlyph(2, 0, L'v');
    //enemy2.SetGlyph(3, 0, L'v');
    //enemy2.SetGlyph(4, 0, L'W');
    //enemy2.SetGlyph(5, 0, L']');
    //enemy2.Save(L"Resources/Sprite/enemy2.sp");

    //Sprite enemy2Bullet{ 1, 1 };
    //enemy2Bullet.SetGlyph(0, 0, L'W');
    //enemy2Bullet.Save(L"Resources/Sprite/enemy2_bullet.sp");

    //Sprite playerBullet{ 1, 1 };
    //playerBullet.SetGlyph(0, 0, L'*');
    //playerBullet.Save(L"Resources/Sprite/default_bullet.sp");
}

