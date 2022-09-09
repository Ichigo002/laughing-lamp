#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <iostream>

/*Abstract class*/
class GameObject
{
public:
	GameObject(SDL_Renderer* r) 
	{
		render = r;
	}
	~GameObject() {}

	/* Here you can load all needed textures*/
	virtual void loadTexture() {}

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update() {}

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve) {}

	/* Called on every global draw to display on screen */
	virtual void draw() {}

	/* Returns the tagname of object. */
	std::string getTag() { return tagname;  }

protected:
	SDL_Renderer* render;
	SDL_Texture* tex;
	SDL_Rect srcR, destR;
	std::string tagname;
	float renderingScale;
};

#endif
