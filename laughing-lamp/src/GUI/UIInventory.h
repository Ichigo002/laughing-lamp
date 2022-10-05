#ifndef UI_INVENTORY_H
#define UI_INVENTORY_H

#include <SDL.h>
#include "../inventory/InventorySystem.h"
#include "../utility/Vector2Int.h"
#include "../utility/Camera.h"
#include "UIText.h"

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
	/// Draws the item in GLB units
	/// </summary>
	/// <param name="uislot_rect">rect of drew slot in inventory</param>
	/// <param name="slot">form what slot get item</param>
	void drawItem(const SDL_Rect* uislot_rect, PSlot slot);

	/// <summary>
	/// Detect Collision AABB for mouse [raw screen units]
	/// </summary>
	/// <param name="t">Target who move to touch object</param>
	/// <param name="mpos">mouse position</param>
	/// <returns>On detect returns true</returns>
	bool MOSUI_AABB(const SDL_Rect* t, Vector2Int mpos);

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

	/// <summary>
	/// Draws the hotbar with items
	/// </summary>
	void drawHotbar();

	/// <summary>
	/// Draws the open inventory with items
	/// </summary>
	void drawOpenInventory();

private:
	/* PRIVATE VARIABLES */
	Camera* c; // Main camera
	InventorySystem* invsys; // Main inventory system

	Vector2Int cmos; // Current position of mouse on screen;
	bool isOpened;
	UIText* txt_item; // text to render amounts

	/* SLOTS DESIGN */
	SDL_Color default_mod_color; // active if mouse is not touching a slot
	SDL_Color hover_mod_color;   // active if mouse hovers a slot
	SDL_Color click_mod_color;   // active if mouse click a slot to grab item
	SDL_Color focus_mod_color;   // active if slot is used as current slot in InventorySystem (chosen by 1-9 keys or by scroll)

	SDL_Rect size_slot; // Used only w,h. Specify width and height of slot [Value scaled with rsc]

	SDL_Texture* default_slot_tex;  // texture in every slot 
	SDL_Texture* focus_slot_tex;    // if slot is current slot in InventorySystem (chosen by 1-9 keys or by scroll)

	/* ITEMS DESIGN */

	int padding_item; // Space between border of slot and item
	FontAsset* amount_font_item; // Font asset to display number of items in one slot (small white numbers)

	/* NON INTERACT ELEMENTS */
	SDL_Texture* bg_main_tex; // Texture of main bg if inventory is opened
	SDL_Texture* bg_bar_tex; // Texture of bar if inventory is closed
	int bg_alpha; // Transparent background 0-255

	SDL_Point begin_point; // Point where begins inventory
	int marginX_slot; // size of margin for slot in X [Value scaled with rsc]
	int marginY_slot; // size of margin for slot in Y [Value scaled with rsc]

	int gap_between_BarInv; // Size of gap between foucs bar & content inventory [Value scaled with rsc]

	int rsc; // Render scale of UI
};

#endif
