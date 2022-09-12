#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Vector2Int.h"

/* Main class to draw Objects depended on current position of Camera */
class Camera
{
public:
	Camera(SDL_Renderer* r, int screen_w, int screen_h);
	~Camera();

	/* Returns vector of move relative to the camera */
	Vector2Int getMoveSet();
	/* Returns the vector with Width as X & Height as Y of screen*/
	Vector2Int getWHScreen();

	/* Returns the renderer of game */
	SDL_Renderer* getRender();

	/* Draw the object which is active in the game world  */
	int drawDynamic(SDL_Texture* texture, const SDL_Rect* srcR, SDL_Rect* destR);

	/* Draw the object who do not get involved into moving by camera */
	int drawStatic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR);

	/* Draw GUI */
	int drawGUI(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR);

	void set(int x, int y);
	void set(Vector2Int v);

	void move(int x, int y);
	void move(Vector2Int v);
private:
	SDL_Rect cam;
	SDL_Renderer* render;
};

#endif

