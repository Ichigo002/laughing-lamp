#ifndef FONT_ASSET_H
#define FONT_ASSET_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <vector>
#include <string>
#include "../utility/Camera.h"

struct CharGlyph
{
	SDL_Texture* tex;
	char c;
};

class FontAsset
{
public:
	/// <param name="path">filename with font (*.ttf)</param>
	/// <param name="pt_size">what size (pt - points) font will be loaded.</param>
	FontAsset(Camera* c, std::string path, int pt_size, SDL_Color color);
	
	/// <param name="path">filename with font (*.ttf)</param>
	/// <param name="pt_size">what size (pt - points) font will be loaded.</param>
	/// <param name="chars">What characters will be loaded from font. Default = all</param>
	FontAsset(Camera* c, std::string path, int pt_size, SDL_Color color, std::string chars);
	
	~FontAsset();

	/// <summary>
	/// Returns vector of glyphs
	/// </summary>
	std::vector<CharGlyph*>& __getglyphs() { return glyphs; }

	Camera* __getcam() { return c; }
private:
	void loadFont(std::string p, int pt);
	void createGlyphs(SDL_Color clr, SDL_Renderer* r);

	std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]|{}\\;\"':,./<>?";
	std::vector<CharGlyph*> glyphs;
	TTF_Font* font;
	Camera* c;
};

#endif
