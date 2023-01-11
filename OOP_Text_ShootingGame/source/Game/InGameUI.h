#pragma once

#include "Engine/ObjectBase.h"

#include "GameDefine.h"
#include "ObjectType.h"

class InGameUI : public ObjectBase
{
public:
    InGameUI(int x = 0, int y = GAME_INFO_ROW)
        :ObjectBase(ObjectType_InGameUI)
    {
        m_X = x;
        m_Y = y;
    }

    bool Init(int hp)
    {
        m_szUI[0] = L'\0';

        wcscat_s(m_szUI, _countof(m_szUI), L"    ");
        wcscat_s(m_szUI, _countof(m_szUI), s_szHP);
        for (int i = 0; i < 3; ++i)
        {
            if (i < hp)
                wcscat_s(m_szUI, _countof(m_szUI), L"¢½");
            else
                wcscat_s(m_szUI, _countof(m_szUI), L" ");
        }

        return true;
    }

    virtual void Update() override {}
    virtual void Render(Renderer* renderer) override;

    void OnUpdate(int hp)
    {
        Init(hp);
    }

private:
    inline static const WCHAR* s_szHP = L"HP ";

    WCHAR m_szUI[GAME_WIDTH] = { 0 };
};

