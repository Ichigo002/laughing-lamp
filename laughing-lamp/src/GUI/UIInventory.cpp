#include "UIInventory.h"
#include "../utility/TextureManager.h"
#include "../utility/KeyboardHandler.h"

UIInventory::UIInventory(Camera* c, InventorySystem* invsys)
	: c(c), invsys(invsys), rsc(2)
{
	default_mod_color = DISABLED_COLOR;
	focus_mod_color = { 255, 172, 172 };
	hover_mod_color = { 190, 190, 190 };
	click_mod_color = { 70, 70, 70 };

	begin_point = { 10, 10 };

	size_slot.w = 32;
	size_slot.h = 32;

	marginX_slot = 4;
	marginY_slot = 4;

	gap_between_BarInv = 5;

	loadTex();

	isOpened = false;
}
// TODO 5 Resourcepacks manager & textures. And get textures by category and name
void UIInventory::loadTex()
{
	default_slot_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_slot.png");
	focus_slot_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_focus_slot.png");
	
	bg_main_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_main_bg.png");
	bg_bar_tex = TextureManager::load(c->getRender(), "assets/textures/ui/inventory_bar_bg.png"); 

	SDL_SetTextureColorMod(default_slot_tex, default_mod_color.r, default_mod_color.g, default_mod_color.b);
	SDL_SetTextureColorMod(focus_slot_tex, focus_mod_color.r, focus_mod_color.g, focus_mod_color.b);
}

void UIInventory::open()
{
	isOpened = true;
}

void UIInventory::close()
{
	isOpened = false;
}

void UIInventory::drawHotbar()
{
	SDL_Rect dr;

	// draw background
	dr.x = begin_point.x;
	dr.y = begin_point.y;
	dr.w = marginX_slot * rsc + NO_FIELDS_X * (size_slot.w + marginX_slot) * rsc;
	dr.h = marginY_slot * rsc * 2 + size_slot.h * rsc;

	c->drawGUI(bg_bar_tex, NULL, &dr);

	// draw slots
	dr.w = size_slot.w * rsc;
	dr.h = size_slot.h * rsc;
	for (size_t x = 0; x < NO_FIELDS_X; x++)
	{
		dr.x = begin_point.x + marginX_slot * rsc + x * (size_slot.w + marginX_slot) * rsc;
		dr.y = begin_point.y + marginY_slot * rsc;

		c->drawGUI(default_slot_tex, NULL, &dr);

		//c->drawGUI(invsys->getItem(PSlot(x, 0))->)
	}
}

void UIInventory::drawOpenInventory()
{
	if (!isOpened)
		return;
	SDL_Rect dr;
	// draw background
	dr.x = begin_point.x;
	dr.y = begin_point.x + marginY_slot * rsc * 2 + (size_slot.h + gap_between_BarInv) * rsc;
	dr.w = marginX_slot * rsc + NO_FIELDS_X * (size_slot.w + marginX_slot) * rsc;
	dr.h = marginY_slot * rsc + (NO_FIELDS_Y-1) * (size_slot.h + marginY_slot) * rsc;

	c->drawGUI(bg_main_tex, NULL, &dr);

	//draw inventory

	dr.w = size_slot.w * rsc;
	dr.h = size_slot.h * rsc;

	for (size_t y = 0; y < NO_FIELDS_Y-1; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			dr.x = begin_point.x + marginX_slot * rsc + x * (size_slot.w + marginX_slot) * rsc;
			dr.y = begin_point.y + marginY_slot * rsc * 3 + (size_slot.w + gap_between_BarInv) * rsc + y * (size_slot.h + marginY_slot) * rsc;

			c->drawGUI(default_slot_tex, NULL, &dr);
		}
	}
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
	drawHotbar();

	drawOpenInventory();
}

