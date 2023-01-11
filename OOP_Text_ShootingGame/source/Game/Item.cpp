#include "stdafx.h"
#include "Item.h"

#include "Engine/Renderer.h"
#include "Engine/Sprite.h"

#include "Resource/infos.h"

#include "GameDefine.h"
#include "ObjectType.h"

Item::Item(ItemInfo* itemInfo)
    : ObjectBase(ObjectType_Item)
{
    m_X = itemInfo->startCoord.X;
    m_Y = itemInfo->startCoord.Y;
    m_Sprite = itemInfo->sprite;

    m_ItemInfo = itemInfo;
    m_Dir = itemInfo->dir;
}

void Item::Update()
{
    DWORD frames = m_Scene->GetFrames();

    if (frames % 10 == 0)
    {
        m_X += m_Dir.X;
        m_Y += m_Dir.Y;

        if (m_X <= 0 || m_X + m_Sprite->Width() - 1 >= GAME_WIDTH)
            m_Dir.X *= -1;
        if (m_Y <= 0 || m_Y + m_Sprite->Height() -1 >= GAME_HEIGHT)
            m_Dir.Y *= -1;
    }
}

void Item::Render(Renderer* renderer)
{
    renderer->DrawSprite(m_X, m_Y, m_Sprite);
}
