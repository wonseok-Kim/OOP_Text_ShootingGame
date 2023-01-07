#include "stdafx.h"
#include "PatternParser.h"

#include "ResourceManager.h"

bool PatternParser::ParsePatternsAndAddPatternsToResMgr()
{
    ResourceManager* resMgr = ResourceManager::Instance();

    // This method is a friend with ResourceManager.
    int& listsCount = resMgr->m_PatternListsCount;
    PatternList& patternList = resMgr->m_PatternLists[listsCount];
    WCHAR*& filename = resMgr->m_PatternFilenames[listsCount];
    listsCount++;

    int patternsCount;
    GetNumberLiteral(&patternsCount);

    for (int i = 0; i < patternsCount; ++i)
    {
        SubString block;
        if (!GetBlock(&block))
            return false;

        Pattern* p = new Pattern;
        if (!ParsePattern(block, p))
        {
            delete p;
            return false;
        }
        patternList.push_back(p);
    }

    size_t size = wcslen(m_Filename) + 1;
    filename = new WCHAR[size];
    wcscpy_s(filename, size, m_Filename);

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
        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        SubString Identifier;
        GetIdentifier(&Identifier);

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
            return false;
        ++m_Current;

        int i;
        for (i = 0; i < identifiersLength; ++i)
            if (Identifier.equal(identifiers[i]))
                break;

        ShotInfo* pShotInfo;
        WCHAR path[MAX_PATH];
        int temp;
        switch (i)
        {
        case 0:
            if (!GetNumberLiteral(&out_Pattern->duration))
                return false;
            break;

        case 1:
            if (!GetCoord(&out_Pattern->moveTo))
                return false;
            break;

        case 2:
            if (!GetNumberLiteral(&temp))
                return false;

            out_Pattern->moveInterval = (DWORD)temp;
            break;

        case 3:
            if (!GetStringLiteral(path, MAX_PATH))
                return false;

            pShotInfo = ResourceManager::Instance()->GetShotInfo(path);
            if (!pShotInfo)
                return false;

            out_Pattern->shotInfo = pShotInfo;
            break;

        case 4:
            if (!GetNumberLiteral(&temp))
                return false;

            out_Pattern->shotInterval = (DWORD)temp;
            break;

        case 5:
            if (!GetNumberLiteral(&out_Pattern->shotChance))
                return false;
            break;

        default:
            *Identifier.end = '\0';
            PrintError(L"존재하지 않는 필드 명 '%hs'", Identifier.begin);
            return false;
        }
    }

    m_Current++;
    return true;
}
