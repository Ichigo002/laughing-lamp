#ifndef GEV_H
#define GEV_H

#include "utility/Vector2Int.h"
#include "SDL_rect.h"
#include "SDL_render.h"

/// What is __declspec(selectany)??
/// This tells the linker to pick one definition for use by all external references and to discard the rest. [VS2019 Linker Tools Error LNK2005]
#define DSPEC __declspec(selectany)

#define vec2i Vector2Int
#define rect SDL_Rect
#define color SDL_Color
#define dbl double

using std::string;

/// <summary>
/// What is GEV? There's Global Environment Variables. You can here get easy access to almost all important variables
/// </summary>
namespace GEV
{
//--- Inventory System settings

	// Number of rows & columns in inventory
#define NO_FIELDS_X 6 // MAX recommended size is max 10 because, above 10 there's no support for keys 1-9
#define NO_FIELDS_Y 5
	DSPEC int invsys_max_stacking = 32; // Maximal size of single stack in inventory

//--- Items settings
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	DSPEC rect	 item_size = { 0, 0, 32, 32 }; // Size of items
	DSPEC vec2i  item_dropped_no_offset(-4, -4); // Offset of number stack on dropped item
	DSPEC int	 item_dropped_rsc = 1.3; // Scale of dropped item
	DSPEC int	 item_pt_font_size = 12; // Size of small numbers of amount in one stack below items
	DSPEC string item_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font fot small nubmers below items
	DSPEC color  item_font_color = { 255, 255, 255 }; // Font color of numbers below items

//--- User Interface settings
	// UIInventory
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	DSPEC string ui_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font for UI
	DSPEC int    ui_pt_font_size = 15; // Size of font in UI
	DSPEC int    ui_rsc = 2; // Render scale of UI

//--- HexMap settings
	DSPEC int   hexmap_chunk_size = 16; // Width and height of chunk on hexmap // Size must be dividable by 2
	DSPEC int   hexmap_generate_edge_offset = 2000; // Extra offset for bug generating
	DSPEC float hexmap_noise_scale = .3f; // Scale of perlin noise while it's generating
//--- DroppingSystem settings
	DSPEC vec2i dropsys_spawn_offset_lt(50, 50); // Distacne between player and spawning object at left top x y
	DSPEC vec2i dropsys_spawn_offset_rb(-5, 25); // Distacne between player and spawning object at right bottom x y
	DSPEC dbl   dropsys_rot_min = -10; // min angle of rotation
	DSPEC dbl   dropsys_rot_max = 10; // max angle of rotation
	DSPEC dbl   dropsys_rot_time = 2000; // miliseconds of animation
}

#endif