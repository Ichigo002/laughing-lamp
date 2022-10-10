#include "FontAsset.h"
#include <iostream>

FontAsset::FontAsset(Camera* c, std::string path, int pt_size, SDL_Color color)
{
	loadFont(path, pt_size);
	createGlyphs(color, c->getRender());
	this->c = c;
}

FontAsset::FontAsset(Camera* c, std::string path, int pt_size, SDL_Color color, std::string chars)
{
	loadFont(path, pt_size);
	this->chars = chars;
	createGlyphs(color, c->getRender());
	this->c = c;
}

FontAsset::~FontAsset()
{
	TTF_CloseFont(font);
	TTF_Quit();
}

void FontAsset::loadFont(std::string p, int pt)
{
	TTF_Init();
	font = TTF_OpenFont(p.c_str(), pt);
	if (font == NULL)
		std::cout << "FontAsset::loadFont(std::string, int): Couldn't load font" << std::endl;
}

void FontAsset::createGlyphs(SDL_Color clr, SDL_Renderer* r)
{
	std::string _chars = "?" + chars;
	SDL_Surface* srf;
	for(size_t i = 0; i < _chars.length(); i++)
	{
		std::string s(1, _chars[i]);
		CharGlyph* glyph = new CharGlyph;
		glyph->c = _chars[i];
		srf = TTF_RenderText_Blended(font, s.c_str(), clr);
		glyph->tex = SDL_CreateTextureFromSurface(r, srf);
		SDL_FreeSurface(srf);
		glyphs.push_back(glyph);
	}
}

