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
    int duration;  // duration ������ ���� �� ������ ������.

    // �̵� ����
    COORD moveTo;
    DWORD moveInterval; // �� ������ �������� MoveTo * speed ��ŭ �̵�

    // ���� ����
    ShotInfo* shotInfo;
    DWORD shotInterval; // �� ������ �������� ����
    int shotChance;     // (0 ~ 100) ���� Ȯ��
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