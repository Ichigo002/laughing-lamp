#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <SDL.h>
#include "../utility/Vector2Int.h"
#include "../utility/Camera.h"

class InventorySystem
{
public:
	InventorySystem(Camera* c);

	/// <summary>
	/// Update for events. For instance: moving items by mouse
	/// </summary>
	void events(SDL_Event* e);

	/// <summary>
	/// Draw UI inventory
	/// </summary>
	void draw();
private:
	Camera* c; // Main camera

	SDL_Rect single_field_rect; // Rect of single field
	SDL_Texture* single_field_tex; // Texture of single field
	SDL_Texture* background_tex; // Texture of background the inventory; nullptr -> none
};

#endif
