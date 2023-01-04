#pragma once

class Parser
{
protected:
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
    Parser() = default;
    ~Parser()
    {
        delete m_Texts;
    }

    bool InitByFilename(const WCHAR* filename)
    {
        FILE* file = nullptr;
        _wfopen_s(&file, filename, L"r");
        if (file == nullptr)
        {
            PrintError(L"'%s' file open err", filename);
            return false;
        }

        size_t size = (size_t)GetFileSize(file);
        m_Texts = new char[size];

        size_t result = fread(m_Texts, 1, size, file);
        if (result == 0)
        {
            PrintError(L"'%s' file read err", filename);
            fclose(file);
            return false;
        }
        fclose(file);

        wcscpy_s(m_Filename, MAX_PATH, filename);

        Assert(result < size, L"버퍼 오버런 컴파일러 경고 막기용");
        m_Texts[result] = '\0';
        m_Current = m_Texts;
        return true;
    }

    virtual bool Run() = 0;

protected:
    void SkipWhiteSpace()
    {
        while (GetCharType(*m_Current) == CharType::Whitespace)
        {
            m_Current++;
        }
    }

    bool GetBlock(SubString* out_Block)
    {
        SkipWhiteSpace();
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
                else if (braceCount > 0)
                    braceCount--;
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

    void GetIdentifier(SubString* sub)
    {
        SkipWhiteSpace();
        sub->begin = m_Current;

        while (GetCharType(*m_Current) == CharType::Identifier)
            m_Current++;

        sub->end = m_Current;
    }

    bool GetStringLiteral(WCHAR* wcs, int cchwcs)
    {
        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::StringLiteral)
        {
            int temp;
            GetLine(m_Current, &temp);
            PrintError(L"%d in file '%s'\n 이 부분에 \"String Literal\"이 와야된다.", temp, m_Filename);
            return false;
        }
        char* begin = ++m_Current;

        while (GetCharType(*m_Current) != CharType::StringLiteral)
        {
            if (*m_Current == L'\0')
            {
                PrintError(L"\"\"짝이 안맞는다. %s file", m_Filename);
                return false;
            }
            ++m_Current;
        }

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
        int temp;

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::OpenParenthesis)
        {
            GetLine(m_Current, &temp);
            PrintError(L"%d line in '%s' file\n 이 부분에 (이 빠졌습니다.", temp, m_Filename);
            return false;
        }
        m_Current++;

        if (!GetNumberLiteral(&temp))
            return false;
        coord->X = (short)temp;

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::Comma)
        {
            GetLine(m_Current, &temp);
            PrintError(L"%d line in '%s' file\n 이 부분에 :이 빠졌습니다.", temp, m_Filename);
            return false;
        }
        ++m_Current;

        if (!GetNumberLiteral(&temp))
            return false;
        coord->Y = (short)temp;

        SkipWhiteSpace();
        if (GetCharType(*m_Current) != CharType::CloseParenthesis)
        {
            GetLine(m_Current, &temp);
            PrintError(L"%d line in '%s' file\n 이 부분에 )이 빠졌습니다.", temp, m_Filename);
            return false;
        }
        ++m_Current;
        return true;
    }

    bool GetNumberLiteral(int* out_int)
    {
        SkipWhiteSpace();
        bool bMinus = false;
        CharType type = GetCharType(*m_Current);

        if (type == CharType::Minus)
        {
            m_Current++;
            bMinus = true;
        }

        if (GetCharType(*m_Current) != CharType::NumberLiteral)
        {
            int errorLine;
            GetLine(m_Current, &errorLine);
            PrintError(L"%d line in '%s' file\n 이 부분의 숫자를 파싱하다 오류났습니다.", errorLine, m_Filename);

            return false;
        }

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

    bool GetLine(const char* current, int* out_Line)
    {
        const char* search = m_Texts;
        int line = 1;

        while (*search != L'\0')
        {
            if (*search == '\n')
                line++;

            search++;
        }
        *out_Line = line;

        return true;
    }

protected:
    WCHAR m_Filename[MAX_PATH];
    char* m_Current;
    char* m_Texts;
};