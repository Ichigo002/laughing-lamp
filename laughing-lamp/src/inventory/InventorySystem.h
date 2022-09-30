#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <SDL.h>
#include <string>
#include "InventoryItemData.h"

#define NO_FIELDS_X 5
#define NO_FIELDS_Y 5

//  Coordinates system in the Inventory
//    
//  Y|X 0   1   2   3   4
//  0  [=] [=] [=] [=] [=]
//  1  [=] [=] [=] [=] [=]
//  2  [=] [=] [=] [=] [=]
//  3  [=] [=] [=] [=] [=]
//  4  [=] [=] [=] [=] [=]
//

/// <summary>
/// This class keeps all items
/// </summary>
class InventorySystem
{
public:
	InventorySystem();

	/// <summary>
	/// Adds new item to the inventory
	/// </summary>
	/// <returns>if inventory is full then return false.</returns>
	bool add(InventoryItemData* _new);

	/// <summary>
	/// Deletes the x items
	/// </summary>
	/// <param name="name">name of item to delete</param>
	/// <param name="amount">number of items to delete</param>
	/// <returns>if it can't delete the items, it'll return false</returns>
	bool del(std::string& name, unsigned int amount = 1);

	/// <summary>
	/// Move the item from old position to new
	/// </summary>
	/// <param name="oldx">old position x</param>
	/// <param name="oldy">old position y</param>
	/// <param name="newx">new position x</param>
	/// <param name="newy">new position y</param>
	/// <returns>if you try move item from empty field or move into the busy field then it returns false</returns>
	bool move(size_t oldx, size_t oldy, size_t newx, size_t newy);
private:
	/// <summary>
	/// Creates the new table
	/// </summary>
	void createTable();

	InventoryItemData* set; // set of all items
};

#endif