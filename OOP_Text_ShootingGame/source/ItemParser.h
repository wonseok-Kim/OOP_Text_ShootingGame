#pragma once

#include "Parser.h"

struct ItemInfo;

class ItemParser : public Parser
{
public:
    ItemParser() = default;
    ~ItemParser() = default;

    bool ParseItem(ItemInfo* out_Item);
};

