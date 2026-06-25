#pragma once
#include <iostream>
#include <raylib.h>
#include "utils.h"
#include "Login.h"
#include "Signup.h"
#include "AuthPrompt.h"
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
    Login*      login;
    Signup*     signup;
    AuthPrompt* authPrompt;
    Menu*       menu;
    Detail*     detail;
    Booking*    booking;
    vector<Film> catalogue;
    int selectedFilmIdx;

    void HandleStateChange(Appstate newState);
};
