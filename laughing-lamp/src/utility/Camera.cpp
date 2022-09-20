#include "Camera.h"

Camera::Camera(SDL_Renderer* r, int screen_w, int screen_h)
{
	cam = { 0, 0, screen_w, screen_h };
	render = r;
	extra_offset = 100;
}

Camera::~Camera()
{

}

Vector2Int Camera::getMoveSet()
{
	return Vector2Int(cam.x*-1,cam.y*-1);
}

Vector2Int Camera::getWHScreen()
{
	return Vector2Int(cam.w - 350, cam.h - 350);
}

SDL_Renderer* Camera::getRender()
{
	return render;
}

int Camera::drawDynamic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR, bool only_in_viewport)
{
	SDL_Rect r = *destR;
	if (only_in_viewport)
	{
		if (!isIntoViewport(destR)) { return 0; }
	}

	r.x += getMoveSet().x;
	r.y += getMoveSet().y;
	return SDL_RenderCopy(render, texture, srcR, &r);
}

int Camera::drawStatic(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR)
{
	return SDL_RenderCopy(render, texture, srcR, destR);
}

int Camera::drawGUI(SDL_Texture* texture, const SDL_Rect* srcR, const SDL_Rect* destR)
{
	return SDL_RenderCopy(render, texture, srcR, destR);
}

void Camera::set(int x, int y)
{
	cam.x = x - cam.w / 2;
	cam.y = y - cam.h / 2;
}

void Camera::set(Vector2Int v)
{
	set(v.x, v.y);
}

void Camera::move(int x, int y)
{
	cam.x += x;
	cam.y += y;
}

void Camera::move(Vector2Int v)
{
	move(v.x, v.y);
}

bool Camera::isIntoViewport(const SDL_Rect* rect)
{
	if (
		rect->x + rect->w >= cam.x - extra_offset &&
		cam.x + cam.w + extra_offset >= rect->x &&
		rect->y + rect->h >= cam.y - extra_offset &&
		cam.y + cam.h + extra_offset >= rect->y
		)
	{
		return true;
	}

	return false;
}
