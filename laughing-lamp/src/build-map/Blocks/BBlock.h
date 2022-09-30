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
	SDL_Rect colliderRect; // Rect of collision if canCollide is true

	SDL_Texture* tex; // Texture of object
	int layer; // layer of rendering if more than one block per position
	float render_scale; // scale of rendering

	std::string getName() { return name; }
	std::string getCat() { return category; }

	bool get_canPlaceover() { return canPlaceover; }
	bool get_canCollide() { return canCollide; }
protected:
	std::string name; // Name of object
	std::string category; // Category of object

	bool canPlaceover; // can other object be placed on this
	bool canCollide; // can this object have collision each other
};

#endif