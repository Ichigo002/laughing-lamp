#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Vector2Int.h"

#define HEX_WIDTH 28
#define HEX_HEIGHT 32
#define MAP_RENDER_SCALE 2
#define RATIOHEX_H .75f // ratio of hegiht adn width

/* Main class to draw Objects depended on current position of Camera */
class Camera
{
public:
	Camera(SDL_Renderer* r, int sw, int sh);
	~Camera();

	/* Returns vector of move relative to the camera */
	Vector2Int getMoveSet();
	/* Returns the vector with Width as X & Height as Y of screen*/
	Vector2Int getWHScreen();

	/* Returns the renderer of game */
	SDL_Renderer* getRender();

	/* Translates the current mouse position to GLB units */
	Vector2Int translateMouseToGLB();

	/* Translate GLB units into Screen units*/
	Vector2Int translateGLBToScreen(Vector2Int v);

	/* Translate Screen units into GLb units*/
	Vector2Int translateScreenToGLB(Vector2Int v);

	/* Returns the raw position of mouse on the screen*/
	Vector2Int getMouse();

	/* Draw the object which is active in the game world  */
	/* Draw in the GLB units*/
	/// <param name="only_in_viewport">If true then texture is rendered only when object is in viewport</param>
	int drawDynamic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR, bool only_in_viewport = true);

	/* Draw the object who do not get involved into moving by camera */
	/* Draw in the Screen units*/
	int drawStatic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR);

	/* Draw GUI */
	int drawGUI(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR);

	/*set position of camera from CENTER in GLB units*/
	void set(int x, int y);
	void set(Vector2Int v);

	/*move the camera in GLB units*/
	void move(int x, int y);
	void move(Vector2Int v);

    /* Converts the GLB position into LCL position */
    Vector2Int convertGLB_LCL(Vector2Int pos);

	/* Converts the GLB position into the build blocks position */
    Vector2Int convertGLB_BBL(Vector2Int pos);

    /* Converts the LCL position into GLB position */
    Vector2Int convertLCL_GLB(Vector2Int pos);

	/* Converts the BBL position into GLB position*/
	Vector2Int convertBBL_GLB(Vector2Int pos);

	void update(SDL_Event* eve);

	/* Get current position of camera*/
	inline Vector2Int getPos() { return Vector2Int(cam.x, cam.y); }

	/* checks is rect into viewport */
	bool isIntoViewport(const SDL_Rect* rect);

	/* true if resized for 1 frame */
	inline bool resizedViewport() { return resized; }
private:
	SDL_Rect cam;
	SDL_Renderer* render;
	Vector2Int cmpos; // current mouse position on screen

	bool resized = false;
	int extra_offset; // additionl field where objects are rendered
};

#endif

