#ifndef GEV_H
#define GEV_H

#include "utility/Vector2Int.h"
#include "SDL_rect.h"

/// <summary>
/// What is GEV? There's Global Environment Variables. You can here get easy access to almost all important variables
/// </summary>
namespace GEV
{
	//--- Item's settings
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	SDL_Rect	item_size = { 0,0,32,32 }; // Size of items
	int			item_dropped_scale = 1.3; // Scale of dropped item
	int			item_num_font_size = 13; // Size of small numbers of amount in one stack below items
	std::string item_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font fot small nubmers below items

	//--- User Interface
		// UIInventory
		// [ MORE SETTINGS => GUI/UIInventory.cpp ]
		std::string ui_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font for UI
		int         ui_num_font_size = 15; // Size of font in UI
		int			ui_rsc; // Render scale of UI

}

#endif