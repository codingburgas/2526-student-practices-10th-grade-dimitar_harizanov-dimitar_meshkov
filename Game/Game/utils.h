#pragma once
#include <raylib.h>
#include <string>
#include <vector>
using namespace std;

enum AppState {
	Menu,
};

struct ButtonProps {
	float x;
	float y;
	float width;
	float height;
	const char* text;
	float fontSize = 0;
	Color color = GREEN;
	Color textColor = BLACK;
	const char* imagePath = nullptr;
};

struct User {
	string username;
	string password;
};