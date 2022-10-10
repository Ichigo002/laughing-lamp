#ifndef TEXT_ASSET_H
#define TEXT_ASSET_H

#include <SDL.h>
#include "FontAsset.h"
#include "../utility/Vector2Int.h"

class TextAsset
{
public:
	/// ui_mode -> if true then text is drown as UI not as object in game
	TextAsset(FontAsset* asset, bool ui_mode = true);
	/// ui_mode -> if true then text is drown as UI not as object in game
	TextAsset(FontAsset* asset, Vector2Int start_pos, int letter_spacing, bool ui_mode = true);
	/// ui_mode -> if true then text is drown as UI not as object in game
	TextAsset(FontAsset* asset, std::string txt, bool ui_mode = true);
	~TextAsset();

	/// <summary>
	/// Set Text to render
	/// </summary>
	/// <param name="txt">text message</param>
	void setText(std::string txt);

	/// <summary>
	/// Space between single letters
	/// </summary>
	/// <param name="s"></param>
	void setLetterSpacing(int s);

	/// <summary>
	/// Starting position on the screen
	/// </summary>
	void setStartingPos(Vector2Int pos);
	void setStartingPos(int x, int y);

	/// <summary>
	/// Draw the text
	/// </summary>
	void draw();

private:
	FontAsset* asset;
	std::string txt;
	Vector2Int start_pos;
	int spacing;
	bool ui_mode;
};

#endif
