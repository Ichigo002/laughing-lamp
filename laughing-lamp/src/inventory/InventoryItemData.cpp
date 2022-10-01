#include "InventoryItemData.h"

InventoryItemData::InventoryItemData()
{
	stack = 0;
}

InventoryItemData::~InventoryItemData()
{
}

int InventoryItemData::addToStack(int amount)
{
	if (!isStackable())
		return -1;

	stack += amount;
	if (stack > max_stack-1)
	{
		int oo = stack - max_stack-1;
		stack = max_stack-1;
		return oo;
	}
	return 0;
}

int InventoryItemData::removeFromStack(int amount)
{
	if (!isStackable())
		return -1;

	stack -= amount;
	if (stack < 0)
	{
		int oo = stack * -1;
		stack = 0;
		return oo;
	}
	return 0;
}
