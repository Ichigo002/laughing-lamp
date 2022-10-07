#ifndef INVENTORY_ITEM_DATA_H
#define INVENTORY_ITEM_DATA_H

#include <string>
#include <SDL.h>

class InventoryItemData 
{
public:
	InventoryItemData(std::string _item_name);
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
	/// Removes all items and left only 1 item (THIS)
	/// </summary>
	void removeAllFromStack();

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
	/// Returns can item be stacked
	/// </summary>
	bool isStackable();

	/// <summary>
	/// Returns if stack is full
	/// </summary>
	bool isStackFull();

	/// <summary>
	/// Returns item texture
	/// </summary>
	SDL_Texture* getItemTex();

	/// <summary>
	/// sets the texture of item on init in UIInventory
	/// </summary>
	void __setTex(SDL_Texture* t);
protected: // to init parameters of item
	std::string item_name; // for instance: black_wool

	bool stackable; // if true that item can be stacked in groups at inventory
	int max_stack; // used when stackable value true. Sets maximum stack in one slot
	
	SDL_Texture* item_tex; // Texture loaded while it is created. Texture is loaded from file with name i.e. 'wooden_block.png';
	// item_tex is initialized if it needs to be rendered. First init is in UIINevntory.
private:
	int stack;
};

#endif
