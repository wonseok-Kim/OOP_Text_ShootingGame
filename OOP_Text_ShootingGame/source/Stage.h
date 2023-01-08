#pragma once

#include "PatternList.h"

class Sprite;

struct ShotInfo
{
    int shotCount;
    Sprite* sprite;
    COORD startCoord[8];
    COORD dir[8];

    bool Load(const WCHAR* filename);
};

struct PlayerInfo
{
    Sprite* sprite;
    COORD startCoord;
    ShotInfo* shotInfo;
};

struct Pattern
{
    int duration;  // duration 프레임 동안 이 패턴을 실행함.

    // 이동 관련
    COORD moveTo;
    DWORD moveInterval; // 이 프레임 간격으로 MoveTo * speed 만큼 이동

    // 공격 관련
    ShotInfo* shotInfo;
    DWORD shotInterval; // 이 프레임 간격으로 공격
    int shotChance;     // (0 ~ 100) 공격 확률
};

struct EnemyInfo
{
    Sprite* sprite;
    COORD startCoord;
    BOOL bLoopPatterns;
    PatternList* pPatternList;    
    int hp;
};

struct Stage
{
    PlayerInfo player;
    EnemyInfo* enemies;
    int enemiesCount;
};