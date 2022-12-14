#ifndef UI_INVENTORY_H
#define UI_INVENTORY_H

#include <SDL.h>
#include "../inventory/InventorySystem.h"
#include "../utility/Vector2Int.h"
#include "../utility/Camera.h"
#include "TextAsset.h"
#include <iostream>
#include "../GEV.h"

#define DISABLED_COLOR {255, 255, 255, 255};

using namespace GEV;

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
	/// Draws the item in GLB units
	/// </summary>
	/// <param name="uislot_rect">rect of drew slot in inventory</param>
	/// <param name="item">item to display</param>
	void drawItem(const SDL_Rect* uislot_rect, InventoryItemData* item);


	/// <summary>
	/// Draw ready to use slot in inventory
	/// </summary>
	/// <param name="destR">size & position on the screen</param>
	/// <param name="slot">which slot should be drown</param>
	void drawReadySlot(SDL_Rect* destR, PSlot slot);

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

	/// <summary>
	/// Draws the item next to teh cursor during moving item
	/// </summary>
	void drawMovingItem();

private:
	/* PRIVATE VARIABLES */
	Camera* c; // Main camera
	InventorySystem* invsys; // Main inventory system

	bool isOpened; // is inventory opened
	bool holdCTRL; // is holded ctrl by finger?
	TextAsset* txt_item; // text to render amounts
	PSlot hover_slot; // currently hovered slot by mouse
	int focus_slot_x; // currently focused slot by keys or scroll
	float old_rsc; // old value of rsc to check is value changed for fonts

	/* SLOTS DESIGN */
	SDL_Color default_mod_color; // active if mouse is not touching a slot
	SDL_Color hover_mod_color;   // active if mouse hovers a slot
	SDL_Color focus_mod_color;   // active if slot is used as current slot in InventorySystem (chosen by 1-9 keys or by scroll)

	SDL_Rect size_slot; // Used only w,h. Specify width and height of slot [Value scaled with rsc]

	SDL_Texture* default_slot_tex;  // texture in every slot 
	SDL_Texture* focus_slot_tex;    // if slot is current slot in InventorySystem (chosen by 1-9 keys or by scroll)

	/* ITEMS DESIGN */

	Vector2Int offest_moving_item; // Offset of item which is moving. This display item next ot the cursor
	int padding_item; // Space between border of slot and item [Value scaled with rsc] 
	FontAsset* amount_font_item; // Font asset to display number of items in one slot (small white numbers) [Value scaled with rsc [size]]

	/* NON INTERACT ELEMENTS */
	SDL_Texture* bg_main_tex; // Texture of main bg if inventory is opened
	SDL_Texture* bg_bar_tex; // Texture of bar if inventory is closed
	int bg_alpha; // Transparent background 0-255

	SDL_Point begin_point; // Point where begins inventory
	int marginX_slot; // size of margin for slot in X [Value scaled with rsc]
	int marginY_slot; // size of margin for slot in Y [Value scaled with rsc]

	int gap_between_BarInv; // Size of gap between foucs bar & content inventory [Value scaled with rsc]
};

#endif
