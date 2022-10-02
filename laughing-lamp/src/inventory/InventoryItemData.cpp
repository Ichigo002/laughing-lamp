#include "InventoryItemData.h"

InventoryItemData::InventoryItemData(std::string _item_name, int _item_rect_x, int _item_rect_y) :
	item_name(_item_name), stackable(false), max_stack(16),
	item_rect_x(_item_rect_x), item_rect_y(_item_rect_y)
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

int InventoryItemData::getSizeStack()
{
	return stack + 1;
}

int InventoryItemData::getMaxSizeStack()
{
	return max_stack - 1;
}

int InventoryItemData::getExtantSpace()
{
	return max_stack - 1 - stack > 0 ? max_stack - stack - 1 : 0;
}

int InventoryItemData::getSrcRectItemX()
{
	return item_rect_x;
}

int InventoryItemData::getSrcRectItemY()
{
	return item_rect_y;
}

bool InventoryItemData::isStackable()
{
	return stackable;
}

bool InventoryItemData::isStackFull()
{
	return stack == max_stack - 1;
}

void InventoryItemData::__setMaxSizeStacking(int mxst)
{
	max_stack = mxst;
}
