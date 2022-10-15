#ifndef Z_ITEM_BRICK_H
#define Z_ITEM_BRICK_H

#include "../InventoryItemData.h"

class Item_BrickBlock : public InventoryItemData
{
public:
	Item_BrickBlock(int max_stack)
		: InventoryItemData("brick_block", max_stack)
	{
		attrs =
			DT_TAG_BLOCK |
			DT_DROPABLE  |
			DT_STACKABLE |
			DT_BUILDABLE;
	}

};

#endif
