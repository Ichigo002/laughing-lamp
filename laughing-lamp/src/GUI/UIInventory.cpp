#include "UIInventory.h"
#include "../utility/TextureManager.h"
#include "../utility/KeyboardHandler.h"

UIInventory::UIInventory(Camera* c, InventorySystem* invsys)
	: c(c), invsys(invsys), rsc(2)
{
	default_mod_color = { 255, 255, 255, 200};
	focus_mod_color = { 255, 172, 172 };
	hover_mod_color = { 190, 190, 190 };
	click_mod_color = { 70, 70, 70 };

	begin_point = { 10, 10 };

	bg_alpha = 180;

	size_slot.w = 32;
	size_slot.h = 32;

	marginX_slot = 4;
	marginY_slot = 4;

	gap_between_BarInv = 5;

	padding_item = 10;

	std::string font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf";

	SDL_Color font_asset_color = { 255, 255, 255 };
	amount_font_item = new FontAsset(c->getRender(), font_path, 26, font_asset_color);
	txt_item = new UIText(amount_font_item);

	loadTex();

	isOpened = false;
}

void UIInventory::drawItem(const SDL_Rect* uislot_rect, PSlot slot)
{
	InventoryItemData* item = invsys->getItem(slot);
	if (item == nullptr)
		return;
	if (item->getItemTex() == nullptr)
	{
		item->__setTex(TextureManager::load(c, "items", item->getName() + ".png"));
		if (item->getItemTex() == nullptr)
		{
			std::cout << "UIInventory::drawItem(SDL_Rect*, PSlot): Couldn't load item texture from '" << DEF_PATH_TEX << "items/" << item->getName() << ".png' " << std::endl;
			return;
		}
	}
	SDL_Rect r = *uislot_rect;
	r.x += padding_item;
	r.y += padding_item;
	r.w -= padding_item*2;
	r.h -= padding_item*2;

	c->drawGUI(item->getItemTex(), NULL, &r);

	int stack = item->getSizeStack();

	if (stack == 1)
		return;
	if (stack < 10)
		r.x += 24/2;
	
	txt_item->setText(std::to_string(stack));
	txt_item->setStartingPos(Vector2Int(r.x + r.w / 2, r.y + r.h / 2));
	txt_item->draw();
}

void UIInventory::loadTex()
{
	default_slot_tex = TextureManager::load(c, "ui", "inventory_slot.png");
	focus_slot_tex = TextureManager::load(c, "ui", "inventory_focus_slot.png");
	
	bg_main_tex = TextureManager::load(c, "ui", "inventory_main_bg.png");
	bg_bar_tex = TextureManager::load(c, "ui", "inventory_bar_bg.png");

	SDL_SetTextureBlendMode(default_slot_tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(focus_slot_tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bg_main_tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bg_bar_tex, SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(bg_main_tex, bg_alpha);
	SDL_SetTextureAlphaMod(bg_bar_tex, bg_alpha);
	SDL_SetTextureAlphaMod(default_slot_tex, default_mod_color.a);
	SDL_SetTextureAlphaMod(focus_slot_tex, focus_mod_color.a);

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

		drawItem(&dr, PSlot(x, 0));
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

	for (size_t y = 1; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			dr.x = begin_point.x + marginX_slot * rsc + x * (size_slot.w + marginX_slot) * rsc;
			dr.y = begin_point.y + marginY_slot * rsc * 3 + (size_slot.w + gap_between_BarInv) * rsc + (y-1) * (size_slot.h + marginY_slot) * rsc;

			c->drawGUI(default_slot_tex, NULL, &dr);

			drawItem(&dr, PSlot(x, y));
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

