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
	setSize(ptsize);
	make();
}

GUI_Text::GUI_Text(Camera* c, const char* text, int pos_x, int pos_y)
{
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() at GUI_Text failed: " << TTF_GetError() << std::endl;
	}
	cam = c;
	initBase();
	setText(text);
	SetPosition(pos_x, pos_y);
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

void GUI_Text::setSize(int pt)
{
	this->pt_size = pt;
	_make = false;
}

void GUI_Text::setText(const char* txt)
{
	this->txt = txt;
	_make = false;
}

void GUI_Text::SetColor(int r, int g, int b)
{
	clr.r = r;
	clr.g = g;
	clr.b = b;
	_make = false;
}

void GUI_Text::setRect(SDL_Rect* destR)
{
	rect = destR;
	_make = false;
}

void GUI_Text::SetPosition(int x, int y)
{
	rect->x = x;
	rect->y = y;
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
	pt_size = 32;
	clr = { 0, 0, 0 };
	rect = new SDL_Rect();
	rect->x = 0;
	rect->y = 0;
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

	SDL_QueryTexture(tex, nullptr, nullptr, &rect->w, &rect->h);
}

/*#include "GUI_Text.h"


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

GUI_Text::GUI_Text(Camera* c, std::string path, int ptsize)
{
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() at GUI_Text failed: " << TTF_GetError() << std::endl;
	}
	cam = c;
	initBase();
	setFont(path);
	setSize(ptsize);
	make();
}

GUI_Text::GUI_Text(Camera* c, std::string text, int pos_x, int pos_y)
{
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() at GUI_Text failed: " << TTF_GetError() << std::endl;
	}
	cam = c;
	initBase();
	setText(text);
	SetPosition(pos_x, pos_y);
	make();
}

GUI_Text::~GUI_Text()
{
	TTF_Quit();
}

void GUI_Text::setFont(std::string path)
{
	this->path = path;
	_make = false;
}

void GUI_Text::setSize(int pt)
{
	this->pt_size = pt;
	_make = false;
}

void GUI_Text::setText(std::string txt)
{
	this->txt = txt;
	_make = false;
}

void GUI_Text::SetColor(int r, int g, int b)
{
	clr.r = r;
	clr.g = g;
	clr.b = b;
	_make = false;
}

void GUI_Text::setRect(SDL_Rect* destR)
{
	rect = destR;
	_make = false;
}

void GUI_Text::SetPosition(int x, int y)
{
	rect->x = x;
	rect->y = y;
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
	pt_size = 32;
	clr = { 0, 0, 0 };
	rect = new SDL_Rect();
	rect->x = 0;
	rect->y = 0;
}

void GUI_Text::loadFontAsset()
{
	font = TTF_OpenFont(path.c_str(), pt_size);
	if (font == NULL)
		std::cout << "ERROR TTF_OpenFont() at GUI_Text: " << TTF_GetError() << std::endl;
}

void GUI_Text::renderSurface()
{
	srf = TTF_RenderText_Solid(font, txt.c_str(), clr);
	if (font == NULL)
		std::cout << "ERROR TTF_RenderText_Solid() at GUI_Text: " << TTF_GetError() << std::endl;
}

void GUI_Text::makeTex()
{
	tex = SDL_CreateTextureFromSurface(cam->getRender(), srf);
	if(tex == NULL)
		std::cout << "ERROR SDL_CreateTextureFromSurface() at GUI_Text: " << SDL_GetError() << std::endl;

	SDL_QueryTexture(tex, nullptr, nullptr, &rect->w, &rect->h);
}
*/