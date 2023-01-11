#include "stdafx.h"
#include "PatternParser.h"

#include "ResourceManager.h"

bool PatternParser::ParsePatterns(PatternList* out_pPatternList)
{
    SkipWhiteSpace();
    int patternsCount;
    if (!GetNumberLiteral(&patternsCount))
    {
        PrintError(L"Pattern ������ ���� ù��°�� ������ ������ ���ߵ˴ϴ�.");
        return false;
    }

    for (int i = 0; i < patternsCount; ++i)
    {
        SkipWhiteSpace();
        SubString block;
        if (!GetBlock(&block))
        {
            PrintError(L"Pattern�� {}�� ���ξ��մϴ�.");
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
            PrintError(L"�ĺ��� : �� �̷� �������� ��������.");
            return false;
        }

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
        {
            *Identifier.end = '\0';
            PrintError(L"'%hs'���⿡ �ݷ� ������.", Identifier.begin);
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
                PrintError(L"duration�� ���� ���ڿ��� �մϴ�.");
                return false;
            }
            break;

        case 1:
            SkipWhiteSpace();
            if (!GetCoord(&out_Pattern->moveTo))
            {
                PrintError(L"MoveTo�� ���� (x, y) ������ ��ǥ���� �մϴ�.");
                return false;
            }
            break;

        case 2:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"moveInterval�� ���� ���ڿ��� �մϴ�.");
                return false;
            }

            out_Pattern->moveInterval = (DWORD)temp;
            break;

        case 3:
            SkipWhiteSpace();
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo�� ���� \"ShotInfo�� ���� ���\"�� �Է��ؾ� ��.");
                return false;
            }

            pShotInfo = ResourceManager::Instance()->GetShotInfo(path);
            if (!pShotInfo)
            {
                PrintError(L"'%s'������ ���� ������ ResourceManager�� ��� �ȵ�", path);
                return false;
            }

            out_Pattern->shotInfo = pShotInfo;
            break;

        case 4:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"shotInterval�� ���� ���ڿ��� �մϴ�.");
                return false;
            }

            out_Pattern->shotInterval = (DWORD)temp;
            break;

        case 5:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&out_Pattern->shotChance))
            {
                PrintError(L"shotChance�� ���� ���ڿ��� �մϴ�.");
                return false;
            }
            break;

        default:
            *Identifier.end = '\0';
            PrintError(L"�������� �ʴ� �ʵ� �� '%hs'", Identifier.begin);
            return false;
        }
    }

    m_Current++;
    return true;
}
