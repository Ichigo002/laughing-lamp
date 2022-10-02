#ifndef ITEM_BRICK_H
#define ITEM_BRICK_H

#include "../InventoryItemData.h"

class Item_BrickBlock : public InventoryItemData
{
public:
	Item_BrickBlock(int max_stack)
		: InventoryItemData("brick_block", 1, 0)
	{
		stackable = true;
		this->max_stack = max_stack;
	}

};

#endif
