#include "stdafx.h"
#include "StageParser.h"

#include "ResourceManager.h"
#include "Infos.h"

bool StageParser::ParseStage(Stage* out_Stage)
{
    Assert(out_Stage, L"out parameter must not be null");

    ZeroMemory(out_Stage, sizeof(Stage));

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
                    PrintError(L"Player 파싱하다 에러");
                    return false;
                }
            }
            else if (strncmp(m_Current, "Enemy", 5) == 0)
            {
                m_Current += 5;

                SkipWhiteSpace();
                if (!GetNumberLiteral(&out_Stage->enemiesCount))
                {
                    PrintError(L"Enemy 다음에 Enemy의 숫자가 와야 됩니다.");
                    return false;
                }
                
                // delete[] in ResourceManager::~ResourceManager().
                out_Stage->enemies = new EnemyInfo[out_Stage->enemiesCount];

                for (int i = 0; i < out_Stage->enemiesCount; ++i)
                {
                    SkipWhiteSpace();
                    SubString block;
                    if (!GetBlock(&block))
                    {
                        goto delete_and_out_ParseStage;
                    }

                    if (!ParseEnemyInfo(block, &out_Stage->enemies[i]))
                    {
                        PrintError(L"enemy 파싱하다 에러");
                        goto delete_and_out_ParseStage;
                    }
                }
            }
            else if (strncmp(m_Current, "Item", 4) == 0)
            {
                m_Current += 4;

                SkipWhiteSpace();
                if (!GetNumberLiteral(&out_Stage->itemsCount))
                {
                    PrintError(L"Item 다음에 Item의 숫자가 와야 됩니다.");
                    return false;
                }

                // delete[] in ResourceManager::~ResourceManager().
                out_Stage->items = new ItemInfo[out_Stage->itemsCount];

                for (int i = 0; i < out_Stage->itemsCount; ++i)
                {
                    SkipWhiteSpace();
                    SubString block;
                    if (!GetBlock(&block))
                    {
                        PrintError(L"Item 파싱하다 에러");
                        goto delete_and_out_ParseStage;
                    }

                    if (!ParseItemInfo(block, &out_Stage->items[i]))
                    {
                        PrintError(L"Item 파싱하다 에러");
                        goto delete_and_out_ParseStage;
                    }
                }
            }
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

delete_and_out_ParseStage:
    delete[] out_Stage->enemies;
    delete[] out_Stage->items;
    return false;
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

    ZeroMemory(out_pEnemyInfo, sizeof(EnemyInfo));

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

bool StageParser::ParseItemInfo(const SubString& texts, ItemInfo* out_pItemInfo)
{
    ZeroMemory(out_pItemInfo, sizeof(ItemInfo));

    const char* identifiers[] = { "hp", "shotInfo", "sprite", "spawn", "coord", "dir"};
    int identifiersLength = sizeof(identifiers) / sizeof(char*);

    m_Current = texts.begin + 1;

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

        SkipWhiteSpace();
        WCHAR path[MAX_PATH];
        int temp;
        switch (i)
        {
        case 0:
            if (!GetNumberLiteral(&out_pItemInfo->hp))
            {
                PrintError(L"hp의 값을 숫자여야 합니다.");
                return false;
            }
            break;

        case 1:
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo의 값을 StringLiteral여야 합니다.");
                return false;
            }

            out_pItemInfo->shotInfo = ResourceManager::Instance()->GetShotInfo(path);
            if (!out_pItemInfo->shotInfo)
            {
                PrintError(L"%s 다음과 같은 shotInfo 파일을 못찾겠음", path);
                return false;
            }
            break;

        case 2:
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo의 값을 StringLiteral여야 합니다.");
                return false;
            }

            out_pItemInfo->sprite = ResourceManager::Instance()->GetSprite(path);
            if (!out_pItemInfo->sprite)
            {
                PrintError(L"%s 다음과 같은 sprite 파일을 못찾겠음", path);
                return false;
            }
            break;

        case 3: //"spawn"
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"spawn의 값은 StringLiteral여야 합니다.");
                return false;
            }
            out_pItemInfo->spawnFrame = (DWORD)temp;
            break;

        case 4: // "coord"
            if (!GetCoord(&out_pItemInfo->startCoord))
            {
                PrintError(L"coord의 값은 (x, y)여야 합니다.");
                return false;
            }
            break;

        case 5:  // "dir"
            if (!GetCoord(&out_pItemInfo->dir))
            {
                PrintError(L"dir의 값은 (x, y)여야 합니다.");
                return false;
            }
            break;

        default:
            *Identifier.end = '\0';
            PrintError(L"존재하지 않는 필드 명 '%hs'", Identifier.begin);
            return false;
        }
    }

    if (!out_pItemInfo->sprite)
    {
        PrintError(L"Item에 sprite 파일은 필수임");
        return false;
    }

    m_Current++;
    return true;
}
