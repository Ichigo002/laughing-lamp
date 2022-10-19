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
	int layer;
};

class BuildMap
{
public:
	BuildMap(Camera* c, GameObjectManager* gom);
	~BuildMap();

	/// <summary>
	/// Place on map item as object where cursor is.
	/// Method copies the item and reset stakc of item to 0. [1 element itself]
	/// </summary>
	/// <param name="item">item to place</param>
	/// <returns>
	/// 0 on success
	/// -1 on access denied by item [lack of required attributes]
	/// -2 on invalid item or nullptr
	/// </returns>
	int settleCursor(InventoryItemData* item);

	/// <summary>
	/// Destroy block where cursor is
	/// </summary>
	/// <param name="ipos">returns to pointer last alive position before die</param>
	/// <returns>
	/// Nullptr if in position of cursor is nothing
	/// Item if object has destroyed
	/// </returns>
	InventoryItemData* unsettleCursor(Vector2Int* ipos);

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
	/// Finds topest layer in LCL position
	/// </summary>
	/// <param name="lclp">LCL position</param>
	/// <returns>
	/// top, highest layer
	/// if not found, returns -1
	/// </returns>
	int getTopLayerByLCL(Vector2Int lclp);

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
	int top_layer; // top layer

};

#endif
