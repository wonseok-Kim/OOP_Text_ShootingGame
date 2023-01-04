#pragma once

#include "Parser.h"
#include "Stage.h"

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

    virtual bool Run() override;

private:
    bool ParsePattern(SubString texts, Pattern* p);
};