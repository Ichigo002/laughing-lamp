#ifndef ACCESSIBLE_ITEMS_MAP_H
#define ACCESSIBLE_ITEMS_MAP_H

#include <string>
#include <map>
#include "../InventoryItemData.h"
#include "../../GEV.h"

using GEV::invsys_max_stacking;

class AccessibleItemsMap
{
public:
	/// <summary>
	/// Adds new class item into set
	/// </summary>
	/// <typeparam name="T">Class inherited from InventoryItemData</typeparam>
	/// <returns>
	/// If item already exist, will return -1
	/// If T class isn't inherited from InventoryItemData, will return -2
	/// </returns>
	template <class T>
	int add();

	/// <summary>
	/// Makes new item based on name.
	/// </summary>
	/// <param name="name">name of item</param>
	/// <returns>
	/// If name isn't accessible or doesn't exist, will return nullptr
	/// </returns>
	InventoryItemData* make(std::string name);

	/// <summary>
	/// Counts all accessible items
	/// </summary>
	/// <returns>number of items' class</returns>
	int count();

	/// <summary>
	/// Checks if class with name exist
	/// </summary>
	bool exist(std::string name);
private:
	std::map<std::string, InventoryItemData*> mapit; // Map of all available items
};

#endif

template<class T>
inline int AccessibleItemsMap::add()
{
	if (!std::is_base_of<InventoryItemData, T>())
		return -2;

	InventoryItemData* nit = new T(invsys_max_stacking);

	if (exist(nit->getName()))
		return -1;

	mapit[nit->getName()] = nit;

	return 0;
}