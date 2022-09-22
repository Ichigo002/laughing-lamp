#ifndef BWALL_H
#define BWALL_H

#include "../../utility/Vector2Int.h"
#include <SDL.h>
#include "BBlock.h"

class BWall : public BBlock
{
public:
	explicit BWall();
	~BWall();

	/* Load textures */
	void loadTex(SDL_Renderer* r) override;

	/* Method called every time. You can put there different move algorithms etc.*/
	void update() override;

	/*Handle all events for this object*/
	void events(SDL_Event* eve) override;

	SDL_Rect srcR; // Rect of source
	SDL_Rect destR; // Rect on the screen relative to size of Hex
	SDL_Texture* tex; // Texture of object

	std::string getName() { return name; }
	std::string getCat() { return category; }
protected:
	std::string name; // Name of object
	std::string category; // Category of object

};

#endif