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
	/// <param name="only_in_viewport">If true then texture is rendered only when object is in viewport</param>
	int drawDynamic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR, bool only_in_viewport = true);

	/* Draw the object who do not get involved into moving by camera */
	int drawStatic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR);

	/* Draw GUI */
	int drawGUI(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR);

	void set(int x, int y);
	void set(Vector2Int v);

	void move(int x, int y);
	void move(Vector2Int v);

	Vector2Int getPos() { return Vector2Int(cam.x, cam.y); }

	bool isIntoViewport(const SDL_Rect* rect);
private:
	SDL_Rect cam;
	SDL_Renderer* render;

	int extra_offset; // additionl field where objects are rendered
};

#endif

