#ifndef INVENTORY_ITEM_DATA_H
#define INVENTORY_ITEM_DATA_H

#include <string>
#include "../utility/Camera.h"
#include "../utility/TextureManager.h"
#include <SDL.h>

// Tags for attributes of item in data
enum DataTags
{
	//must-have
	DT_TAG_BLOCK = 1 << 0,
	DT_TAG_ITEM  = 1 << 1,

	DT_STACKABLE = 1 << 2,
	DT_DROPABLE  = 1 << 3,

	DT_BUILDABLE = 1 << 4,
		DT_COLLIDABLE = 1 << 5,
		DT_PLACEOVERABLE = 1 << 6, // Make possible placing THIS ON OTHER object during building
};

class InventoryItemData 
{
public:
	InventoryItemData(std::string _item_name, int max_st);
	~InventoryItemData();

	// Future Feature
	// TODO 2 if animation will be needed
	//virtual void updateAnimation(...);

	/// <summary>
	/// Initialize texture only if it's needed
	/// </summary>
	/// <param name="c"></param>
	void _initTex(Camera* c);

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
	/// Returns if stack is full
	/// </summary>
	bool isStackFull();

	/// <summary>
	/// Retruns true if item includes attribute
	/// </summary>
	bool attr(DataTags dt);

	/// <summary>
	/// Returns item texture
	/// </summary>
	SDL_Texture* getItemTex();

protected: // to init parameters of item
	std::string item_name; // for instance: black_wool

	int attrs; // Attributes of items
	
	SDL_Texture* item_tex; // Texture loaded while it is created. Texture is loaded from file with name i.e. 'wooden_block.png';
	// item_tex is initialized if it needs to be rendered. First init is in UIInevntory.

	SDL_Rect destR; // Rect on the screen relative to size of Hex
	SDL_Rect colliderR; // Rect of collision if item's got DT_COLLIDABLE 

private:
	int stack;
	int max_stack;  // Sets maximum stack in one slot
};

#endif
