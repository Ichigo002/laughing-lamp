#ifndef INVENTORY_ITEM_DATA_H
#define INVENTORY_ITEM_DATA_H

#include <string>

class InventoryItemData 
{
public:
	InventoryItemData();
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
	int getSizeStack() { return stack+1; }

	/// <summary>
	/// Returns max size of stack
	/// </summary>
	/// <returns></returns>
	int getMaxSizeStack() { return max_stack-1; }

	/// <summary>
	/// Returns extant space in stack
	/// </summary>
	/// <returns></returns>
	inline int getExtantSpace() { return max_stack-1 - stack > 0 ? max_stack - stack-1 : 0; }

	/// <summary>
	/// Returns can item be stacked
	/// </summary>
	bool isStackable() { return stackable; }

	/// <summary>
	/// Returns if stack is full
	/// </summary>
	bool isStackFull() { return stack == max_stack-1; }
private:
	std::string item_name = "ITEM";

	bool stackable = true;
	int max_stack = 16;
private:
	int stack;
};

#endif
