#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <SDL.h>
#include "FontAsset.h"
#include "../utility/Vector2Int.h"

class UIText
{
public:
	UIText(FontAsset* asset);
	UIText(FontAsset* asset, Vector2Int start_pos, int letter_spacing);
	UIText(FontAsset* asset, std::string txt);
	~UIText();

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
};

#endif
