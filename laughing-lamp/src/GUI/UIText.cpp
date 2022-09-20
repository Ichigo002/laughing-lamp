#include "UIText.h"
#include "FontAsset.h"

UIText::UIText(FontAsset* asset)
{
	this->asset = asset;
	start_pos = Vector2Int(0, 0);
	spacing = 0;
	setText("Default Text");
}

UIText::UIText(FontAsset* asset, Vector2Int start_pos, int letter_spacing)
{
	this->asset = asset;
	this->start_pos = start_pos;
	spacing = letter_spacing;
	setText("Default Text");
}

UIText::UIText(FontAsset* asset, std::string txt)
{
	start_pos = Vector2Int(0, 0);
	spacing = 0;
	this->asset = asset;
	setText(txt);
}

UIText::~UIText()
{
}

void UIText::setText(std::string txt)
{
	this->txt = txt;
}

void UIText::setLetterSpacing(int s)
{
	spacing = s;
}

void UIText::setStartingPos(Vector2Int pos)
{
	start_pos = pos;
}

void UIText::setStartingPos(int x, int y)
{
	setStartingPos(Vector2Int(x, y));
}

void UIText::draw()
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
					SDL_RenderCopy(asset->__getrender(), obj->tex, NULL, &r);
					r.x += r.w + spacing;
					drawn = true;
					break;
				}
			}
			if (!drawn)
			{
				SDL_QueryTexture(asset->__getglyphs()[0]->tex, nullptr, nullptr, &r.w, &r.h);
				SDL_RenderCopy(asset->__getrender(), asset->__getglyphs()[0]->tex, NULL, &r);
				r.x += r.w + spacing;
			}
		}
		
	}
}
