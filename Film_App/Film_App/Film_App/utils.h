#pragma once
#include <raylib.h>
#include <string>
#include <vector>
using namespace std;

enum Appstate {
    EXIT,
    MENU,
    DETAIL,
    BOOKING,
};

enum Position {
    CENTER,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

enum PositionProperty {
    NONE,
    RELATIVE,
    ABSOLUTE,
};

struct ButtonProps {
    Position         pos         = CENTER;
    PositionProperty posProp     = NONE;
    Vector2          margin      = { 0, 0 };
    string           imgPath     = "";
    string           text        = "";
    int              fontSize    = 18;
    Vector2          size        = { 130, 42 };
    Color            bgColor     = { 220, 40, 60, 255 };
    Color            textColor   = WHITE;
    int              elementsNum = 1;
    Appstate         nextState   = MENU;
};

namespace Palette {
    const Color BG         = {  10,  10,  22, 255 };
    const Color NAV        = {   8,   8,  18, 255 };
    const Color ACCENT     = { 220,  40,  60, 255 };
    const Color CARD       = {  20,  20,  38, 255 };
    const Color CARD_HOV   = {  30,  30,  52, 255 };
    const Color TEXT_HI    = { 240, 240, 248, 255 };
    const Color TEXT_MID   = { 160, 160, 185, 255 };
    const Color TEXT_DIM   = {  90,  90, 115, 255 };
    const Color STAR_ON    = { 255, 195,  50, 255 };
    const Color STAR_OFF   = {  55,  55,  75, 255 };
}
