#pragma once
#include <raylib.h>
#include "Film.h"
#include "utils.h"
#include <string>
#include <vector>
using namespace std;

class Booking {
public:
    Booking();

    void SetFilm(const Film& f);
    void Update();
    void Draw();

    Appstate GetNextState() const { return nextState; }

private:
    Film     film;
    Appstate nextState;
    bool     hovBack;
    bool     hovConfirm;

    int  selectedDate;
    int  selectedTime;
    vector<bool> seats;

    bool  confirmed;
    float confirmTimer;

    static const int NAVBAR_H = 70;
    static const int ROWS = 5;
    static const int COLS = 10;
    static const int SEAT_W = 42;
    static const int SEAT_H = 36;
    static const int SEAT_GAP = 8;

    static const char* DATES[3];
    static const char* TIMES[4];
    static const float TICKET_PRICE;

    int  CountSelected() const;
    void DrawNavbar(int screenW);
};