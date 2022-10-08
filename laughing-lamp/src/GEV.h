#ifndef GEV_H
#define GEV_H

//#include "utility/Vector2Int.h"
#include "SDL_rect.h"
#include "SDL_render.h"

/// What is __declspec(selectany)??
/// This tells the linker to pick one definition for use by all external references and to discard the rest. [VS2019 Linker Tools Error LNK2005]
#define DSPEC __declspec(selectany)

using std::string;

/// <summary>
/// What is GEV? There's Global Environment Variables. You can here get easy access to almost all important variables
/// </summary>
namespace GEV
{
//--- Item's settings
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	DSPEC SDL_Rect	item_size = { 0, 0, 32, 32 }; // Size of items
	DSPEC int		item_dropped_rsc = 1.3; // Scale of dropped item
	DSPEC int		item_pt_font_size = 13; // Size of small numbers of amount in one stack below items
	DSPEC string    item_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font fot small nubmers below items
	DSPEC SDL_Color item_font_color = { 255, 255, 255 }; // Font color of numbers below items

//--- User Interface
	// UIInventory
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	DSPEC string ui_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font for UI
	DSPEC int    ui_pt_font_size = 15; // Size of font in UI
	DSPEC int    ui_rsc = 2; // Render scale of UI

}

#endif