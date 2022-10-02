#ifndef Z_ITEM_WOOD_H
#define Z_ITEM_WOOd_H

#include "../InventoryItemData.h"

class Item_Wood : public InventoryItemData
{
public:
	Item_Wood(int max_stack)
		: InventoryItemData("wood", 1, 0)
	{
		stackable = true;
		this->max_stack = max_stack;
	}
};

#endif
