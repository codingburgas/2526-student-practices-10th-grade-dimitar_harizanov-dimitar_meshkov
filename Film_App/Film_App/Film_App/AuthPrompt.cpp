#include "AuthPrompt.h"

AuthPrompt::AuthPrompt()
    : nextState(AUTH_PROMPT), hovLogin(false), hovSignup(false), hovCancel(false)
{
}

void AuthPrompt::Update()
{
    nextState = AUTH_PROMPT;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    const int BOX_W = 440;
    const int BOX_H = 300;
    int boxX = screenW / 2 - BOX_W / 2;
    int boxY = screenH / 2 - BOX_H / 2;

    Vector2 mouse = GetMousePosition();

    const int BTN_W = 180;
    const int BTN_H = 50;
    int loginBtnX  = boxX + 30;
    int signupBtnX = boxX + BOX_W - 30 - BTN_W;
    int btnY       = boxY + BOX_H - 80;

    Rectangle loginRect  = { (float)loginBtnX,  (float)btnY, (float)BTN_W, (float)BTN_H };
    Rectangle signupRect = { (float)signupBtnX, (float)btnY, (float)BTN_W, (float)BTN_H };

    Rectangle cancelRect = { (float)(boxX + BOX_W - 36), (float)(boxY + 10), 26.0f, 26.0f };

    hovLogin  = CheckCollisionPointRec(mouse, loginRect);
    hovSignup = CheckCollisionPointRec(mouse, signupRect);
    hovCancel = CheckCollisionPointRec(mouse, cancelRect);

    bool clickedOutside = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        !CheckCollisionPointRec(mouse, { (float)boxX, (float)boxY, (float)BOX_W, (float)BOX_H });

    if (IsKeyPressed(KEY_ESCAPE) || clickedOutside ||
        (hovCancel && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        nextState = DETAIL;

    if (hovLogin  && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextState = LOGIN;
    if (hovSignup && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextState = SIGNUP;
}

void AuthPrompt::Draw()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    DrawRectangle(0, 0, screenW, screenH, { 0, 0, 0, 160 });

    const int BOX_W = 440;
    const int BOX_H = 300;
    int boxX = screenW / 2 - BOX_W / 2;
    int boxY = screenH / 2 - BOX_H / 2;

    DrawRectangle(boxX, boxY, BOX_W, BOX_H, Palette::CARD);
    DrawRectangle(boxX, boxY, BOX_W, 4, Palette::ACCENT);
    DrawRectangleLines(boxX, boxY, BOX_W, BOX_H, { 40, 40, 65, 255 });

    const char* title = "Sign in to Book";
    int titleW = MeasureText(title, 22);
    DrawText(title, boxX + BOX_W / 2 - titleW / 2, boxY + 30, 22, Palette::TEXT_HI);

    const char* sub = "You need an account to book tickets.";
    int subW = MeasureText(sub, 14);
    DrawText(sub, boxX + BOX_W / 2 - subW / 2, boxY + 66, 14, Palette::TEXT_MID);

    const char* sub2 = "Please log in or create a free account.";
    int sub2W = MeasureText(sub2, 14);
    DrawText(sub2, boxX + BOX_W / 2 - sub2W / 2, boxY + 88, 14, Palette::TEXT_MID);

    DrawRectangle(boxX + 30, boxY + 118, BOX_W - 60, 1, { 40, 40, 62, 255 });

    const int BTN_W = 180;
    const int BTN_H = 50;
    int loginBtnX  = boxX + 30;
    int signupBtnX = boxX + BOX_W - 30 - BTN_W;
    int btnY       = boxY + BOX_H - 80;

    Color loginBg  = hovLogin  ? Palette::ACCENT : Color{ 45, 18, 25, 255 };
    Color loginTxt = hovLogin  ? WHITE : Palette::ACCENT;
    DrawRectangle(loginBtnX, btnY, BTN_W, BTN_H, loginBg);
    const char* llbl  = "Log In";
    int         llblW = MeasureText(llbl, 17);
    DrawText(llbl, loginBtnX + BTN_W / 2 - llblW / 2, btnY + 16, 17, loginTxt);

    Color signupBorder = hovSignup ? Palette::ACCENT : Palette::TEXT_DIM;
    Color signupTxt    = hovSignup ? Palette::ACCENT : Palette::TEXT_MID;
    DrawRectangle(signupBtnX, btnY, BTN_W, BTN_H, Palette::CARD);
    DrawRectangleLines(signupBtnX, btnY, BTN_W, BTN_H, signupBorder);
    const char* slbl  = "Sign Up";
    int         slblW = MeasureText(slbl, 17);
    DrawText(slbl, signupBtnX + BTN_W / 2 - slblW / 2, btnY + 16, 17, signupTxt);

    Color xCol = hovCancel ? Palette::ACCENT : Palette::TEXT_DIM;
    DrawText("x", boxX + BOX_W - 28, boxY + 14, 18, xCol);
}
