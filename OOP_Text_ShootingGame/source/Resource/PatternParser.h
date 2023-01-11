#pragma once

#include "Parser.h"

struct Pattern;

class PatternParser : public Parser
{
public:
    PatternParser() = default;
    ~PatternParser() = default;

    bool ParsePatternsAndAddPatternsToResMgr();

private:
    bool ParsePattern(const SubString& block, Pattern* p);
};