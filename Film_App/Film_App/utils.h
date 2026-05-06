#pragma once
#include <raylib.h>
#include <string>
#include <vector>
using namespace std;

	enum Appstate {
		EXIT,
		MENU,

	};

    struct ButtonProps {
        Position pos = CENTER;
        PositionProperty posProp = NONE;
        Vector2 margin = { 0, 0 };
        string imgPath = "";
        string text = "";
        int fontSize = 20;
        Vector2 size;
        Color bgColor = GREEN;
        Color textColor = BLACK;
        int elementsNum;
        AppState nextState;
    };