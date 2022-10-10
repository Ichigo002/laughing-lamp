#ifndef DROPPING_SYSTEM_H
#define DROPPING_SYSTEM_H

#include "../InventoryItemData.h"
#include "../../game-objects/Player.h"
#include "../../GUI/TextAsset.h"
#include <vector>
#include <iostream>
#include "../../GEV.h"

using namespace GEV;

struct DropItem
{
public:
	InventoryItemData* i; // Just item, nothing more . . .
	Vector2Int p; // position in GLB units
	double currot = 0; // Current rotation
	bool clockdir = true; // Is going in clockwise direction or not
};

/// <summary>
/// Drawing and managing dropped items.
/// MUST be initialized after init of game object manager and player object
/// </summary>
class DroppingSystem
{
public:
	DroppingSystem(Camera* c, Player* pl);
	~DroppingSystem();

	/// <summary>
	/// Drops the item on the ground and add item to drp
	/// </summary>
	/// <param name="item">item's data</param>
	void drop(InventoryItemData* item);

	/// <summary>
	/// Picks up item from the ground and deletes from drp
	/// </summary>
	/// <param name="which">what number from vector shall be picked up</param>
	InventoryItemData* pickUp(size_t which);

	/// <summary>
	/// Updates items
	/// </summary>
	void update();

	/// <summary>
	/// Draws dropped items if any
	/// </summary>
	void draw();

private:

	/// <summary>
	/// Returns new vector position for item dependent from direction and position of player
	/// </summary>
	Vector2Int getNewPosItem();

	/// <summary>
	/// Draw simple item
	/// </summary>
	void drawItem(DropItem* di);

	/// <summary>
	/// Returns the index of table where is free space for item
	/// If returns -1 then there's no free space ;(
	/// </summary>
	int getFreeRoom();

private:
	Camera* c;
	Player* pl;

	FontAsset* font; // Font of numbers for items
	TextAsset* text; // Texto to display numbers

	// nullptr -> none
	// NOT nullptr -> some item
	std::vector<DropItem*> drp; // Dropped items

	SDL_Rect destR;

};

#endif