#pragma once

#include "Parser.h"

struct Stage;
struct PlayerInfo;
struct EnemyInfo;
struct ItemInfo;

class StageParser : public Parser
{
public:
    StageParser() = default;
    ~StageParser() = default;

    bool ParseStage(Stage* out_Stage);

private:
    bool ParsePlayerInfo(const SubString& texts, PlayerInfo* out_pPlayerInfo);
    bool ParseEnemyInfo(const SubString& texts, EnemyInfo* out_pEnemyInfo);
    bool ParseItemInfo(const SubString& texts, ItemInfo* out_pItemInfo);
};


