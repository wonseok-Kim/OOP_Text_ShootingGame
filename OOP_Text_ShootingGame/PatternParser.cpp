#include "stdafx.h"
#include "PatternParser.h"

#include "ResourceManager.h"

bool PatternParser::Run()
{
    int* pCount = &(ResourceManager::Instance().m_PatternListsCount);

    while (*m_Current != '\0')
    {
        PatternList* pPatternList = &(ResourceManager::Instance().m_PatternLists[*pCount]);
        WCHAR** pPatternFilename = &(ResourceManager::Instance().m_PatternFilenames[*pCount]);

        size_t size = wcslen(m_PatternFilename) + 1;
        (*pPatternFilename) = new WCHAR[size];
        wcscpy_s(*pPatternFilename, size, m_PatternFilename);

        int count;
        GetNumberLiteral(&count);

        for (int i = 0; i < count; ++i)
        {
            SubString block;
            if (!GetBlock(&block))
                return false;
                        
            Pattern* p = new Pattern;
            ParsePattern(block, p);
            pPatternList->push_back(p);
        }

        ++(*pCount);        
    }

    return true;
}

bool PatternParser::ParsePattern(SubString texts, Pattern* out_Pattern)
{
    const char* identifiers[6] = { "duration", "moveTo", "moveInterval", "shotInfo", "shotInterval", "shotChance" };
    size_t identifiersLength = sizeof(identifiers) / sizeof(char*);

    m_Current = texts.begin;

    while (true)
    {
        SkipWhiteSpace();
        if (m_Current == texts.end)
            break;

        SubString key;
        GetIdentifier(&key);

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
            return false;
        ++m_Current;

        int i;
        for (i = 0; i < identifiersLength; ++i)
            if (key.equal(identifiers[i]))
                break;

        switch (i)
        {
        case 0:
        {
            if (GetCharType(*m_Current) != CharType::NumberLiteral)
            {
                return false;
            }
            GetNumberLiteral(&out_Pattern->duration);
            break;
        }
        case 1:
        {
            if (GetCharType(*m_Current) != CharType::OpenParenthesis)
            {
                return false;
            }
            GetCoord(&out_Pattern->moveTo);
            break;
        }
        case 2:
        {
            if (GetCharType(*m_Current) != CharType::NumberLiteral)
            {
                return false;
            }
            int temp;
            GetNumberLiteral(&temp);
            out_Pattern->moveInterval = (DWORD)temp;
            break;
        }
        case 3:
        {
            if (GetCharType(*m_Current) != CharType::StringLiteral)
            {
                return false;
            }
            WCHAR path[MAX_PATH];
            GetStringLiteral(path, MAX_PATH);

            ShotInfo* pShotInfo = ResourceManager::Instance().GetShotInfo(path);
            if (!pShotInfo)
                return false;

            out_Pattern->shotInfo = pShotInfo;
            break;
        }
        case 4:
        {
            if (GetCharType(*m_Current) != CharType::NumberLiteral)
            {
                return false;
            }
            int temp;
            GetNumberLiteral(&temp);
            out_Pattern->shotInterval = (DWORD)temp;
            break;
        }
        case 5:
        {
            if (GetCharType(*m_Current) != CharType::NumberLiteral)
            {
                return false;
            }
            GetNumberLiteral(&out_Pattern->shotChance);
            break;
        }
        default:
            return false;
        }
    }

    return true;
}
