#include "button.h"

Button::Button(ButtonProps props) {
	button = { props.x, props.y , props.width, props.height };
	text = props.text;
	if (fontSize == 0)
		fontSize = findPerfectFontSize(button, text, 100);
	else fontSize = props.fontSize;
	color = props.color;
	textColor = props.textColor;
	hasTexture = false;
	// Only load texture if an image path is provided
	if (props.imagePath != nullptr) {
		Image img = LoadImage(props.imagePath);
		ImageResize(&img, props.width, props.height);
		texture = LoadTextureFromImage(img);

		if (texture.id != 0) {
			hasTexture = true;
		}

	}

}
void Button::Draw()
{
	if (hasTexture) {
		DrawTexture(texture, button.x, button.y, WHITE);
		DrawTextEx(GetFontDefault(), text, findPerfectTextPos(), fontSize, 1.f, WHITE);
	}
	else {
		DrawRectangleRec(button, color);
		DrawTextEx(GetFontDefault(), text, findPerfectTextPos(), fontSize, 1.f, textColor);
	}
}
void Button::Unload()
{
	if (hasTexture) {
		UnloadTexture(texture);
		hasTexture = false;
	}
}

Rectangle Button::getRect() {
	return button;
}


bool Button::isClicked()
{
	if (CheckCollisionPointRec(GetMousePosition(), button))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return true;
		}
	}
	return false;
}
#include <iostream>
float Button::findPerfectFontSize(Rectangle container, const char* text, int textPadding) {
	// Start with a font size as large as the container width.
	float fontSize = container.width;
	Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 5.f);
	std::cout << text << std::endl;
	for (int i = fontSize; i >= 1; i--) {
		textSize.x = MeasureText(text, 100);
		std::cout << "TEXT X: " << textSize.x << " TEXT Y: " << textSize.y << std::endl;
		if (textSize.x < container.width - textPadding) {
			return (float)i;
		}
	}
	return 0.f;
}

Vector2 Button::findPerfectTextPos() {
	Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1.f);
	Vector2 textPos = { button.x + ((button.width - textSize.x) / 2),
						button.y + ((button.height - textSize.y) / 2) };
	return textPos;
}