#pragma once
#include <raylib.h>
#include <string>
#include "utils.h"
using namespace std;

class Signup {
public:
    Signup();

    void Update();
    void Draw();

    Appstate GetNextState() const { return nextState; }

private:
    string username;
    string password;
    string confirmPassword;

    bool   usernameActive;
    bool   passwordActive;
    bool   confirmActive;
    bool   hovSignup;
    bool   hovLogin;
    bool   showError;
    string errorMsg;

    Appstate nextState;

    static const int FIELD_W = 360;
    static const int FIELD_H = 46;

    void DrawField(int x, int y, const string& value, bool active,
        bool mask, const char* placeholder);
};
