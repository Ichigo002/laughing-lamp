#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <string>
#include "InventoryItemData.h"
#include "items/Items.h"

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
	PSlot() { x = y = 0; }

	size_t x;
	size_t y;

	inline bool operator==(const PSlot& s)
	{
		return s.x == x && s.y == y;
	}
	inline bool isNeg()
	{
		return neg;
	}
	PSlot setNeg()
	{
		neg = true;
		return *this;
	}
	void unsetNeg() { neg = false; }
private:
	bool neg = false;
};

//  Coordinates system in the Inventory
//  Accessing the set: set[Y][X]
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

	/// <param name="max_size_stacking">Recommended sizes are next results of multiplying 2; e.g.: 2,4,8,16,32,64...</param>
	InventorySystem(int max_size_stacking = 32);
	~InventorySystem();

	// SET OF ITEMS METHODS

	/// <summary>
	/// Adds new item to the inventory
	/// </summary>
	/// <typeparam name="T">Inherited object from InventoryItemData</typeparam>
	/// <returns>if inventory is full then return false.</returns>
	template<class T>
	bool add(int amount = 1);

	/// <summary>
	/// Deletes the x items
	/// </summary>
	/// <param name="item_name">name of item to delete</param>
	/// <param name="amount">number of items to delete</param>
	/// <returns>if it can't delete the items, it'll return false</returns>
	bool del(std::string item_name, int amount = 1);

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
	bool drop(PSlot s, int amount = 1);

	/// <summary>
	/// Returns true if the inventory is full
	/// </summary>
	bool checkFull();

	/// <summary>
	/// Returns the item from slot.
	/// If it won't find the item then returns nullptr
	/// </summary>
	InventoryItemData* getItem(PSlot s);

	/// <summary>
	/// Returns the set of items. Size of table is defined in NO_FIELD_X & Y
	/// </summary>
	InventoryItemData*** getSet();

	/// <summary>
	/// Returns true If inventory containts enough items.
	/// </summary>
	/// <param name="item_name">name of item to check</param>
	/// <param name="amount">Number of items to check</param>
	bool contains(std::string item_name, int amount = 1);

	/// <summary>
	/// Returns the number of all items with this name
	/// </summary>
	/// <param name="item_name">name of item to drop</param>
	int count(std::string item_name);

	// CURRENT SLOT METHODS

	/// <summary>
	/// Change current chosen slot
	/// </summary>
	void setCurrentSlot(PSlot slot);

	/// <summary>
	/// Returns current item
	/// </summary>
	InventoryItemData* getCurrentItem();

	// CMD METHODS

	/// <summary>
	/// Prints the inventory in cmd
	/// </summary>
	void printCMD();
private:

	/// <summary>
	/// Returns first found free slot at set
	/// </summary>
	/// <returns>If there's no empty slot then return negative slot</returns>
	PSlot getFreeSlot();

	/// <summary>
	/// Returns free slot or slot with space to stack
	/// </summary>
	/// <param name="item_name">what item needs space</param>
	/// <returns>If there's no space then return negative slot.</returns>
	PSlot getFreeStackSlot(std::string item_name);

	/// <summary>
	/// Checks is slot's position in range of set.
	/// </summary>
	/// <param name="s">slot to check</param>
	bool validateSlot(PSlot s);

	/// <summary>
	/// Check is slot empty or busy
	/// </summary>
	//bool checkBusySlot(PSlot s);

	PSlot current_item_slot; // current item ready to use
	InventoryItemData*** set; // set of all items

	int max_size_stacking; // max stacking size of items in a single slot
};

template <class T>
bool InventorySystem::add(int amount)
{
	InventoryItemData* _n = new T(max_size_stacking);
	PSlot fs = getFreeStackSlot(_n->getName()); // free space
	if (fs.isNeg())
		return false;

	if (set[fs.y][fs.x] == nullptr)
	{
		set[fs.y][fs.x] = _n;
		return add<T>(amount - 1);
	}

	int extant = set[fs.y][fs.x]->getExtantSpace();
	amount -= extant;

	if (amount > 0)
	{
		set[fs.y][fs.x]->addToStack(extant);
		return add<T>(amount);
	}
	else
	{
		set[fs.y][fs.x]->addToStack(amount + extant);
	}
	return true;
}

#endif
