#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Vector2Int.h"

class Camera
{
public:
	Camera(int screen_w, int screen_h);
	~Camera();

	Vector2Int getMoveSet();

	void set(int x, int y);
	void set(Vector2Int v);

	void move(int x, int y);
	void move(Vector2Int v);
private:
	SDL_Rect cam;
};

#endif

