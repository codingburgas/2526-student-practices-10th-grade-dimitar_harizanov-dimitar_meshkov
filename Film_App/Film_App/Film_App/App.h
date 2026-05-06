#pragma once
#include <iostream>
#include <raylib.h>
#include "utils.h"
#include "Menu.h"
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

    void HandleStateChange(Appstate newState);
};
