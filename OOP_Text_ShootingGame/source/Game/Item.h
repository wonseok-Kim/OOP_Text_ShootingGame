#pragma once

#include "Engine/ObjectBase.h"

struct ItemInfo;

class Item : public ObjectBase
{
public:
    Item(ItemInfo* itemInfo);

    virtual void Update();
    virtual void Render(Renderer* renderer);

    const ItemInfo* GetInfo() const { return m_ItemInfo; }

private:
    ItemInfo* m_ItemInfo;
    COORD m_Dir;
};