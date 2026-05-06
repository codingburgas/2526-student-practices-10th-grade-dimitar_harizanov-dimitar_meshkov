#pragma once
#include <iostream>
#include <raylib.h>
#include "utils.h"
using namespace std;

class App {
public:
    App();
    void Display();
    void Update();
    void Draw();

private:
    Appstate state;

};