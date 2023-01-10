#include "stdafx.h"
#include "StageParser.h"

#include "ResourceManager.h"
#include "Infos.h"

bool StageParser::ParseStage(Stage* out_Stage)
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

                if (!ParsePlayerInfo(block, &out_Stage->player))
                {
                    return false;
                }
            }
            else if (strncmp(m_Current, "Enemy", 5) == 0)
            {
                m_Current += 5;

                SkipWhiteSpace();
                if (!GetNumberLiteral(&out_Stage->enemiesCount))
                    return false;
                
                // delete[] in ResourceManager::~ResourceManager().
                out_Stage->enemies = new EnemyInfo[out_Stage->enemiesCount];

                for (int i = 0; i < out_Stage->enemiesCount; ++i)
                {
                    SkipWhiteSpace();
                    SubString block;
                    if (!GetBlock(&block))
                    {
                        delete[] out_Stage->enemies;
                        return false;
                    }

                    if (!ParseEnemyInfo(block, &out_Stage->enemies[i]))
                    {
                        delete[] out_Stage->enemies;
                        return false;
                    }
                }
            }
           /* else if (strncmp(m_Current, "Item", 4) == 0)
            {
                m_Current += 4;

                SkipWhiteSpace();
                if (!GetNumberLiteral(&out_Stage->itemsCount))
                    return false;

                for (int i = 0; i < out_Stage->itemsCount; ++i)
                {
                    SkipWhiteSpace();
                    SubString block;
                    if (!GetBlock(&block))
                    {
                        return false;
                    }

                    if (!ParseEnemyInfo(block, &out_Stage->enemies[i]))
                    {
                        return false;
                    }
                }
            }*/
            else
            {
                PrintError(L"잘못된 문법");
                return false;
            }
            break;

        default:
            PrintError(L"잘못된 문법");
            return false;
        }
    }

    return true;
}

bool StageParser::ParsePlayerInfo(const SubString& texts, PlayerInfo* out_pPlayerInfo)
{
    Assert(out_pPlayerInfo, L"out parameter must not be null");

    const char* identifiers[] = { "sprite", "coord" };
    constexpr int identifiersLength = sizeof(identifiers) / sizeof(char*);

    m_Current = texts.begin + 1;
    while (true)
    {
        SkipWhiteSpace();
        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        if (GetCharType(*m_Current) != CharType::Identifier)
            return false;

        SkipWhiteSpace();
        SubString identifier;
        if (!GetIdentifier(&identifier))
        {
            PrintError(L"식별자 : 값 이런 형식으로 적으세요.");
            return false;
        }

        int i;
        for (i = 0; i < 2; ++i)
        {
            if (identifier.equal(identifiers[i]))
                break;
        }

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
        {
            *identifier.end = '\0';
            PrintError(L"'%hs'에 콜론 빼먹음", identifier.begin);
            return false;
        }

        m_Current++;
        SkipWhiteSpace();

        WCHAR path[MAX_PATH];
        Sprite* sprite;
        COORD coord;
        switch (i)
        {
        case 0:
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"sprite: \"<파일 경로 명>\" 이렇게 들어가야됨. ");
                return false;
            }

            sprite = ResourceManager::Instance()->GetSprite(path);
            if (!sprite)
            {
                PrintError(L"'%s' sprite file 명이 ResourceManager에 등록되어 있지 않습니다.", path);
                return false;
            }

            out_pPlayerInfo->sprite = sprite;
            break;

        case 1:
            if (!GetCoord(&coord))
            {
                PrintError(L"coord: (x, y) 이런 식으로 좌표가 들어가야 됨");
                return false;
            }
            out_pPlayerInfo->startCoord = coord;
            break;

        default:
            *identifier.end = '\0';
            PrintError(L"'%hs' 라는 식별자는 존재하지 않습니다.", identifier.begin);
            return false;
        }
    }
    m_Current++;

    return true;
}

bool StageParser::ParseEnemyInfo(const SubString& texts, EnemyInfo* out_pEnemyInfo)
{
    Assert(out_pEnemyInfo, L"out parameter must not be null");

    const char* identifiers[] = { "sprite", "coord", "loopPattern", "pattern", "HP", "spawn"};
    constexpr int identifiersLength = sizeof(identifiers) / sizeof(char*);

    m_Current = texts.begin + 1;

    while (true)
    {
        SkipWhiteSpace();
        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        if (GetCharType(*m_Current) != CharType::Identifier)
            return false;

        SkipWhiteSpace();
        SubString identifier;
        if (!GetIdentifier(&identifier))
        {
            PrintError(L"식별자 : 값 이런 형식으로 적으세요.");
            return false;
        }

        int i;
        for (i = 0; i < identifiersLength; ++i)
        {
            if (identifier.equal(identifiers[i]))
                break;
        }

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Colon)
        {
            *identifier.end = '\0';
            PrintError(L"'%hs'에 콜론 빼먹음", identifier.begin);
            return false;
        }
        m_Current++;

        SkipWhiteSpace();

        WCHAR path[MAX_PATH];
        Sprite* sprite;
        int temp;
        PatternList* pPatternList;
        switch (i)
        {
        case 0:
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"sprite: \"<파일 경로 명>\" 이렇게 들어가야됨. ");
                return false;
            }

            sprite = ResourceManager::Instance()->GetSprite(path);
            if (!sprite)
            {
                PrintError(L"'%s' sprite file 명이 ResourceManager에 등록되어 있지 않습니다.", path);
                return false;
            }
            out_pEnemyInfo->sprite = sprite;
            break;

        case 1:
            if (!GetCoord(&out_pEnemyInfo->startCoord))
            {
                PrintError(L"coord의 값을 (x, y) 형식의 좌표여야 합니다.");
                return false;
            }
            break;
        
        case 2:
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"bLoopPatterns의 값은 숫자여야 합니다.");
                return false;
            }
            out_pEnemyInfo->bLoopPatterns = (BOOL)temp;
            break;
        
        case 3:
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"patterns의 값은 \"<pattern 파일 경로>\"로 입력해야 됨.");
                return false;
            }

            pPatternList = ResourceManager::Instance()->GetPatternList(path);
            if (!pPatternList)
            {
                PrintError(L"'%s'다음과 같은 파일은 ResourceManager에 등록 안됨", path);
                return false;
            }

            out_pEnemyInfo->pPatternList = pPatternList;
            break;

        case 4:
            if (!GetNumberLiteral(&out_pEnemyInfo->hp))
            {
                PrintError(L"HP의 값은 NumberLiteral이 와야됨.");
                return false;
            }
            break;

        case 5:
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"spawn의 값은 NumberLiteral이 와야됨.");
                return false;
            }
            out_pEnemyInfo->spawnFrame = (DWORD)temp;
            break;
        
        default:
            *identifier.end = '\0';
            PrintError(L"'%hs'라는 식별자는 없습니다.", identifier.begin);
            return false;
        }
    }

    m_Current++;
    return true;
}
