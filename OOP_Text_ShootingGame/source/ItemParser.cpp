#include "stdafx.h"
#include "ItemParser.h"

#include "ResourceManager.h"
#include "Infos.h"

bool ItemParser::ParseItem(ItemInfo* out_Item)
{
    ZeroMemory(out_Item, sizeof(ItemInfo));

    const char* identifiers[] = { "hp", "shotInfo", "sprite" };
    int identifiersLength = sizeof(identifiers) / sizeof(char*);

    while (true)
    {
        SkipWhiteSpace();
        if (*m_Current == '\0')
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
        switch (i)
        {
        case 0:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&out_Item->hp))
            {
                PrintError(L"hp�� ���� ���ڿ��� �մϴ�.");
                return false;
            }
            break;

        case 1:
            SkipWhiteSpace();
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo�� ���� StringLiteral���� �մϴ�.");
                return false;
            }

            out_Item->shotInfo = ResourceManager::Instance()->GetShotInfo(path);
            if (!out_Item->shotInfo)
            {
                PrintError(L"%s ������ ���� shotInfo ������ ��ã����", path);
                return false;
            }
            break;

        case 2:
            SkipWhiteSpace();
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo�� ���� StringLiteral���� �մϴ�.");
                return false;
            }

            out_Item->sprite = ResourceManager::Instance()->GetSprite(path);
            if (!out_Item->sprite)
            {
                PrintError(L"%s ������ ���� sprite ������ ��ã����", path);
                return false;
            }
            break;

        default:
            *Identifier.end = '\0';
            PrintError(L"�������� �ʴ� �ʵ� �� '%hs'", Identifier.begin);
            return false;
        }
    }

    if (!out_Item->sprite)
    {
        PrintError(L"Item�� sprite ������ �ʼ���");
        return false;
    }

    return true;
}
