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

public:
    ~Parser() { delete m_Texts; }

    bool InitByFilename(const WCHAR* filename);

protected:
    Parser() = default;

    long GetFileSize(FILE* file);
    
    CharType GetCharType(char ch);
    void SkipWhiteSpace();

    bool GetBlock(SubString* out_Block);
    void GetIdentifier(SubString* sub);
    bool GetStringLiteral(WCHAR* wcs, int cchwcs);
    bool GetCoord(COORD* coord);
    bool GetNumberLiteral(int* out_int);
    bool GetLine(const char* current, int* out_Line);

protected:
    WCHAR m_Filename[MAX_PATH];
    char* m_Current;
    char* m_Texts;
};