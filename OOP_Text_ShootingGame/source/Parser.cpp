#include "stdafx.h"
#include "Parser.h"

bool Parser::Init(const WCHAR* filename)
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

    if (result < size) // Buffer Overrun warning 막기용
        m_Texts[result] = '\0';
    m_Current = m_Texts;
    return true;
}

void Parser::SkipWhiteSpace()
{
    while (GetCharType(*m_Current) == CharType::Whitespace)
    {
        m_Current++;
    }
}

bool Parser::GetBlock(SubString* out_Block)
{
    if (GetCharType(*m_Current) != CharType::OpenBrace)
    {
        PrintError(L"Block의 시작점 아님");
        return false;
    }

    out_Block->begin = m_Current++;
    while (true)
    {
        if (*m_Current == '\0')
            goto out_and_print_err;

        if (GetCharType(*m_Current) == CharType::OpenBrace)
            goto out_and_print_err;

        if (GetCharType(*m_Current) == CharType::CloseBrace)
            break;

        ++m_Current;
    }
    out_Block->end = ++m_Current;

    return true;

out_and_print_err:
    m_Current = out_Block->begin;
    PrintError(L"{} 짝이 안맞다.");
    return false;
}

long Parser::GetFileSize(FILE* file)
{
    Assert(file, L"file must be not null");
    long backupPos = ftell(file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    fseek(file, backupPos, SEEK_SET);
    return size;
}

bool Parser::GetIdentifier(SubString* sub)
{
    if (GetCharType(*m_Current) != CharType::Identifier)
    {
        abort();
        return false;
    }

    sub->begin = m_Current;

    while (GetCharType(*m_Current) == CharType::Identifier)
        m_Current++;

    sub->end = m_Current;
    return true;
}

bool Parser::GetStringLiteral(WCHAR* wcs, int cchwcs)
{
    if (GetCharType(*m_Current) != CharType::StringLiteral)
        return false;

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

bool Parser::GetCoord(COORD* coord)
{
    int temp;

    SkipWhiteSpace();
    if (GetCharType(*m_Current) != CharType::OpenParenthesis)
    {
        return false;
    }
    m_Current++;

    SkipWhiteSpace();
    if (!GetNumberLiteral(&temp))
        return false;
    coord->X = (short)temp;

    SkipWhiteSpace();
    if (GetCharType(*m_Current) != CharType::Comma)
    {
        return false;
    }
    ++m_Current;

    SkipWhiteSpace();
    if (!GetNumberLiteral(&temp))
        return false;
    coord->Y = (short)temp;

    SkipWhiteSpace();
    if (GetCharType(*m_Current) != CharType::CloseParenthesis)
    {
        return false;
    }
    ++m_Current;
    return true;
}

bool Parser::GetNumberLiteral(int* out_int)
{
    bool bMinus = false;
    CharType type = GetCharType(*m_Current);

    if (type == CharType::Minus)
    {
        m_Current++;
        bMinus = true;
    }

    if (GetCharType(*m_Current) != CharType::NumberLiteral)
    {
        PrintError(L"숫자를 파싱하다 오류났습니다.");
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

Parser::CharType Parser::GetCharType(char ch)
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

//inline bool Parser::GetLine(const char* current, int* out_Line)
//{
//    const char* search = m_Texts;
//    int line = 1;
//
//    while (*search != L'\0')
//    {
//        if (search == current)
//            break;
//
//        if (*search == '\n')
//            line++;
//
//        search++;
//    }
//    *out_Line = line;
//
//    return true;
//}
