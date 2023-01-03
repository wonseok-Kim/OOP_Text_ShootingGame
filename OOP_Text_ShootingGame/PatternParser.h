#pragma once

#include "Parser.h"
#include "BulletInfo.h"

struct Pattern;

class PatternParser : public Parser
{
public:
    PatternParser() = default;
    ~PatternParser() = default;
        
    bool InitByFilename(const WCHAR* filename)
    {
        wcscpy_s(m_PatternFilename, MAX_PATH, filename);

        return Parser::InitByFilename(filename);
    }

    virtual bool Run() override;

private:
    bool ParsePattern(SubString texts, Pattern* p);

private:
    WCHAR m_PatternFilename[MAX_PATH];
};