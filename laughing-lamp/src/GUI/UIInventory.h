#ifndef UI_INVENTORY_H
#define UI_INVENTORY_H

#include <SDL.h>
#include "../inventory/InventorySystem.h"
#include "../utility/Vector2Int.h"
#include "../utility/Camera.h"

#define DISABLED_COLOR {255, 255, 255};

class UIInventory
{
public:
	UIInventory(Camera* c, InventorySystem* invsys);

	/// <summary>
	/// Update for events. For instance: moving items by mouse
	/// </summary>
	void events(SDL_Event* e);

	/// <summary>
	/// Updates animations
	/// </summary>
	void update();

	/// <summary>
	/// Draw UI inventory
	/// </summary>
	void draw();

private:
	/// <summary>
	/// Load all necessary textures & sets the rects
	/// </summary>
	void loadTex();

	/// <summary>
	/// Opens the inventory & starts the animation
	/// </summary>
	void open();

	/// <summary>
	/// Closes the inventory & starts the animation
	/// </summary>
	void close();

private:
	/* PRIVATE VARIABLES */
	Camera* c; // Main camera
	InventorySystem* invsys; // Main inventory system

	bool isOpened;

	/* SLOTS DESIGN */
	SDL_Color default_mod_color; // active if mouse is not touching a slot
	SDL_Color hover_mod_color;   // active if mouse hovers a slot
	SDL_Color click_mod_color;   // active if mouse click a slot to grab item
	SDL_Color focus_mod_color;   // active if slot is used as current slot in InventorySystem (chosen by 1-9 keys or by scroll)

	SDL_Rect size_slot; // Used only w,h. Specify width and height of slot

	SDL_Texture* default_slot_tex;  // texture in every slot 
	SDL_Texture* focus_slot_tex;    // if slot is current slot in InventorySystem (chosen by 1-9 keys or by scroll)

	/* NON INTERACT ELEMENTS */
	SDL_Texture* bg_main_tex; // Texture of main bg if inventory is opened
	SDL_Texture* bg_bar_tex; // Texture of bar if inventory is closed

	SDL_Point begin_point; // Point where begins inventory
	int marginX_slot; // size of margin for slot in X
	int marginY_slot; // size of margin for slot in Y

	int rsc; // Render scale of UI
};

#endif
