#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <iostream>

/*Abstract class*/
class GameObject
{
public:
	GameObject();
	~GameObject();

	/* On start of program the method init once the renderer*/
	virtual void initRenderer(SDL_Renderer* r);
	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update();
	/* Called on every global draw to display on screen */
	virtual void draw();
	/* Returns the tagname of object. */
	std::string getTag() { return tagname;  }

protected:
	SDL_Renderer* render;
	SDL_Texture* tex;
	SDL_Rect srcR, destR;
	std::string tagname;

};

#endif
