#pragma once
#include <raylib.h>
#include "menu.h"
#include "utils.h"
#include "button.h"
using namespace std;

class App {
public:
	App();
	void Display();
	void Update();
	void Draw();
private:
	AppState state;
	Menu menu;
	Map map;
	
};