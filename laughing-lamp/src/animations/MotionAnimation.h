#ifndef MOTION_ANIMATION_H
#define MOTION_ANIMATION_H

#include <SDL.h>
#include <iostream>

/* Class to animate any object */
/* It makes using easy stop-motion animation */
/* In order to use create only the object or pointer of this and use it! */
class MotionAnimation
{
public:
	MotionAnimation(SDL_Rect* sourceRect);
	MotionAnimation(SDL_Rect* sourceRect, int nFrames, int nDelay, bool isVertical = false);
	MotionAnimation(SDL_Rect* sourceRect, int nFrames, int nDelay, int start_row, int start_col, bool isVertical = false);
	~MotionAnimation();

	/* Set Amount of frames */
	void setFrames(int f);
	int getFrames() { return frames; }

	/* Set Delays between frames [miliseconds] */
	void setDelays(int d);
	int getDelays() { return delays; }

	/* Set will Animation be played vertical mode or horizontal */
	/* If true then is vertical mode */
	void setVH(bool v);
	bool getVH() { return verticalAnimation; }

	/* Set where animation will start. */
	/* Rows & Columns size is based on default source rect */
	void setStartRowAndCol(int row, int column);
	int getStartRow() { return st_row; }
	int getStartCol() { return st_col; }

	/* Call update of animation */
	/* Recommended put this into main loop of game*/
	void update();

	/* Starts the animation where it was stopped */
	void start();

	/* Starts the animation from new position */
	void start(int row, int col);

	/* Stop the currently playing animation */
	void stop();

private:
	/* Default constructor */
	void setDefaultConstructor();

	int frames; // amount of frames
	int delays; // delays between frames
	bool verticalAnimation; // vertical | or horizontal --
	bool playing; // is animation playing now
	int st_row; // where in the source animation starts
	int st_col; // where in the source animation starts

	int tmp_dlv; // temporary delay value

	SDL_Rect* src;
};

#endif

