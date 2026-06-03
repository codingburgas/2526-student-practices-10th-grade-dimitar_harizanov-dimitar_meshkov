#pragma once
#include <raylib.h>
#include "Film.h"
#include "utils.h"
#include <string>
using namespace std;

class Detail {
public:
    Detail();

    void SetFilm(const Film& f);
    void Update();
    void Draw();

    Appstate GetNextState() const { return nextState; }

private:
    Film     film;
    Appstate nextState;
    bool     hovBack;
    bool     hovBook;

    static const int NAVBAR_H = 70;
    static const int POSTER_W = 420;

    void DrawStars(float rating, int x, int y, int size);
    void DrawWrappedText(const string& text, int x, int y, int maxW,
        int fontSize, Color col);
};