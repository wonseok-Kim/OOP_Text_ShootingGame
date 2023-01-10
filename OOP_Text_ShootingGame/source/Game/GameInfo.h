#pragma once

#include "Engine/ObjectBase.h"

#include "GameDefine.h"
#include "ObjectType.h"

class GameInfo : public ObjectBase
{
public:
    GameInfo(int x = 0, int y = GAME_INFO_ROW)
        :ObjectBase(ObjectType_GameInfo)
    {
        m_X = x;
        m_Y = y;
    }

    bool Init(int life, int hp)
    {
        m_PlayerLife = life;
        m_PlayerHP = hp;

        errno_t err = 0;
        int i;
        for (i = 0; i < m_PlayerLife; ++i)
            err += wcscat_s(m_szLife, _countof(m_szLife), L"в╜");

        for (i = 0; i < m_PlayerHP; ++i)
            err += wcscat_s(m_szHP, _countof(m_szHP), L"бс");

        if (err != 0)
        {
            PrintError(L"err life: %d, hp: %d", life, hp);
            return false;
        }

        swprintf_s(m_szInfo, _countof(m_szInfo), s_Format, m_szLife, m_szHP);
        return true;
    }

    virtual void Update() override {}
    virtual void Render(Renderer* renderer) override;

    void OnUpdate(int life, int hp)
    {
        m_szLife[0] = L'\0';
        m_szHP[0] = L'\0';

        Init(life, hp);
    }

private:
    inline static const WCHAR* s_Format = L"\tLIFE %3s\tHP %3s\t ";

    WCHAR m_szLife[4]{};
    WCHAR m_szHP[4]{};

    WCHAR m_szInfo[GAME_WIDTH];

    int m_PlayerLife = 0;
    int m_PlayerHP = 0;
};

