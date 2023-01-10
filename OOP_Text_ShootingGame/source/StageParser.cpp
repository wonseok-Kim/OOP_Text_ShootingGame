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
                PrintError(L"�߸��� ����");
                return false;
            }
            break;

        default:
            PrintError(L"�߸��� ����");
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
            PrintError(L"�ĺ��� : �� �̷� �������� ��������.");
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
            PrintError(L"'%hs'�� �ݷ� ������", identifier.begin);
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
                PrintError(L"sprite: \"<���� ��� ��>\" �̷��� ���ߵ�. ");
                return false;
            }

            sprite = ResourceManager::Instance()->GetSprite(path);
            if (!sprite)
            {
                PrintError(L"'%s' sprite file ���� ResourceManager�� ��ϵǾ� ���� �ʽ��ϴ�.", path);
                return false;
            }

            out_pPlayerInfo->sprite = sprite;
            break;

        case 1:
            if (!GetCoord(&coord))
            {
                PrintError(L"coord: (x, y) �̷� ������ ��ǥ�� ���� ��");
                return false;
            }
            out_pPlayerInfo->startCoord = coord;
            break;

        default:
            *identifier.end = '\0';
            PrintError(L"'%hs' ��� �ĺ��ڴ� �������� �ʽ��ϴ�.", identifier.begin);
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
            PrintError(L"�ĺ��� : �� �̷� �������� ��������.");
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
            PrintError(L"'%hs'�� �ݷ� ������", identifier.begin);
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
                PrintError(L"sprite: \"<���� ��� ��>\" �̷��� ���ߵ�. ");
                return false;
            }

            sprite = ResourceManager::Instance()->GetSprite(path);
            if (!sprite)
            {
                PrintError(L"'%s' sprite file ���� ResourceManager�� ��ϵǾ� ���� �ʽ��ϴ�.", path);
                return false;
            }
            out_pEnemyInfo->sprite = sprite;
            break;

        case 1:
            if (!GetCoord(&out_pEnemyInfo->startCoord))
            {
                PrintError(L"coord�� ���� (x, y) ������ ��ǥ���� �մϴ�.");
                return false;
            }
            break;
        
        case 2:
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"bLoopPatterns�� ���� ���ڿ��� �մϴ�.");
                return false;
            }
            out_pEnemyInfo->bLoopPatterns = (BOOL)temp;
            break;
        
        case 3:
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"patterns�� ���� \"<pattern ���� ���>\"�� �Է��ؾ� ��.");
                return false;
            }

            pPatternList = ResourceManager::Instance()->GetPatternList(path);
            if (!pPatternList)
            {
                PrintError(L"'%s'������ ���� ������ ResourceManager�� ��� �ȵ�", path);
                return false;
            }

            out_pEnemyInfo->pPatternList = pPatternList;
            break;

        case 4:
            if (!GetNumberLiteral(&out_pEnemyInfo->hp))
            {
                PrintError(L"HP�� ���� NumberLiteral�� �;ߵ�.");
                return false;
            }
            break;

        case 5:
            if (!GetNumberLiteral(&temp))
            {
                PrintError(L"spawn�� ���� NumberLiteral�� �;ߵ�.");
                return false;
            }
            out_pEnemyInfo->spawnFrame = (DWORD)temp;
            break;
        
        default:
            *identifier.end = '\0';
            PrintError(L"'%hs'��� �ĺ��ڴ� �����ϴ�.", identifier.begin);
            return false;
        }
    }

    m_Current++;
    return true;
}
