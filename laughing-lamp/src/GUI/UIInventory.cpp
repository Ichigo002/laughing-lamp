#include "UIInventory.h"
#include "../utility/TextureManager.h"
#include "../utility/KeyboardHandler.h"

UIInventory::UIInventory(Camera* c, InventorySystem* invsys)
	: c(c), invsys(invsys)
{
	default_mod_color = { 255, 255, 245, 210};
	focus_mod_color = { 255, 255, 255, 200 };
	hover_mod_color = { 150, 170, 230, 200 };

	begin_point = { 10, 10 };

	bg_alpha = 180;

	size_slot.w = 28;
	size_slot.h = 28;

	marginX_slot = 2;
	marginY_slot = 2;

	gap_between_BarInv = 5;
	focus_slot_x = 0;

	padding_item = 5;
	offest_moving_item.set(-5, -5);

	loadTex();

	isOpened = false;
}

void UIInventory::drawItem(const SDL_Rect* uislot_rect, PSlot slot)
{
	drawItem(uislot_rect, invsys->getItem(slot));
}

void UIInventory::drawItem(const SDL_Rect* uislot_rect, InventoryItemData* item)
{
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
	r.x += padding_item * ui_rsc;
	r.y += padding_item * ui_rsc;
	r.w -= padding_item * 2 * ui_rsc;
	r.h -= padding_item * 2 * ui_rsc;

	c->drawGUI(item->getItemTex(), NULL, &r);

	int stack = item->getSizeStack();

	if (stack == 1)
		return;
	if (stack < 10)
		r.x += item_pt_font_size *ui_rsc / 2;

	txt_item->setText(std::to_string(stack));
	txt_item->setStartingPos(Vector2Int(r.x + r.w / 2, r.y + r.h / 2));
	txt_item->draw();
}

void UIInventory::drawReadySlot(SDL_Rect* destR, const PSlot slot)
{
	if (slot.y == 0 && slot.x == focus_slot_x)
	{
		if (!hover_slot.isNeg() && hover_slot == slot)
		{
			SDL_SetTextureAlphaMod(focus_slot_tex, hover_mod_color.a);
			SDL_SetTextureColorMod(focus_slot_tex, hover_mod_color.r, hover_mod_color.g, hover_mod_color.b);
		}
		else
		{
			SDL_SetTextureAlphaMod(focus_slot_tex, focus_mod_color.a);
			SDL_SetTextureColorMod(focus_slot_tex, focus_mod_color.r, focus_mod_color.g, focus_mod_color.b);
		}
		c->drawGUI(focus_slot_tex, NULL, destR);
		drawItem(destR, slot);
		return;
	}

	if (!hover_slot.isNeg() && hover_slot == slot)
	{
		SDL_SetTextureAlphaMod(default_slot_tex, hover_mod_color.a);
		SDL_SetTextureColorMod(default_slot_tex, hover_mod_color.r, hover_mod_color.g, hover_mod_color.b);
	}
	else
	{
		SDL_SetTextureAlphaMod(default_slot_tex, default_mod_color.a);
		SDL_SetTextureColorMod(default_slot_tex, default_mod_color.r, default_mod_color.g, default_mod_color.b);
	}

	c->drawGUI(default_slot_tex, NULL, destR);

	drawItem(destR, slot);
}

void UIInventory::loadTex()
{
	default_slot_tex = TextureManager::load(c, "ui", "inventory_slot.png");
	focus_slot_tex = TextureManager::load(c, "ui", "inventory_focus_slot.png");
	
	bg_main_tex = TextureManager::load(c, "ui", "inventory_main_bg.png");
	bg_bar_tex = TextureManager::load(c, "ui", "inventory_hotbar_bg.png");

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
	dr.w = marginX_slot * ui_rsc + NO_FIELDS_X * (size_slot.w + marginX_slot) * ui_rsc;
	dr.h = marginY_slot * ui_rsc * 2 + size_slot.h * ui_rsc;

	c->drawGUI(bg_bar_tex, NULL, &dr);

	// draw slots
	dr.w = size_slot.w * ui_rsc;
	dr.h = size_slot.h * ui_rsc;
	for (size_t x = 0; x < NO_FIELDS_X; x++)
	{
		dr.x = begin_point.x + marginX_slot * ui_rsc + x * (size_slot.w + marginX_slot) * ui_rsc;
		dr.y = begin_point.y + marginY_slot * ui_rsc;

		drawReadySlot(&dr, PSlot(x, 0));
	}
}

void UIInventory::drawOpenInventory()
{
	if (!isOpened)
		return;
	SDL_Rect dr;
	// draw background
	dr.x = begin_point.x;
	dr.y = begin_point.x + marginY_slot * ui_rsc * 2 + (size_slot.h + gap_between_BarInv) * ui_rsc;
	dr.w = marginX_slot * ui_rsc + NO_FIELDS_X * (size_slot.w + marginX_slot) * ui_rsc;
	dr.h = marginY_slot * ui_rsc + (NO_FIELDS_Y-1) * (size_slot.h + marginY_slot) * ui_rsc;

	c->drawGUI(bg_main_tex, NULL, &dr);

	//draw inventory

	dr.w = size_slot.w * ui_rsc;
	dr.h = size_slot.h * ui_rsc;

	for (size_t y = 1; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			dr.x = begin_point.x + marginX_slot * ui_rsc + x * (size_slot.w + marginX_slot) * ui_rsc;
			dr.y = begin_point.y + marginY_slot * ui_rsc * 3 + (size_slot.w + gap_between_BarInv) * ui_rsc + (y-1) * (size_slot.h + marginY_slot) * ui_rsc;

			drawReadySlot(&dr, PSlot(x, y));
		}
	}
}

