#ifndef BUILD_MAP_H
#define BUILD_MAP_H

#include <iostream>
#include "SDL.h"
#include "../utility/Camera.h"
#include "../game-objects/GameObjectManager.h"
#include "../inventory/InventoryItemData.h"

class BuildMap
{
public:
	BuildMap(Camera* c, GameObjectManager* gom);
	~BuildMap();

	int settleWithCursor

private:

private:
	Camera* c;
	
};

#endif
