#ifndef INVENTORY_ITEM_DATA_H
#define INVENTORY_ITEM_DATA_H

#include <string>

class InventoryItemData 
{
public:
	InventoryItemData(std::string _item_name, int _item_rect_x, int _item_rect_y);
	~InventoryItemData();
	/// <summary>
	/// Returns the name of item
	/// </summary>
	std::string getName() { return item_name; };

	/// <summary>
	/// Add to stack next items
	/// </summary>
	/// <param name="amount">Number of items to add to stack</param>
	/// <returns>Returns excess items. If all ran success then returns 0. If item cannot be stacked then return -1</returns>
	int addToStack(int amount = 1);

	/// <summary>
	/// Remove from stack the x items
	/// </summary>
	/// <param name="amount">Number of items to add to stack</param>
	/// <returns>Returns number of items which couldn't be already removed. If all ran success then return 0. If item cannot be stacked then return -1</returns>
	int removeFromStack(int amount = 1);

	/// <summary>
	/// Returns size of stack
	/// </summary>
	int getSizeStack();

	/// <summary>
	/// Returns max size of stack
	/// </summary>
	int getMaxSizeStack();

	/// <summary>
	/// Returns extant space in stack
	/// </summary>
	int getExtantSpace();

	/// <summary>
	/// Get item's source rect in X to multiply by WIDTH
	/// </summary>
	int getSrcRectItemX();

	/// <summary>
	/// Get item's source rect in Y to multiply by HEIGHT
	/// </summary>
	int getSrcRectItemY();

	/// <summary>
	/// Returns can item be stacked
	/// </summary>
	bool isStackable();

	/// <summary>
	/// Returns if stack is full
	/// </summary>
	bool isStackFull();

protected: // to init parameters of item
	std::string item_name; // for instance: black_wool

	bool stackable; // if true that item can be stacked in groups at inventory
	int max_stack; // used when stackable value true. Sets maximum stack in one slot
	
	int item_rect_x; // Item's number column in the source Texture. for instance: x = 3; Result: 3*WIDTH
	int item_rect_y; // Item's number rows in the source Texture. for instance: y = 4; Result: 4*HEGIHT
private:
	int stack;
};

#endif
