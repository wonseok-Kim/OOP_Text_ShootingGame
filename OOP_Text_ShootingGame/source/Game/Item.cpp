#include "stdafx.h"
#include "Item.h"

#include "Engine/Renderer.h"

#include "GameDefine.h"
#include "infos.h"
#include "ObjectType.h"

Item::Item(ItemInfo* itemInfo, int x, int y, COORD dir)
    : ObjectBase(ObjectType_Item)
{
    m_X = x;
    m_Y = y;
    m_Sprite = itemInfo->sprite;

    m_ItemInfo = itemInfo;
    m_Dir = dir;
}

void Item::Update()
{
    DWORD frames = m_Scene->GetFrames();

    if (frames % 2 == 0)
    {
        m_X += m_Dir.X;
        m_Y += m_Dir.Y;

        if (m_X <= 0 || m_X >= GAME_WIDTH)
            m_Dir.X *= -1;
        if (m_Y <= 0 || m_Y >= GAME_HEIGHT)
            m_Dir.Y *= -1;
    }
}

void Item::Render(Renderer* renderer)
{
    renderer->DrawSprite(m_X, m_Y, m_Sprite);
}
