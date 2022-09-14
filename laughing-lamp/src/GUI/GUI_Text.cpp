#include "GUI_Text.h"

GUI_Text::GUI_Text(Camera* c)
{
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() at GUI_Text failed: " << TTF_GetError() << std::endl;
	}
	cam = c;
	initBase();
	make();
}

GUI_Text::GUI_Text(Camera* c, const char* path, int ptsize)
{
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() at GUI_Text failed: " << TTF_GetError() << std::endl;
	}
	cam = c;
	initBase();
	setFont(path);
	setRes(ptsize);
	make();
}

GUI_Text::~GUI_Text()
{
	TTF_Quit();
}

void GUI_Text::setFont(const char* path)
{
	this->path = path;
	_make = false;
}

void GUI_Text::setRes(int pt)
{
	this->pt_size = pt;
	_make = false;
}

void GUI_Text::setText(const char* txt)
{
	this->txt = txt;
	_make = false;
}

void GUI_Text::SetColor(int r, int g, int b, int a)
{
	clr.r = r;
	clr.g = g;
	clr.b = b;
	clr.a = a;
	_make = false;
}

void GUI_Text::setRect(SDL_Rect* destR)
{
	rect = destR;
	_make = false;
}

void GUI_Text::setRect(int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	_make = false;
}

void GUI_Text::make()
{
	if (!_make)
	{
		loadFontAsset();
		renderSurface();
		makeTex();
		_make = true;
	}
}

void GUI_Text::draw()
{
	if (_make)
		cam->drawGUI(tex, NULL, rect);
	else
		std::cout << "Text has not been completed. Use once make() method before Draw Text" << std::endl;
}

void GUI_Text::initBase()
{
	path = "assets/fonts/Lato-Regular.ttf";
	txt = "Default Text";
	pt_size = 150;
	clr = { 0, 0, 0, 255 };
	rect = new SDL_Rect();
	rect->x = 0;
	rect->y = 0;
	rect->w = 200;
	rect->h = 300;
}

void GUI_Text::loadFontAsset()
{
	font = TTF_OpenFont(path, pt_size);
	if (font == NULL)
		std::cout << "ERROR TTF_OpenFont() at GUI_Text: " << TTF_GetError() << std::endl;
}

void GUI_Text::renderSurface()
{
	srf = TTF_RenderText_Solid(font, txt, clr);
	if (font == NULL)
		std::cout << "ERROR TTF_RenderText_Solid() at GUI_Text: " << TTF_GetError() << std::endl;
}

void GUI_Text::makeTex()
{
	tex = SDL_CreateTextureFromSurface(cam->getRender(), srf);
	if(tex == NULL)
		std::cout << "ERROR SDL_CreateTextureFromSurface() at GUI_Text: " << SDL_GetError() << std::endl;
}
