#include "stdafx.h"
#include "StageParser.h"

#include "ResourceManager.h"
#include "Stage.h"

bool StageParser::Run(Stage* out_Stage)
{
    Assert(out_Stage, L"out parameter must not be null");

    while (*m_Current != '\0')
    {
        switch (GetCharType(*m_Current))
        {
        case CharType::Whitespace:
            SkipWhiteSpace();
            break;

        case CharType::Identifier:
            if (strncmp(m_Current, "Player", 6) == 0)
            {
                m_Current += 6;
                SkipWhiteSpace();

                SubString block;
                if (!GetBlock(&block))
                    return false;

                ParsePlayerInfo(block, &out_Stage->player);
            }
            else if (strncmp(m_Current, "Enemy", 5) == 0)
            {
                m_Current += 5;
                SkipWhiteSpace();

                GetNumberLiteral(&out_Stage->enemiesCount);
                SkipWhiteSpace();

                out_Stage->enemies = new EnemyInfo[out_Stage->enemiesCount];

                for (int i = 0; i < out_Stage->enemiesCount; ++i)
                {
                    SubString block;
                    if (!GetBlock(&block))
                        return false;

                    ParseEnemyInfo(block, &out_Stage->enemies[i]);
                }
            }
            else
            {
                PrintError(L"肋给等 巩过");
                return false;
            }
            break;

        default:
            PrintError(L"肋给等 巩过");
            return false;
        }
    }

    return true;
}

bool StageParser::ParsePlayerInfo(const SubString& texts, PlayerInfo* out_pPlayerInfo)
{
    const char* keys[] = { "sprite", "coord" };
    const CharType types[] = { CharType::StringLiteral, CharType::OpenParenthesis };

    m_Current = texts.begin;
    while (true)
    {
        SubString key;
        SkipWhiteSpace();

        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        if (GetCharType(*m_Current) != CharType::Identifier)
            return false;

        GetIdentifier(&key);
        SkipWhiteSpace();

        int i;
        for (i = 0; i < 2; ++i)
        {
            if (key.equal(keys[i]))
                break;
        }

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
            return false;

        m_Current++;
        SkipWhiteSpace();

        switch (i)
        {
        case 0:
        {
            if (GetCharType(*m_Current) != types[0])
                return false;

            WCHAR path[MAX_PATH];
            GetStringLiteral(path, MAX_PATH);

            Sprite* sprite = ResourceManager::Instance()->GetSprite(path);
            if (!sprite)
                return false;
            out_pPlayerInfo->sprite = sprite;
            break;
        }
        case 1:
        {
            COORD coord;
            GetCoord(&coord);
            out_pPlayerInfo->startCoord = coord;
            break;
        }
        default:
            PrintError(L"肋给等 巩过");
            return false;
        }
    }
    m_Current++;

    return true;
}

bool StageParser::ParseEnemyInfo(const SubString& texts, EnemyInfo* out_pEnemyInfo)
{
    const char* identifiers[] = { "sprite", "coord", "loopPattern", "patterns" };
    constexpr int identifiersLength = sizeof(identifiers) / sizeof(char*);

    m_Current = texts.begin;

    while (true)
    {
        SubString key;

        SkipWhiteSpace();
        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        if (GetCharType(*m_Current) != CharType::Identifier)
            return false;

        GetIdentifier(&key);
        SkipWhiteSpace();

        int i;
        for (i = 0; i < identifiersLength; ++i)
        {
            if (key.equal(identifiers[i]))
                break;
        }

        if (GetCharType(*m_Current) != CharType::Colon)
            return false;

        m_Current++;
        SkipWhiteSpace();

        WCHAR path[MAX_PATH];
        switch (i)
        {
        case 0:
        {
            if (GetCharType(*m_Current) != CharType::StringLiteral)
                return false;

            GetStringLiteral(path, MAX_PATH);

            Sprite* sprite = ResourceManager::Instance()->GetSprite(path);
            if (!sprite)
                return false;
            out_pEnemyInfo->sprite = sprite;
            break;
        }
        case 1:
        {
            if (GetCharType(*m_Current) != CharType::OpenParenthesis)
                return false;

            COORD coord{};
            GetCoord(&coord);
            out_pEnemyInfo->startCoord = coord;
            break;
        }
        case 2:
        {
            if (GetCharType(*m_Current) != CharType::NumberLiteral)
                return false;

            int temp;
            GetNumberLiteral(&temp);
            out_pEnemyInfo->bLoopPatterns = temp;
            break;
        }
        case 3:
        {
            if (GetCharType(*m_Current) != CharType::StringLiteral)
                return false;

            GetStringLiteral(path, MAX_PATH);
            PatternList* pPatternList = ResourceManager::Instance()->GetPatternList(path);
            out_pEnemyInfo->pPatternList = pPatternList;
            break;
        }
        default:
            PrintError(L"肋给等 巩过");
            return false;
        }
    }

    m_Current++;
    return true;
}
