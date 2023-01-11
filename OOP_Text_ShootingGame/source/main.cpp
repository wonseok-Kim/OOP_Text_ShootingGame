#include "stdafx.h"

#include <locale.h>

#include "Engine/Sprite.h"

#include "Game/ShootingGame.h"
#include "Game/SceneTitle.h"

static void MakeSprite();

int wmain()
{
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

    //Sprite hpUP{ 3,1 };
    //hpUP.SetGlyph(0, 0, L'<');
    //hpUP.SetGlyph(1, 0, L'H');
    //hpUP.SetGlyph(2, 0, L'>');
    //hpUP.Save(L"Resources/Item/hp_up.sp");

    //Sprite doubleShot{ 3, 1 };
    //doubleShot.SetGlyph(0, 0, L'<');
    //doubleShot.SetGlyph(1, 0, L'D');
    //doubleShot.SetGlyph(2, 0, L'>');
    //doubleShot.Save(L"Resources/Item/double_shot.sp");

    //const WCHAR* leftHand[] = {
    //    L"         ",
    //    L"         ",
    //    L"=========",
    //    L"||       ",
    //    L"||       ",
    //    L"||       ",
    //    L"||-------"
    //};

    //Sprite bossLeft{ 9, 7 };
    //for (int y = 0; y < 7; ++y)
    //    for (int x = 0; x < 9; ++x)
    //        bossLeft.SetGlyph(x, y, leftHand[y][x]);
    //bossLeft.Save(L"Resources/Sprite/boss_left.sp");

    //const WCHAR* body[] = {
    //    L"     XXX     ",
    //    L"    /---\\    ",
    //    L"---/     \\---",
    //    L"  /       \\  ",
    //    L" /         \\ ",
    //    L"/-----------\\",
    //    L"=  ||  ||   ="
    //};

    //Sprite boss{ 13, 7 };
    //for (int y = 0; y < 7; ++y)
    //    for (int x = 0; x < 13; ++x)
    //        boss.SetGlyph(x, y, body[y][x]);
    //boss.Save(L"Resources/Sprite/boss.sp");


    //const WCHAR* rigthHand[] = {
    //    L"         ",
    //    L"         ",
    //    L"=========",
    //    L"       ||",
    //    L"       ||",
    //    L"       ||",
    //    L"-------||"
    //};

    //Sprite bossRight{ 9, 7 };
    //for (int y = 0; y < 7; ++y)
    //    for (int x = 0; x < 9; ++x)
    //        bossRight.SetGlyph(x, y, rigthHand[y][x]);
    //bossRight.Save(L"Resources/Sprite/boss_right.sp");
}

