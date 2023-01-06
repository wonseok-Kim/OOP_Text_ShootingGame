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

    bool Run();

private:
    bool ParsePattern(SubString texts, Pattern* p);
};