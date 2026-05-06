#pragma once
#include <iostream>
#include <raylib.h>
#include "utils.h"
#include "Menu.h"
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  App – top-level state machine
//  Owns every screen object. Each frame it calls the active screen's
//  Update() and Draw(), then checks if the screen requested a transition.
// ─────────────────────────────────────────────────────────────────────────────
class App {
public:
    App();
    ~App();

    void Display();   // window creation + game loop
    void Update();    // delegates to active screen
    void Draw();      // delegates to active screen

private:
    Appstate state;

    // ── Screen instances (add more as the project grows) ─────────────────────
    Menu* menu;

    // ── Helpers ──────────────────────────────────────────────────────────────
    void HandleStateChange(Appstate newState);
};
