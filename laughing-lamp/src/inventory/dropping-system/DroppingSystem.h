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
	double rot_time = 0.5f; // Current rotation time
	bool backdir = false; // direction of animation
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
	/// Executed in inventory system.
	/// If player tries pick up any item, item will be returned by method
	/// At the same time item is removed from dropping system
	/// </summary>
	InventoryItemData* tryPickUp();

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