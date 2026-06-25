#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include "Film.h"
#include "utils.h"
using namespace std;

class Menu {
public:
    Menu(const vector<Film>& catalogue);

    void     Update();
    void     Draw();

    Appstate GetNextState()    const { return nextState; }
    int      GetSelectedFilm() const { return selectedFilm; }

private:
    vector<Film>   films;
    vector<string> navLinks;

    int      hoveredCard;
    int      hoveredNav;
    float    scrollY;
    Appstate nextState;
    int      selectedFilm;

    static const int NAVBAR_H = 70;
    static const int CARD_W = 210;
    static const int CARD_H = 345;
    static const int CARD_GAP = 26;
    static const int CARD_POSTER = 185;
    static const int SIDE_PAD = 48;
    static const int SECTION_Y = NAVBAR_H + 26;

    void DrawNavbar(int screenW);
    void DrawSectionHeader(int screenW);
    void DrawGrid(int screenW, int screenH);
    void DrawCard(const Film& film, int x, int y, bool hovered);
    void DrawStars(float rating, int x, int y, int size);
    void DrawScrollBar(int screenW, int screenH,
        int totalGridH, int gridAreaH);

    int  CalcCols(int screenW) const;
    int  GridStartY()          const;
};