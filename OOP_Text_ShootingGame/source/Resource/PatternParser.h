#pragma once

#include "Parser.h"
#include "PatternList.h"

struct Pattern;

class PatternParser : public Parser
{
public:
    PatternParser() = default;
    ~PatternParser() = default;

    bool ParsePatterns(PatternList* out_pPatternList);

private:
    bool ParsePattern(const SubString& block, Pattern* p);
};