#pragma once
#include "raylib.h"
#include "utils.h"

class Button {
	Rectangle button;
	const char* text;
	float fontSize;
	Color color;
	Color textColor;
	Texture2D texture;
	bool hasTexture = false;
	Font font = LoadFont("../fonts/font.otf");
public:
	Button(ButtonProps props);
	void Draw();
	bool isClicked();
	// Returns the biggest font size that fits in a given container
	float findPerfectFontSize(Rectangle container, const char* text, int textPadding);
	// Returns a vector with the position of the perfectly centered text in a given container
	Vector2 findPerfectTextPos();
	void Unload();
	Rectangle getRect();
};