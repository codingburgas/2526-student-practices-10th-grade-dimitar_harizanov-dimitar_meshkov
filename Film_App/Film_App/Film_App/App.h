#pragma once
#include <iostream>
#include <raylib.h>
#include "utils.h"
#include "Menu.h"
#include "Detail.h"
#include "Booking.h"
using namespace std;

class App {
public:
    App();
    ~App();

    void Display();   
    void Update();    
    void Draw();     
private:
    Appstate state;
    Menu* menu;
    Detail* detail;
    Booking* booking;
    vector<Film> catalogue;
    int selectedFilmIdx;

    void HandleStateChange(Appstate newState);
};
