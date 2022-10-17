#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <string>
//FUCKING LNK2005 ERROR AND REDEFINITION!!!!
#include "accessible-items-map/AccessibleItemsMap.h"
#include "items/Items.h"
#include "dropping-system/DroppingSystem.h"
#include "../build-map/BuildMap.h"

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
	InventorySystem(DroppingSystem* dropsys, BuildMap* buildmap);
	~InventorySystem();

	// SET OF ITEMS METHODS

	/// <summary>
	/// Adds new item into inventory
	/// </summary>
	/// <param name="nameitem">name of item</param>
	/// <param name="amount">amount of items</param>
	/// <returns>
	/// if there's no empty slot in inventory, will return false
	/// if name is invalid, will return false
	/// </returns>
	bool add(std::string nameitem, int amount = 1);

	/// <summary>
	///  Adds new custom item back to the inventory
	/// </summary>
	/// <param name="item">item to add</param>
	/// <returns>if inventory is full or object is null then return false </returns>
	bool add(InventoryItemData* item);

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
	bool move_direct(PSlot _old, PSlot _new);

	/// <summary>
	/// Init move operation. Removes item from his place and put it into buffor
	/// </summary>
	/// <param name="f">where is old place of item</param>
	/// <param name="amount">number of items from this slot [if -1 then move all items]</param>
	void move_init(PSlot f, int amount);

	/// <summary>
	/// Execute move and finish it
	/// </summary>
	/// <param name="dest">Detination slot</param>
	void move_exec(PSlot dest);

	/// <summary>
	/// Cancel whole operation and returns items to its old place
	/// </summary>
	void move_cancel();

	/// <summary>
	/// Gets the status of moving. If it is ready to move_exec the true
	/// </summary>
	/// <returns></returns>
	bool move_ready();

	/// <summary>
	/// Just reset, do not returns item to his old slot
	/// </summary>
	void move_reset();

	/// <summary>
	/// Returns move item from buffor
	/// </summary>
	InventoryItemData* move_getItem();

	/// <summary>
	/// Drops the item from the inventory on the ground.
	/// If amount of items is -1 then drops all items
	/// </summary>
	/// <param name="s">slot of item to drop</param>
	/// <param name="amount">Number of items to drop</param>
	/// <returns>if everything runs successful then returns true</returns>
	bool drop(PSlot s, int amount = -1);

	/// <summary>
	/// Place focused item in hotbar by player
	/// </summary>
	void placeFocusedItem();

	/// <summary>
	/// Destroy item palced at cursor's position
	/// </summary>
	void destroyPlacedItem();

	/// <summary>
	/// Returns reference to dropping system
	/// </summary>
	DroppingSystem* getDroppingSystem();

	void update();

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
	/// Returns the set of items. Size of table is defined in GEV
	/// </summary>
	InventoryItemData*** getSet();

	/// <summary>
	/// Returns true If inventory containts enough items.
	/// </summary>
	/// <param name="item_name">name of item to check</param>
	/// <param name="amount">Number of items to check</param>
	bool contains(std::string item_name, int amount = 1);

	// TODO 1 Fix count method
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
	/// INITS DEFAULT ITEMS
	/// </summary>
	void initItems();

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

private:
	PSlot mov_old_slot; // Old slot of moving
	InventoryItemData* mov_item; // Current moving item

	PSlot current_item_slot; // current item ready to use
	InventoryItemData*** set; // set of all items

	AccessibleItemsMap mapitem; // Map of items
	DroppingSystem* dropsys; // Dropping system reference
	BuildMap* buildmap;
};

#endif