void UIInventory::drawMovingItem()
{
	if (invsys->move_getItem() == nullptr)
		return;

	SDL_Rect dr;
	dr.w = size_slot.w * ui_rsc;
	dr.h = size_slot.h * ui_rsc;
	dr.x = c->getMouse().x + offest_moving_item.x;
	dr.y = c->getMouse().y + offest_moving_item.y;

	drawItem(&dr, invsys->move_getItem());
}

void UIInventory::events(SDL_Event* e)
{
	// Closes different action for Escape
	if (KeyboardHandler::pressedKey(SDLK_ESCAPE, e) && !invsys->move_ready())
		close();
	if (KeyboardHandler::pressedKey(SDLK_ESCAPE, e) && invsys->move_ready())
		invsys->move_cancel();

	/// CTRL events
	if (KeyboardHandler::pressedKey(SDLK_LCTRL, e))
		holdCTRL = true;
	if (KeyboardHandler::releasedKey(SDLK_LCTRL, e))
		holdCTRL = false;


	if (KeyboardHandler::pressedKey(SDLK_TAB, e))
	{
		if (isOpened)
			close();
		else
			open();
	}
	hover_slot.setNeg();
	
	//Focus keys 1-9;
	if(e->type == SDL_KEYDOWN)
		switch (e->key.keysym.sym)
		{
		case SDLK_1:
			focus_slot_x = 0;
			break;
		case SDLK_2:
			focus_slot_x = 1;
			break;
		case SDLK_3:
			focus_slot_x = 2;
			break;
		case SDLK_4:
			focus_slot_x = 3;
			break;
		case SDLK_5:
			focus_slot_x = 4;
			break;
		case SDLK_6:
			focus_slot_x = 5;
			break;
		case SDLK_7:
			focus_slot_x = 6;
			break;
		case SDLK_8:
			focus_slot_x = 7;
			break;
		case SDLK_9:
			focus_slot_x = 8;
			break;
		case SDLK_0:
			focus_slot_x = 9;
			break;
		}

	// Limit of keys
	if (focus_slot_x > NO_FIELDS_X-1)
		focus_slot_x = NO_FIELDS_X-1;

	if (e->type == SDL_MOUSEWHEEL)
	{
		if (e->wheel.y > 0) // Scroll up
		{
			focus_slot_x++;
		}
		else if (e->wheel.y < 0) // Scroll down
		{
			focus_slot_x--;
		}
	}

	//Limit of scroll
	if (focus_slot_x < 0)
		focus_slot_x = NO_FIELDS_X - 1;

	if (focus_slot_x > NO_FIELDS_X - 1)
		focus_slot_x = 0;

	if (KeyboardHandler::pressedKey(SDLK_q, e))
	{
		invsys->drop(PSlot(focus_slot_x, 0), holdCTRL ? -1 : 1);
	}

	//Open inventory
	if (!isOpened)
		return;

	Vector2Int mp = c->getMouse();
	SDL_Rect dr;

	dr.w = size_slot.w * ui_rsc;
	dr.h = size_slot.h * ui_rsc;

	for (size_t y = 0; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			// Sets slots sizes
			if (y == 0)
			{
				dr.y = begin_point.y + marginY_slot * ui_rsc;
			}
			else
			{
				dr.y = begin_point.y + marginY_slot * ui_rsc * 3 + (size_slot.w + gap_between_BarInv) * ui_rsc + (y - 1) * (size_slot.h + marginY_slot) * ui_rsc;
			}
			dr.x = begin_point.x + marginX_slot * ui_rsc + x * (size_slot.w + marginX_slot) * ui_rsc;

			// Check if cursor touch slot
			if (mp.x > dr.x && mp.x < dr.x + dr.w && mp.y < dr.y + dr.h && mp.y > dr.y)
			{
				// Hover system
				hover_slot.unsetNeg();
				hover_slot = PSlot(x, y);

				// Moving algorithm
				if (e->type == SDL_MOUSEBUTTONDOWN)
				{
					if (invsys->move_ready())
					{
						invsys->move_exec(PSlot(x, y));
					}
					else
					{
						if (e->button.button == 1) // left
							invsys->move_init(PSlot(x, y), -1);
						if (e->button.button == 3) // right
							invsys->move_init(PSlot(x, y), invsys->getItem(PSlot(x, y))->getSizeStack() / 2);
						if(e->button.button == 2)
							invsys->move_init(PSlot(x, y), 1);
					}
				}
				//Drops
				else if (KeyboardHandler::pressedKey(SDLK_q, e))
				{
					invsys->drop(PSlot(x, y), holdCTRL ? -1 : 1);
				}
			}
			// TODO 3 cursor with item is out of inventory and drop
			// 
			//else if ()
			//{
			//
			//}
		}
	}
}

void UIInventory::update()
{
	if (old_rsc != ui_rsc)
	{
		old_rsc = ui_rsc;
		amount_font_item = new FontAsset(c->getRender(), item_font_path, item_pt_font_size * ui_rsc, item_font_color);
		txt_item = new UIText(amount_font_item);
	}
}

void UIInventory::draw()
{
	drawHotbar();

	drawOpenInventory();

	drawMovingItem();
}