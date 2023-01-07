#pragma once

#include "Parser.h"

struct Pattern;

class PatternParser : public Parser
{
public:
    PatternParser() = default;
    ~PatternParser() = default;
        
    bool InitByFilename(const WCHAR* filename)
    {
        return Parser::InitByFilename(filename);
    }

    bool ParsePatternsAndAddPatternsToResMgr();

private:
    bool ParsePattern(SubString texts, Pattern* p);
};