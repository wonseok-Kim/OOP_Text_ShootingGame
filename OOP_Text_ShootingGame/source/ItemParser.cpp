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
        switch (i)
        {
        case 0:
            SkipWhiteSpace();
            if (!GetNumberLiteral(&out_Item->hp))
            {
                PrintError(L"hp의 값을 숫자여야 합니다.");
                return false;
            }
            break;

        case 1:
            SkipWhiteSpace();
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo의 값을 StringLiteral여야 합니다.");
                return false;
            }

            out_Item->shotInfo = ResourceManager::Instance()->GetShotInfo(path);
            if (!out_Item->shotInfo)
            {
                PrintError(L"%s 다음과 같은 shotInfo 파일을 못찾겠음", path);
                return false;
            }
            break;

        case 2:
            SkipWhiteSpace();
            if (!GetStringLiteral(path, MAX_PATH))
            {
                PrintError(L"shotInfo의 값을 StringLiteral여야 합니다.");
                return false;
            }

            out_Item->sprite = ResourceManager::Instance()->GetSprite(path);
            if (!out_Item->sprite)
            {
                PrintError(L"%s 다음과 같은 sprite 파일을 못찾겠음", path);
                return false;
            }
            break;

        default:
            *Identifier.end = '\0';
            PrintError(L"존재하지 않는 필드 명 '%hs'", Identifier.begin);
            return false;
        }
    }

    if (!out_Item->sprite)
    {
        PrintError(L"Item에 sprite 파일은 필수임");
        return false;
    }

    return true;
}
