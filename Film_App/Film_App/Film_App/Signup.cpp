#include "Signup.h"
#include "UserStore.h"
using namespace std;

Signup::Signup()
    : usernameActive(true), passwordActive(false), confirmActive(false),
    hovSignup(false), hovLogin(false), showError(false), nextState(SIGNUP)
{
}

void Signup::Update()
{
    nextState = SIGNUP;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    int boxX  = screenW / 2 - FIELD_W / 2;
    int userY = screenH / 2 - 100;
    int passY = userY + 64;
    int confY = passY + 64;

    Rectangle userBox = { (float)boxX, (float)userY, (float)FIELD_W, (float)FIELD_H };
    Rectangle passBox = { (float)boxX, (float)passY, (float)FIELD_W, (float)FIELD_H };
    Rectangle confBox = { (float)boxX, (float)confY, (float)FIELD_W, (float)FIELD_H };

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        usernameActive = CheckCollisionPointRec(mouse, userBox);
        passwordActive = CheckCollisionPointRec(mouse, passBox);
        confirmActive  = CheckCollisionPointRec(mouse, confBox);
    }

    auto handleInput = [](string& field, int maxLen) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125 && (int)field.size() < maxLen)
                field += (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !field.empty())
            field.pop_back();
    };

    if (usernameActive) {
        handleInput(username, 24);
        if (IsKeyPressed(KEY_TAB)) { usernameActive = false; passwordActive = true; }
    } else if (passwordActive) {
        handleInput(password, 24);
        if (IsKeyPressed(KEY_TAB)) { passwordActive = false; confirmActive = true; }
    } else if (confirmActive) {
        handleInput(confirmPassword, 24);
        if (IsKeyPressed(KEY_TAB)) { confirmActive = false; usernameActive = true; }
    }

    int btnW = FIELD_W, btnH = 48;
    int btnX = boxX;
    int btnY = confY + 74;
    Rectangle signupBtn = { (float)btnX, (float)btnY, (float)btnW, (float)btnH };
    hovSignup = CheckCollisionPointRec(mouse, signupBtn);

    int linkY = btnY + btnH + 24;
    const char* linkTxt = "Already have an account?  Log In";
    int linkW = MeasureText(linkTxt, 14);
    Rectangle linkRect = { (float)(screenW / 2 - linkW / 2), (float)linkY, (float)linkW, 20.0f };
    hovLogin = CheckCollisionPointRec(mouse, linkRect);

    bool pressedEnter = IsKeyPressed(KEY_ENTER);
    if ((hovSignup && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || pressedEnter)
    {
        if (username.empty() || password.empty() || confirmPassword.empty()) {
            showError = true;
            errorMsg = "Please fill in all fields";
        } else if (password != confirmPassword) {
            showError = true;
            errorMsg = "Passwords do not match";
        } else if (UserStore::UserExists(username)) {
            showError = true;
            errorMsg = "An account with this username already exists";
        } else {
            UserStore::CreateUser(username, password);
            showError = false;
            nextState = MENU;
        }
    }

    if (hovLogin && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        nextState = LOGIN;
}

void Signup::Draw()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    int boxX  = screenW / 2 - FIELD_W / 2;
    int userY = screenH / 2 - 100;
    int passY = userY + 64;
    int confY = passY + 64;

    int logoY = userY - 140;
    DrawRectangle(screenW / 2 - 16, logoY, 32, 32, Palette::ACCENT);
    DrawText("C", screenW / 2 - 8, logoY + 6, 22, WHITE);

    const char* title = "CINEBOOK";
    int titleW = MeasureText(title, 28);
    DrawText(title, screenW / 2 - titleW / 2, logoY + 44, 28, Palette::TEXT_HI);

    const char* sub = "Create your account";
    int subW = MeasureText(sub, 15);
    DrawText(sub, screenW / 2 - subW / 2, logoY + 80, 15, Palette::TEXT_MID);

    DrawField(boxX, userY, username,        usernameActive, false, "Username");
    DrawField(boxX, passY, password,        passwordActive, true,  "Password");
    DrawField(boxX, confY, confirmPassword, confirmActive,  true,  "Confirm Password");

    int btnW = FIELD_W, btnH = 48;
    int btnX = boxX;
    int btnY = confY + 74;

    Color btnBg  = hovSignup ? Palette::ACCENT : Color{ 45, 18, 25, 255 };
    Color btnTxt = hovSignup ? WHITE : Palette::ACCENT;
    DrawRectangle(btnX, btnY, btnW, btnH, btnBg);
    const char* lbl  = "Create Account";
    int         lblW = MeasureText(lbl, 18);
    DrawText(lbl, btnX + btnW / 2 - lblW / 2, btnY + 14, 18, btnTxt);

    if (showError)
    {
        int errW = MeasureText(errorMsg.c_str(), 13);
        DrawText(errorMsg.c_str(),
            screenW / 2 - errW / 2, btnY + btnH + 14, 13, Palette::ACCENT);
    }

    int linkY = btnY + btnH + 42;
    const char* linkTxt = "Already have an account?  Log In";
    int linkW = MeasureText(linkTxt, 14);
    int linkX = screenW / 2 - linkW / 2;
    Color linkCol = hovLogin ? Palette::ACCENT : Palette::TEXT_MID;
    DrawText(linkTxt, linkX, linkY, 14, linkCol);
    if (hovLogin)
        DrawRectangle(linkX, linkY + 16, linkW, 1, Palette::ACCENT);
}

void Signup::DrawField(int x, int y, const string& value, bool active,
    bool mask, const char* placeholder)
{
    Color border = active ? Palette::ACCENT : Palette::TEXT_DIM;
    DrawRectangle(x, y, FIELD_W, FIELD_H, Palette::CARD);
    DrawRectangleLines(x, y, FIELD_W, FIELD_H, border);

    string shown = value;
    if (mask) shown = string(value.size(), '*');

    if (shown.empty())
        DrawText(placeholder, x + 14, y + FIELD_H / 2 - 8, 16, Palette::TEXT_DIM);
    else
        DrawText(shown.c_str(), x + 14, y + FIELD_H / 2 - 8, 16, Palette::TEXT_HI);

    if (active)
    {
        int caretX = x + 14 + MeasureText(shown.c_str(), 16) + 2;
        DrawRectangle(caretX, y + 10, 2, FIELD_H - 20, Palette::ACCENT);
    }
}
