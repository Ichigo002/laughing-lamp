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
//--- Texture Manager
	DSPEC string txm_resourcepack = "hexpack"; // Resourcepack name
	// default path is: .../resourcepacks/default/
	// TODO 2 in future add to every resourcepacks meta data file with size of textures

//--- Inventory System settings

	// Number of rows & columns in inventory
#define NO_FIELDS_X 6 // MAX recommended size is max 10 because, above 10 there's no support for keys 1-9
#define NO_FIELDS_Y 5
	DSPEC int    invsys_max_stacking = 32; // Maximal size of single stack in inventory

//--- Player settings
	DSPEC float  player_walk_speed = 2.6; // Walk speed
	DSPEC float  player_run_speed = 4.3; // Run speed

//--- Items settings
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	DSPEC rect	 item_size = { 0, 0, 28, 32 }; // Size of items
	DSPEC vec2i  item_dropped_no_offset(-4, -4); // Offset of number stack on dropped item
	DSPEC float	 item_dropped_rsc = 1.45; // Scale of dropped item
	DSPEC int	 item_pt_font_size = 12; // Size of small numbers of amount in one stack below items
	DSPEC string item_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font fot small nubmers below items
	DSPEC color  item_font_color = { 255, 255, 255 }; // Font color of numbers below items

//--- User Interface settings
	// UIInventory
	// [ MORE SETTINGS => GUI/UIInventory.cpp ]
	DSPEC string ui_font_path = "assets/fonts/Gemunu/GemunuLibre-Bold.ttf"; // Path to font for UI
	DSPEC int    ui_pt_font_size = 15; // Size of font in UI
	DSPEC int    ui_rsc = 2; // Render scale of UI
	// TODO 1 Future animation of opening animation
	DSPEC bool   ui_inv_anim_enabled = true; // Animation of moving inventory enabled
	DSPEC dbl    ui_inv_anim_time = 10000; // Length of animation for opening inventory [miliseconds]

//--- Map settings
	DSPEC int   hexmap_chunk_size = 16; // Width and height of chunk on hexmap // Size must be dividable by 2
	DSPEC int   hexmap_generate_edge_offset = 2000; // Extra offset for bug generating
	DSPEC float hexmap_noise_scale = .3f; // Scale of perlin noise while it's generating
	#define HEX_WIDTH 28
	#define HEX_HEIGHT 32
	#define MAP_RENDER_SCALE 2
	#define RATIOHEX_H .75f // ratio of height to width

//--- DroppingSystem settings
	DSPEC vec2i dropsys_spawn_offset_lt(50, 50); // Distacne between player and spawning object at left top x y
	DSPEC vec2i dropsys_spawn_offset_rb(0, 25); // Distacne between player and spawning object at right bottom x y
	DSPEC dbl   dropsys_rot_min = -10; // min angle of rotation
	DSPEC dbl   dropsys_rot_max = 10; // max angle of rotation
	DSPEC dbl   dropsys_rot_time = 1750; // length of animation [miliseconds]
}

#endif