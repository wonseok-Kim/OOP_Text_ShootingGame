#pragma once

#include "Stage.h"
#include "ResourceManager.h"

class StageParser
{
    enum class CharType
    {
        Whitespace,
        OpenBrace,
        CloseBrace,
        OpenParenthesis,
        CloseParenthesis,
        Identifier,
        Colon,
        StringLiteral,
        NumberLiteral,
        Minus,
        Comma,
        Error
    };

    struct SubString
    {
        char* begin;
        char* end;  // 포함 안함.

        bool empty() { return begin == end; }

        bool equal(const char* str)
        {
            size_t len = end - begin;
            return strncmp(begin, str, len) == 0;
        }
    };

    struct Token
    {
        SubString key;
        SubString value;
    };

public:
    StageParser() = default;
    ~StageParser()
    {
        delete m_StageTexts;
    }

    bool Init(const WCHAR* filename)
    {
        FILE* file = nullptr;
        _wfopen_s(&file, filename, L"r");
        if (file == nullptr)
        {
            PrintError(L"'%s' file open err", filename);
            return false;
        }

        size_t size = (size_t)GetFileSize(file);
        m_StageTexts = new char[size];

        size_t result = fread(m_StageTexts, 1, size, file);
        if (result == 0)
        {
            PrintError(L"'%s' file read err", filename);
            return false;
        }

        Assert(result < size, L"버퍼 오버런 컴파일러 경고 막기용");
        m_StageTexts[result] = '\0';
        m_Current = m_StageTexts;
        m_Stage = new Stage;
        return true;
    }

    bool Run()
    {
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

                    ParsePlayerInfo(block);
                }
                else if (strncmp(m_Current, "Enemy", 5) == 0)
                {
                    m_Current += 5;
                    SkipWhiteSpace();

                    GetNumberLiteral(&m_Stage->enemiesCount);
                    SkipWhiteSpace();

                    m_Stage->enemies = new EnemyInfo[m_Stage->enemiesCount];

                    for (int i = 0; i < m_Stage->enemiesCount; ++i)
                    {
                        SubString block;
                        if (!GetBlock(&block))
                            return false;

                        ParseEnemyInfo(block, &m_Stage->enemies[i]);
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
    }

    Stage* GetStage()
    {
        return m_Stage;
    }

private:
    void SkipWhiteSpace()
    {
        while (GetCharType(*m_Current) == CharType::Whitespace)
        {
            m_Current++;
        }
    }

    bool GetBlock(SubString* out_Block)
    {
        if (GetCharType(*m_Current) != CharType::OpenBrace)
        {
            PrintError(L"Block의 시작점 아님");
            return false;
        }

        int braceCount = 0;
        out_Block->begin = ++m_Current;
        while (true)
        {
            if (*m_Current == '\0')
                goto out_and_print_err;

            if (GetCharType(*m_Current) == CharType::OpenBrace)
                braceCount++;

            if (GetCharType(*m_Current) == CharType::CloseBrace)
            {
                if (braceCount == 0)
                    break;
                else
                    goto out_and_print_err;
            }

            ++m_Current;
        }
        out_Block->end = m_Current;

        m_Current = out_Block->begin;
        return true;

    out_and_print_err:
        m_Current = out_Block->begin;
        PrintError(L"{} 짝이 안맞다.");
        return false;
    }

    long GetFileSize(FILE* file)
    {
        Assert(file, L"file must be not null");
        long backupPos = ftell(file);

        fseek(file, 0, SEEK_END);
        long size = ftell(file);

        fseek(file, backupPos, SEEK_SET);
        return size;
    }

    bool ParsePlayerInfo(const SubString& texts)
    {
        const char* keys[] = { "sprite", "coord" };
        const CharType types[] = { CharType::StringLiteral, CharType::OpenParenthesis };

        m_Current = texts.begin;
        while (true)
        {
            SubString key;
            SkipWhiteSpace();

            if (m_Current == texts.end)
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

            if (i == 2)
                return false;

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

                Sprite* sprite = ResourceManager::Instance().GetSprite(path);
                if (!sprite)
                    return false;
                m_Stage->player.sprite = sprite;
                break;
            }
            case 1:
            {
                COORD coord;
                GetCoord(&coord);
                m_Stage->player.startCoord = coord;
                break;
            }
            default:
                PrintError(L"잘못된 문법");
                return false;
            }
        }

