#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../utility/Camera.h"

#define TXT_RATIO 5.7

class GUI_Text
{
public:
	GUI_Text(Camera* c);
	GUI_Text(Camera* c, const char* path, int ptsize);
	~GUI_Text();

	/* In order correctly work of program this method MUST be firstly or secondly called */
	/* set font from the path for this text */
	void setFont(const char* path);

	/* In order correctly work of program this method MUST be firstly or secondly called */
	/* Set resolution of loaded font in points */
	/* if resolution is higher, pixels are smaller during scaling */
	void setRes(int pt);

	/* set text to display on next frame */
	void setText(const char* txt);

	/* set the color of text */
	void SetColor(int r, int g, int b, int a);

	/* set Destination Rect of Text on the screen */
	void setRect(SDL_Rect* destR);

	/* set Destination Rect of Text on the screen */
	void setRect(int x, int y, int w, int h);

	/* make ready text to render */
	void make();

	/* Draw the text */
	void draw();

private:
	/* init basic values */
	void initBase();

	/* loads font */
	void loadFontAsset();

	/* create surface for new text */
	void renderSurface();

	/* create Texture from surface */
	void makeTex();

	const char* path;
	const char* txt;
	int pt_size;
	float ratio;
	bool _make;

	SDL_Texture* tex;
	SDL_Surface* srf;
	SDL_Color clr;
	SDL_Rect* rect;

	TTF_Font* font;

	Camera* cam;
};

#endif

