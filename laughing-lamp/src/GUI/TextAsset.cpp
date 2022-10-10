#include "TextAsset.h"
#include "FontAsset.h"

TextAsset::TextAsset(FontAsset* asset, bool ui_mode)
{
	this->asset = asset;
	this->ui_mode = ui_mode;
	start_pos = Vector2Int(0, 0);
	spacing = 0;
	setText("Default Text");
}

TextAsset::TextAsset(FontAsset* asset, Vector2Int start_pos, int letter_spacing, bool ui_mode)
{
	this->asset = asset;
	this->start_pos = start_pos;
	this->ui_mode = ui_mode;
	spacing = letter_spacing;
	setText("Default Text");
}

TextAsset::TextAsset(FontAsset* asset, std::string txt, bool ui_mode)
{
	start_pos = Vector2Int(0, 0);
	spacing = 0;
	this->asset = asset;
	this->ui_mode = ui_mode;
	setText(txt);
}

TextAsset::~TextAsset()
{
}

void TextAsset::setText(std::string txt)
{
	this->txt = txt;
}

void TextAsset::setLetterSpacing(int s)
{
	spacing = s;
}

void TextAsset::setStartingPos(Vector2Int pos)
{
	start_pos = pos;
}

void TextAsset::setStartingPos(int x, int y)
{
	setStartingPos(Vector2Int(x, y));
}

void TextAsset::draw()
{
	SDL_Rect r;
	r.x = start_pos.x;
	r.y = start_pos.y;
	bool drawn = false;

	for (size_t i = 0; i < txt.length(); i++)
	{
		if (txt[i] == ' ')
		{
			SDL_QueryTexture(asset->__getglyphs()[0]->tex, nullptr, nullptr, &r.w, &r.h);
			r.x += r.w + spacing;
		}
		else
		{
			drawn = false;
			for (auto& obj : asset->__getglyphs())
			{
				if (obj->c == txt[i])
				{
					SDL_QueryTexture(obj->tex, nullptr, nullptr, &r.w, &r.h);
					if (ui_mode)
						asset->__getcam()->drawGUI(obj->tex, NULL, &r);
					else
						asset->__getcam()->drawDynamic(obj->tex, NULL, &r);
					r.x += r.w + spacing;
					drawn = true;
					break;
				}
			}
			if (!drawn)
			{
				SDL_QueryTexture(asset->__getglyphs()[0]->tex, nullptr, nullptr, &r.w, &r.h);
				if (ui_mode)
					asset->__getcam()->drawGUI(asset->__getglyphs()[0]->tex, NULL, &r);
				else
					asset->__getcam()->drawDynamic(asset->__getglyphs()[0]->tex, NULL, &r);
				r.x += r.w + spacing;
			}
		}
		
	}
}
