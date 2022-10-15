#ifndef Z_ITEM_WOOD_H
#define Z_ITEM_WOOd_H

#include "../InventoryItemData.h"

class Item_Wood : public InventoryItemData
{
public:
	Item_Wood(int max_stack)
		: InventoryItemData("wooden_block", max_stack)
	{
		attrs =
			DT_TAG_BLOCK |
			DT_DROPABLE  |
			DT_STACKABLE |
			DT_BUILDABLE;
	}
};

#endif
