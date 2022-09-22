#ifndef BBLOCK_H
#define BBLOCK_H

#include "../../utility/Vector2Int.h"
#include <SDL.h>

/// <summary>
/// Build Block
/// </summary>
class BBlock
{
public:
	BBlock() {}
	~BBlock() {}

	/* Load textures */
	virtual void loadTex(SDL_Renderer* r) = 0;

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update() = 0;

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve) = 0;

	SDL_Rect srcR; // Rect of source
	SDL_Rect destR; // Rect on the screen relative to size of Hex
	SDL_Texture* tex; // Texture of object

	std::string getName() { return name; }
	std::string getCat() { return category; }
protected:
	float render_scale; // scale of rendering
	std::string name; // Name of object
	std::string category; // Category of object

};

#endif