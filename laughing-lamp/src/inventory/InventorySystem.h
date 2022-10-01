#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <SDL.h>
#include <string>
#include "InventoryItemData.h"

#define NO_FIELDS_X 5
#define NO_FIELDS_Y 5

/// <summary>
/// Position of slot in the inventory system
/// </summary>
struct PSlot 
{
public:
	PSlot(size_t x, size_t y)
	{
		this->x = x;
		this->y = y;
	}

	size_t x;
	size_t y;
};

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

	// SET OF ITEMS METHODS

	/// <summary>
	/// Adds new item to the inventory
	/// </summary>
	/// <returns>if inventory is full then return false.</returns>
	bool add(InventoryItemData* _new);

	/// <summary>
	/// Deletes the x items
	/// </summary>
	/// <param name="item_name">name of item to delete</param>
	/// <param name="amount">number of items to delete</param>
	/// <returns>if it can't delete the items, it'll return false</returns>
	bool del(std::string item_name, unsigned int amount = 1);

	/// <summary>
	/// Move the item from old position to new
	/// </summary>
	/// <param name="_old">old position</param>
	/// <param name="_new">new position</param>
	/// <returns>if you try move item from empty field or move into the busy field then it returns false</returns>
	bool move(PSlot _old, PSlot _new);

	// TODO 4 Drop method to do
	/// <summary>
	/// Drops the item from the inventory on the ground.
	/// </summary>
	/// <param name="s">slot of item to drop</param>
	/// <param name="amount">Number of items to drop</param>
	/// <returns>if everything runs successful then returns true</returns>
	bool drop(PSlot s, unsigned int amount = 1);

	/// <summary>
	/// Drops the item from the inventory on the ground.
	/// </summary>
	/// <param name="item_name">name of item to drop</param>
	/// <param name="amount">number of items to delete</param>
	/// <returns>if it can't drop the items, it'll return false</returns>
	bool drop(std::string item_name, unsigned int amount = 1);

	/// <summary>
	/// Returns true if the inventory is full
	/// </summary>
	bool checkFull();

	/// <summary>
	/// Returns the item from slot.
	/// If it won't find the item then returns nullptr
	/// </summary>
	InventoryItemData* getItem(PSlot s);

	// CURRENT SLOT METHODS

	/// <summary>
	/// Change current chosen slot
	/// </summary>
	void setCurrentSlot(PSlot slot);

	/// <summary>
	/// Returns current item
	/// </summary>
	InventoryItemData* getCurrentItem() { return current_item; }

	/// <summary>
	/// Prints the inventory in cmd
	/// </summary>
	void printCMD();
private:

	/// <summary>
	/// Returns first found free slot at set
	/// </summary>
	/// <returns>If there's no empty slot then return PSlot()</returns>
	PSlot getFreeSlot();

	/// <summary>
	/// Checks is slot's position in range of set.
	/// </summary>
	/// <param name="s">slot to check</param>
	bool validateSlot(PSlot s);

	/// <summary>
	/// Check is slot empty or busy
	/// </summary>
	//bool checkBusySlot(PSlot s);

	/// <summary>
	/// Creates the new table
	/// </summary>
	void createTable();

	InventoryItemData* current_item; // current item ready to use
	InventoryItemData* set; // set of all items
};

#endif
// TODO 3 Make new class for pool object and use it for dropped items and GameObjectManager