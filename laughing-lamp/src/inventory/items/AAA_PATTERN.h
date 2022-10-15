/// Pattern made by Wiktor developer C++
///
/// To make item available, add: include "YourItem.h" at file Items.h
/// And then add it in InventorySystem::initItems() your class!
/// And just call item with your name. here: "pattern"
/// Below pattern shows out how every item shall be done
/// ====================================================

#ifndef Z_ITEM_PATTERN_H
#define Z_ITEM_PATTERN_H

#include "../InventoryItemData.h"

class Item_Pattern : public InventoryItemData
{
public:
	Item_Pattern(int max_stack)
		: InventoryItemData("pattern", max_stack)
	{
		attrs = 
			DT_STACKABLE | 
			DT_BUILDABLE | 
			DT_DROPABLE; // all available tags under DT_
	}
};

#endif
