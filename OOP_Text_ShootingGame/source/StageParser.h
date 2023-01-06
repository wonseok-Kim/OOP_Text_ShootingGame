#pragma once

#include "Parser.h"

struct Stage;
struct PlayerInfo;
struct EnemyInfo;

class StageParser : public Parser
{
public:
    StageParser() = default;
    ~StageParser() = default;

    bool Init(const WCHAR* filename)
    {
        return Parser::InitByFilename(filename);
    }

    bool Run(Stage* out_Stage);

private:
    bool ParsePlayerInfo(const SubString& texts, PlayerInfo* out_pPlayerInfo);
    bool ParseEnemyInfo(const SubString& texts, EnemyInfo* out_pEnemyInfo);
};


