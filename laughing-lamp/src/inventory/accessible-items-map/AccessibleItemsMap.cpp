#include "AccessibleItemsMap.h"

InventoryItemData* AccessibleItemsMap::make(std::string name)
{
	if (auto srh = mapit.find(name); srh != mapit.end())
	{
		InventoryItemData* nit = new InventoryItemData(*srh->second);
		nit->removeAllFromStack();
		return nit;
	}
	return nullptr;
}

inline int AccessibleItemsMap::count()
{
	return mapit.size();
}

bool AccessibleItemsMap::exist(std::string name)
{
	return mapit.find(name) != mapit.end();
}
