#ifndef BUILD_MAP_H
#define BUILD_MAP_H

#include <iostream>
#include <vector>
#include "SDL.h"
#include "../utility/Camera.h"
#include "../game-objects/GameObjectManager.h"
#include "../inventory/InventoryItemData.h"

/// <summary>
/// Struct with item and needed values only if item must be built
/// </summary>
struct Block
{
	InventoryItemData* item; // original item
	Vector2Int lcl; // position of block in LCL units
};

class BuildMap
{
public:
	BuildMap(Camera* c, GameObjectManager* gom);
	~BuildMap();

	/// <summary>
	/// Place on map item as object where cursor is
	/// </summary>
	/// <param name="item">item to place</param>
	/// <returns>
	/// 0 on success
	/// -1 on access denied by item [lack of DT_BUILDABLE]
	/// -2 on invalid item or nullptr
	/// </returns>
	int settleCursor(InventoryItemData* item);

	/// <summary>
	/// Destroy block where cursor is
	/// </summary>
	/// <returns>
	/// Nullptr if in position of cursor is nothing
	/// Item if object has destroyed
	/// </returns>
	InventoryItemData* unsettleCursor();

	/// <summary>
	/// Updates all collision between GameObjectManager's objects and buildmap's blocks
	/// </summary>
	void fixedUpdate();

	/// <summary>
	/// Draws whole map of blocks
	/// </summary>
	void draw();

private:
	/// <summary>
	/// Pushes new block on the map
	/// </summary>
	/// <param name="b">block to push</param>
	void pushBlock(Block* b);

	/// <summary>
	/// Pops block from map by LCL position
	/// </summary>
	/// <param name="lclp">position in LCL units</param>
	/// <returns>
	/// Block* on success
	/// Nullptr on fail
	/// </returns>
	Block* popBlockByLCL(Vector2Int lclp);

	/// <summary>
	/// Draws single block of map
	/// </summary>
	/// <param name="b">block to draw data</param>
	void drawBlock(Block* b);

private:
	Camera* c;
	GameObjectManager* gom;

	std::vector<Block*> map_block; // vector of blocks built on map
	SDL_Rect destR; // Rect of drawing single block

};

#endif
