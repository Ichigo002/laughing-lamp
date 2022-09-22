#include "Camera.h"

Camera::Camera(SDL_Renderer* r, int sw, int sh)
{
	cam.x = 0;
	cam.y = 0;
	cam.w = sw;
	cam.h = sh;
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
	return Vector2Int(cam.w, cam.h);
}

SDL_Renderer* Camera::getRender()
{
	return render;
}

Vector2Int Camera::translateMouseToGLB()
{
	return Vector2Int(cmpos.x - getMoveSet().x, cmpos.y - getMoveSet().y);
}

Vector2Int Camera::getMouse()
{
	return cmpos;
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

Vector2Int Camera::convertGLB_LCL(Vector2Int pos)
{
	if (pos.y < 0)
		pos.y -= (HEX_HEIGHT * RATIOHEX_H * MAP_RENDER_SCALE);
	if (pos.x < 0)
		pos.x -= (HEX_WIDTH * MAP_RENDER_SCALE);
	return Vector2Int(pos.x / (HEX_WIDTH * MAP_RENDER_SCALE), pos.y / (HEX_HEIGHT * RATIOHEX_H * MAP_RENDER_SCALE));
}

Vector2Int Camera::convertLCL_GLB(Vector2Int pos)
{
	return Vector2Int(pos.x * (HEX_WIDTH * MAP_RENDER_SCALE), pos.y * (HEX_HEIGHT * RATIOHEX_H * MAP_RENDER_SCALE));
}

void Camera::update(SDL_Event* eve)
{
	if (eve->type == SDL_MOUSEMOTION)
	{
		cmpos.x = eve->button.x;
		cmpos.y = eve->button.y;
	}
	if (eve->type == SDL_WINDOWEVENT)
	{
		if (eve->window.event == SDL_WINDOWEVENT_RESIZED)
		{
			cam.w = eve->window.data1;
			cam.h = eve->window.data2;
			resized = true;
		}
	}
	else
	{
		resized = false;
	}
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

