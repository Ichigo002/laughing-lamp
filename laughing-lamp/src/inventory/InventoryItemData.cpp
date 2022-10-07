#include "InventoryItemData.h"

InventoryItemData::InventoryItemData(std::string _item_name) :
	item_name(_item_name), stackable(false), max_stack(2)
{
	item_tex = nullptr;
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

void InventoryItemData::removeAllFromStack()
{
	stack = 0;
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

bool InventoryItemData::isStackable()
{
	return stackable;
}

bool InventoryItemData::isStackFull()
{
	return stack == max_stack - 1;
}

SDL_Texture* InventoryItemData::getItemTex()
{
	return item_tex;
}

void InventoryItemData::__setTex(SDL_Texture* t)
{
	item_tex = t;
}