        return true;
    }

    bool ParseEnemyInfo(const SubString& texts, EnemyInfo* enemy)
    {
        const char* keys[] = { "sprite", "coord", "loopPattern", "patterns" };        

        m_Current = texts.begin;

        while (true)
        {
            SubString key;
            SkipWhiteSpace();

            if (m_Current == texts.end)
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

            if (i == 2)
                return false;

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

                Sprite* sprite = ResourceManager::Instance().GetSprite(path);
                if (!sprite)
                    return false;
                enemy->sprite = sprite;
                break;
            }
            case 1:
            {
                if (GetCharType(*m_Current) != CharType::OpenParenthesis)
                    return false;

                COORD coord{};
                GetCoord(&coord);
                enemy->startCoord = coord;
                break;
            }
            case 2:
            {
                if (GetCharType(*m_Current) != CharType::NumberLiteral)
                    return false;

                int temp;
                GetNumberLiteral(&temp);
                enemy->bLoopPatterns = temp;
                break;
            }
            case 3:
            {

            }
            default:
                PrintError(L"잘못된 문법");
                return false;
            }
        }

        return true;
    }

    void GetIdentifier(SubString* sub)
    {
        sub->begin = m_Current;

        while (GetCharType(*m_Current) == CharType::Identifier)
            m_Current++;

        sub->end = m_Current;
    }

    bool GetStringLiteral(WCHAR* wcs, int cchwcs)
    {
        char* begin = ++m_Current;

        while (GetCharType(*m_Current) != CharType::StringLiteral)
            ++m_Current;

        int cbMultiByte = (int)(m_Current - begin);
        int result = MultiByteToWideChar(CP_ACP, 0, begin, cbMultiByte, wcs, cchwcs);
        if (result == 0)
        {
            PrintError(L"MultiByteToWideChar err : %d", GetLastError());
            return false;
        }
        wcs[result] = 0;

        ++m_Current;
        return true;
    }

    bool GetCoord(COORD* coord)
    {
        if (GetCharType(*m_Current) != CharType::OpenParenthesis)
            return false;

        m_Current++;
        SkipWhiteSpace();

        int temp;
        GetNumberLiteral(&temp);
        coord->X = (short)temp;
        SkipWhiteSpace();

        if (GetCharType(*m_Current) != CharType::Comma)
            return false;

        ++m_Current;
        SkipWhiteSpace();


        GetNumberLiteral(&temp);
        coord->X = (short)temp;
        SkipWhiteSpace();

        if (GetCharType(*m_Current) != CharType::CloseParenthesis)
            return false;
        ++m_Current;

        return true;
    }

    bool GetNumberLiteral(int* out_int)
    {
        bool bMinus = false;
        CharType type = GetCharType(*m_Current);

        if (type == CharType::Minus)
        {
            m_Current++;
            bMinus = true;
        }

        if (type != CharType::NumberLiteral)
            return false;

        *out_int = 0;

        while (GetCharType(*m_Current) == CharType::NumberLiteral)
        {
            *out_int *= 10;
            *out_int += *m_Current - '0';
            m_Current++;
        }

        if (bMinus)
            *out_int = -1 * (*out_int);

        return true;
    }

    CharType GetCharType(char ch)
    {
        if (ch == ' ' || ch == '\n' || ch == '\t')
            return CharType::Whitespace;

        if (ch == '{')
            return CharType::OpenBrace;

        if (ch == '}')
            return CharType::CloseBrace;

        if (ch == '(')
            return CharType::OpenParenthesis;

        if (ch == ')')
            return CharType::CloseParenthesis;

        if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'))
            return CharType::Identifier;

        if (ch == ':')
            return CharType::Colon;

        if (ch == '"')
            return CharType::StringLiteral;

        if ('0' <= ch && ch <= '9')
            return CharType::NumberLiteral;

        if (ch == '-')
            return CharType::Minus;

        if (ch == ',')
            return CharType::Comma;

        return CharType::Error;
    }


private:
    char* m_Current;
    char* m_StageTexts;
    Stage* m_Stage;
};

