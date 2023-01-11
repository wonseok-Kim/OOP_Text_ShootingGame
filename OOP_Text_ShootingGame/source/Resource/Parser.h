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

        bool empty() const { return begin == end; }

        bool equal(const char* str) const
        {
            size_t len = strlen(str);
            return strncmp(begin, str, len) == 0;
        }
    };

public:
    ~Parser() { delete[] m_Texts; }

    bool Init(const WCHAR* filename);

protected:
    Parser() = default;

    long GetFileSize(FILE* file);
    
    CharType GetCharType(char ch);
    void SkipWhiteSpace();

    bool GetBlock(SubString* out_Block);
    bool GetIdentifier(SubString* sub);
    bool GetStringLiteral(WCHAR* wcs, int cchwcs);
    bool GetCoord(COORD* coord);
    bool GetNumberLiteral(int* out_int);

protected:
    WCHAR m_Filename[MAX_PATH];
    char* m_Current;
    char* m_Texts;
};