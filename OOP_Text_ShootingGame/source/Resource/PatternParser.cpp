#include "stdafx.h"
#include "PatternParser.h"

#include "ResourceManager.h"

bool PatternParser::ParsePatterns(PatternList* out_pPatternList)
{
    SkipWhiteSpace();
    int patternsCount;
    if (!GetNumberLiteral(&patternsCount))
    {
        PrintError(L"Pattern 파일의 제일 첫번째는 패턴의 개수가 들어가야됩니다.");
        return false;
    }

    for (int i = 0; i < patternsCount; ++i)
    {
        SkipWhiteSpace();
        SubString block;
        if (!GetBlock(&block))
        {
            PrintError(L"Pattern을 {}로 감싸야합니다.");
            return false;
        }

        Pattern* p = new Pattern; // delete in ReousrceManager::~ResourceManager()
        if (!ParsePattern(block, p))
        {
            delete p;
            return false;
        }
        out_pPatternList->push_back(p);
    }

    return true;
}

bool PatternParser::ParsePattern(const SubString& block, Pattern* out_Pattern)
{
    const char* identifiers[6] = { "duration", "moveTo", "moveInterval", "shotInfo", "shotInterval", "shotChance" };
    int identifiersLength = sizeof(identifiers) / sizeof(char*);

    m_Current = block.begin + 1;

    while (true)
    {
        SkipWhiteSpace();
        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        SkipWhiteSpace();
        SubString Identifier;
        if (!GetIdentifier(&Identifier))
        {
            PrintError(L"식별자 : 값 이런 형식으로 적으세요.");
            return false;
        }

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
        {
            *Identifier.end = '\0';
            PrintError(L"'%hs'여기에 콜론 빼먹음.", Identifier.begin);
            return false;
        }
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
            SkipWhiteSpace();
            if (!GetNumberLiteral(&out_Pattern->duration))
            {
                PrintError(L"duration의 값을 숫자여야 합니다.");
                return false;
            }
            break;

        case 1:
            SkipWhiteSpace();
            if (!GetCoord(&out_Pattern->moveTo))
            {
                PrintError(L"MoveTo의 값을 (x, y) 형식의 좌표여야 합니다.");
                return false;
            }
            break;

        case 2:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"moveInterval의 값은 숫자여야 합니다.");
                return false;
            }

            out_Pattern->moveInterval = (DWORD)temp;
            break;

        case 3:
            SkipWhiteSpace();
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo의 값은 \"ShotInfo의 파일 경로\"로 입력해야 됨.");
                return false;
            }

            pShotInfo = ResourceManager::Instance()->GetShotInfo(path);
            if (!pShotInfo)
            {
                PrintError(L"'%s'다음과 같은 파일은 ResourceManager에 등록 안됨", path);
                return false;
            }

            out_Pattern->shotInfo = pShotInfo;
            break;

        case 4:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"shotInterval의 값을 숫자여야 합니다.");
                return false;
            }

            out_Pattern->shotInterval = (DWORD)temp;
            break;

        case 5:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&out_Pattern->shotChance))
            {
                PrintError(L"shotChance의 값을 숫자여야 합니다.");
                return false;
            }
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
