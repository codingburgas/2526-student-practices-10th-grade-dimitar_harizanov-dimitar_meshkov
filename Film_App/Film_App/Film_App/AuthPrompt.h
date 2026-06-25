#pragma once
#include <raylib.h>
#include "utils.h"
using namespace std;

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
