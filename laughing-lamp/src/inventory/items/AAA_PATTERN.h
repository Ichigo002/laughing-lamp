/// Pattern made by Victor developer C++
///
/// To make item available, add: include "YourItem.h" at file Items.h
/// And then add it by InventorySystem::add<YourItemClass>(int amount)!!
/// Below pattern shows out how every item shall be done
/// ====================================================

#ifndef Z_ITEM_PATTERN_H
#define Z_ITEM_PATTERN_H

#include "../InventoryItemData.h"

class Item_Pattern : public InventoryItemData
{
public:
	Item_Pattern(int max_stack)
		: InventoryItemData("pattern", 1, 0)
	{
		//stackable = true;
		//this->max_stack = max_stack;
	}
};

#endif
