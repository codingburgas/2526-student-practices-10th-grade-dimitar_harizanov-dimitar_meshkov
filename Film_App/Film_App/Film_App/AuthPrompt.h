#pragma once
#include <raylib.h>
#include "utils.h"
using namespace std;

// Overlay shown when a guest tries to book a film.
// They can choose Log In, Sign Up, or dismiss (ESC / click outside).
class AuthPrompt {
public:
    AuthPrompt();

    void Update();
    void Draw();

    Appstate GetNextState() const { return nextState; }

private:
    Appstate nextState;
    bool hovLogin;
    bool hovSignup;
    bool hovCancel;
};
