#include "Login.h"
using namespace std;

Login::Login()
    : usernameActive(true), passwordActive(false),
    hovLogin(false), hovSignup(false), showError(false), nextState(LOGIN)
{
}

void Login::Reset()
{
    username = "";
    password = "";
    usernameActive = true;
    passwordActive = false;
    hovLogin  = false;
    hovSignup = false;
    showError = false;
    nextState = LOGIN;
}

void Login::Update()
{
    nextState = LOGIN;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    int boxX  = screenW / 2 - FIELD_W / 2;
    int userY = screenH / 2 - 70;
    int passY = userY + 70;

    Rectangle userBox = { (float)boxX, (float)userY, (float)FIELD_W, (float)FIELD_H };
    Rectangle passBox = { (float)boxX, (float)passY, (float)FIELD_W, (float)FIELD_H };

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        usernameActive = CheckCollisionPointRec(mouse, userBox);
        passwordActive = CheckCollisionPointRec(mouse, passBox);
    }

    if (usernameActive)
    {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125 && username.size() < 24)
                username += (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !username.empty())
            username.pop_back();
        if (IsKeyPressed(KEY_TAB)) { usernameActive = false; passwordActive = true; }
    }
    else if (passwordActive)
    {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125 && password.size() < 24)
                password += (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !password.empty())
            password.pop_back();
        if (IsKeyPressed(KEY_TAB)) { passwordActive = false; usernameActive = true; }
    }

    // Log In button
    int btnW = FIELD_W, btnH = 48;
    int btnX = boxX;
    int btnY = passY + 80;
    Rectangle loginBtn = { (float)btnX, (float)btnY, (float)btnW, (float)btnH };
    hovLogin = CheckCollisionPointRec(mouse, loginBtn);

    // Sign Up link
    int linkY = btnY + btnH + 24;
    const char* linkTxt = "Don't have an account?  Sign Up";
    int linkW = MeasureText(linkTxt, 14);
    Rectangle linkRect = { (float)(screenW / 2 - linkW / 2), (float)linkY, (float)linkW, 20.0f };
    hovSignup = CheckCollisionPointRec(mouse, linkRect);

    bool pressedEnter = IsKeyPressed(KEY_ENTER);
    if ((hovLogin && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || pressedEnter)
    {
        if (!username.empty() && !password.empty()) {
            showError = false;
            nextState = MENU;
        } else {
            showError = true;
        }
    }

    if (hovSignup && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        nextState = SIGNUP;

    if (IsKeyPressed(KEY_ESCAPE))
        nextState = AUTH_PROMPT;
}

void Login::Draw()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    int boxX  = screenW / 2 - FIELD_W / 2;
    int userY = screenH / 2 - 70;
    int passY = userY + 70;

    // Logo
    int logoY = userY - 130;
    DrawRectangle(screenW / 2 - 16, logoY, 32, 32, Palette::ACCENT);
    DrawText("C", screenW / 2 - 8, logoY + 6, 22, WHITE);

    const char* title = "CINEBOOK";
    int titleW = MeasureText(title, 28);
    DrawText(title, screenW / 2 - titleW / 2, logoY + 44, 28, Palette::TEXT_HI);

    const char* sub = "Sign in to continue";
    int subW = MeasureText(sub, 15);
    DrawText(sub, screenW / 2 - subW / 2, logoY + 80, 15, Palette::TEXT_MID);

    DrawField(boxX, userY, username, usernameActive, false, "Username");
    DrawField(boxX, passY, password, passwordActive, true,  "Password");

    // Log In button
    int btnW = FIELD_W, btnH = 48;
    int btnX = boxX;
    int btnY = passY + 80;

    Color btnBg  = hovLogin ? Palette::ACCENT : Color{ 45, 18, 25, 255 };
    Color btnTxt = hovLogin ? WHITE : Palette::ACCENT;
    DrawRectangle(btnX, btnY, btnW, btnH, btnBg);
    const char* lbl  = "Log In";
    int         lblW = MeasureText(lbl, 18);
    DrawText(lbl, btnX + btnW / 2 - lblW / 2, btnY + 14, 18, btnTxt);

    if (showError)
    {
        const char* err = "Please enter a username and password";
        int         errW = MeasureText(err, 13);
        DrawText(err, screenW / 2 - errW / 2, btnY + btnH + 14, 13, Palette::ACCENT);
    }

    // Sign Up link
    int linkY = btnY + btnH + 42;
    const char* linkTxt = "Don't have an account?  Sign Up";
    int linkW = MeasureText(linkTxt, 14);
    int linkX = screenW / 2 - linkW / 2;
    Color linkCol = hovSignup ? Palette::ACCENT : Palette::TEXT_MID;
    DrawText(linkTxt, linkX, linkY, 14, linkCol);
    if (hovSignup)
        DrawRectangle(linkX, linkY + 16, linkW, 1, Palette::ACCENT);
}

void Login::DrawField(int x, int y, const string& value, bool active,
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
