#include "UIInventory.h"
#include "../utility/TextureManager.h"
#include "../utility/KeyboardHandler.h"

UIInventory::UIInventory(Camera* c, InventorySystem* invsys)
	: c(c), invsys(invsys), rsc(2)
{
	default_mod_color = DISABLED_COLOR;
	hover_mod_color = { 190, 190, 190 };
	focus_mod_color = { 255, 172, 172 };
	click_mod_color = { 70, 70, 70 };

	begin_point = { 10, 10 };

	size_slot.w = 32;
	size_slot.h = 32;

	marginX_slot = 4;
	marginY_slot = 4;

	loadTex();

	isOpened = false;
}
// TODO 5 Resourcepacks manager & textures. And get textures by category and name
void UIInventory::loadTex()
{
	default_slot_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_slot.png");
	//focus_slot_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_focus_slot.png");
	
	//bg_main_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_main_bg.png");
	//bg_bar_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_bar_bg.png"); 
	std::cout << SDL_GetError() << std::endl;
}

void UIInventory::open()
{
	isOpened = true;
}

void UIInventory::close()
{
	isOpened = false;
}

void UIInventory::events(SDL_Event* e)
{
	if (KeyboardHandler::pressedKey(SDLK_TAB, e))
	{
		if (isOpened)
			close();
		else
			open();
	}
	
}

void UIInventory::update()
{
}

void UIInventory::draw()
{
	//Inventory closed & opened Bar
	SDL_Rect dr;
	dr.w = size_slot.w * rsc;
	dr.h = size_slot.h * rsc;

	for (size_t x = 0; x < NO_FIELDS_X; x++)
	{
		dr.x = begin_point.x + marginX_slot * rsc + x * (size_slot.w + marginX_slot) * rsc;
		dr.y = begin_point.y + marginY_slot * rsc;

		c->drawGUI(default_slot_tex, NULL, &dr);
	}

	// Inventory opened
	if (!isOpened)
		return;
}

