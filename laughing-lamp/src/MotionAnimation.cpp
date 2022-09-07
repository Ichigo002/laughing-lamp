#include "MotionAnimation.h"

MotionAnimation::MotionAnimation(SDL_Rect* sourceRect)
{
	src = sourceRect;
	setDefaultConstructor();
}

MotionAnimation::MotionAnimation(SDL_Rect* sourceRect, int nFrames, int nDelay, bool isVertical)
{
	src = sourceRect;
	setDefaultConstructor();

	setFrames(nFrames);
	setDelays(nDelay);
	setStartRowAndCol(0, 0);
	setVH(isVertical);
}

MotionAnimation::MotionAnimation(SDL_Rect* sourceRect, int nFrames, int nDelay, int start_row, int start_col, bool isVertical)
{
	src = sourceRect;
	setDefaultConstructor();

	setFrames(nFrames);
	setDelays(nDelay);
	setStartRowAndCol(start_row, start_col);
	setVH(isVertical);
}

MotionAnimation::~MotionAnimation()
{

}

void MotionAnimation::setFrames(int f)
{
	if (f > 0) 
	{
		frames = f;
	}
}

void MotionAnimation::setDelays(int d)
{
	if (d > 0)
	{
		delays = d;
	}
}

void MotionAnimation::setVH(bool v)
{
	verticalAnimation = v;
}

void MotionAnimation::setStartRowAndCol(int row, int column)
{
	if (row > 0) { st_row = row; }
	if (column > 0) { st_col = column; }
}

void MotionAnimation::update()
{
	if (playing)
	{
		tmp_dlv = static_cast<int>((SDL_GetTicks() / delays) % frames);

		if (verticalAnimation)
		{
			src->x = st_col * src->w;
			src->y = src->h * tmp_dlv;
		}
		else
		{
			src->x = src->w * tmp_dlv;
			src->y = st_row * src->h;
		}
	}
}

void MotionAnimation::start()
{
	playing = true;
}

void MotionAnimation::start(int row, int col)
{
	setStartRowAndCol(row, col);
	playing = true;
}

void MotionAnimation::stop()
{
	playing = false;
}

void MotionAnimation::setDefaultConstructor()
{
	setFrames(1);
	setDelays(100);
	setStartRowAndCol(0, 0);
	setVH(false);
	start();
}
