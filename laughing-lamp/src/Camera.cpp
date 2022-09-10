#include "Camera.h"

Camera::Camera(int screen_w, int screen_h)
{
	cam = { 0, 0, screen_w, screen_h };
}

Camera::~Camera()
{

}

Vector2Int Camera::getMoveSet()
{
	return Vector2Int(cam.x*-1,cam.y*-1);
}

void Camera::set(int x, int y)
{
	cam.x = x;
	cam.y = y;
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
