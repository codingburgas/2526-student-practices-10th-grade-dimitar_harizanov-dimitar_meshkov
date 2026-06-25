#include "Detail.h"
#include <algorithm>
#include <cstdio>
using namespace std;

Detail::Detail()
    : nextState(DETAIL), hovBack(false), hovBook(false)
{
}

void Detail::SetFilm(const Film& f)
{
    film = f;
    nextState = DETAIL;
    hovBack = false;
    hovBook = false;
}

void Detail::Update()
{
    nextState = DETAIL;

    Vector2 mouse = GetMousePosition();
    int     screenW = GetScreenWidth();
    int     screenH = GetScreenHeight();

    Rectangle backBtn = { 48.0f, (float)(NAVBAR_H + 24), 110.0f, 34.0f };
    hovBack = CheckCollisionPointRec(mouse, backBtn);
    if (hovBack && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        nextState = MENU;

    int btnW = 240, btnH = 52;
    int btnX = POSTER_W + 64;
    int btnY = screenH - 90;
    Rectangle bookBtn = { (float)btnX, (float)btnY, (float)btnW, (float)btnH };
    hovBook = CheckCollisionPointRec(mouse, bookBtn);
    if (hovBook && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        nextState = BOOKING;

    if (IsKeyPressed(KEY_ESCAPE))
        nextState = MENU;
}

void Detail::Draw()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    DrawRectangle(0, 0, screenW, NAVBAR_H, Palette::NAV);
    DrawRectangle(0, NAVBAR_H - 2, screenW, 2, Palette::ACCENT);
    DrawRectangle(48, NAVBAR_H / 2 - 14, 28, 28, Palette::ACCENT);
    DrawText("C", 56, NAVBAR_H / 2 - 10, 20, WHITE);
    DrawText("CINEBOOK", 86, NAVBAR_H / 2 - 9, 19, Palette::TEXT_HI);

    Color backCol = hovBack ? Palette::ACCENT : Palette::TEXT_MID;
    DrawText("< Back", 48, NAVBAR_H + 24, 17, backCol);
    if (hovBack)
        DrawRectangle(48, NAVBAR_H + 45, MeasureText("< Back", 17), 2, Palette::ACCENT);

    int posterH = screenH - NAVBAR_H;
    DrawRectangle(0, NAVBAR_H, POSTER_W, posterH, film.posterColor);

    for (int i = 0; i < 90; i++)
    {
        unsigned char a = (unsigned char)((float)i / 90.0f * 210.0f);
        DrawRectangle(POSTER_W - 90 + i, NAVBAR_H, 1, posterH,
            { Palette::BG.r, Palette::BG.g, Palette::BG.b, a });
    }

    DrawRectangle(0, NAVBAR_H, 4, posterH, Palette::ACCENT);

    int titleY = NAVBAR_H + posterH - 130;
    DrawText(film.title.c_str(), 28, titleY, 38, WHITE);
    DrawRectangle(28, titleY + 48, MeasureText(film.title.c_str(), 38), 4,
        Palette::ACCENT);

    int infoX = POSTER_W + 64;
    int infoW = screenW - infoX - 48;
    int infoY = NAVBAR_H + 72;

    const char* genreStr = film.genre.c_str();
    int gnW = MeasureText(genreStr, 13) + 22;
    DrawRectangle(infoX, infoY, gnW, 28, Palette::ACCENT);
    DrawText(genreStr, infoX + 11, infoY + 7, 13, WHITE);
    infoY += 50;

    string meta = "Dir.  " + film.director + "     \xb7     " + film.duration;
    DrawText(meta.c_str(), infoX, infoY, 15, Palette::TEXT_MID);
    infoY += 44;

    DrawStars(film.rating, infoX, infoY, 14);
    char rBuf[16];
    snprintf(rBuf, sizeof(rBuf), "%.1f / 10", film.rating);
    DrawText(rBuf, infoX + 108, infoY + 2, 14, Palette::TEXT_MID);
    infoY += 52;

    DrawText("SYNOPSIS", infoX, infoY, 11, Palette::TEXT_DIM);
    infoY += 18;
    DrawRectangle(infoX, infoY, 44, 2, Palette::ACCENT);
    infoY += 14;

    DrawWrappedText(film.description, infoX, infoY, infoW, 16, Palette::TEXT_HI);

    int btnW = 240, btnH = 52;
    int btnX = infoX;
    int btnY = screenH - 90;

    Color btnBg = hovBook ? Palette::ACCENT : Color{ 45, 18, 25, 255 };
    Color btnTxt = hovBook ? WHITE : Palette::ACCENT;

    DrawRectangle(btnX, btnY, btnW, btnH, btnBg);
    const char* lbl = "Book Now";
    int         lblW = MeasureText(lbl, 20);
    DrawText(lbl, btnX + btnW / 2 - lblW / 2, btnY + 16, 20, btnTxt);
}

void Detail::DrawStars(float rating, int x, int y, int size)
{
    float filled = (rating / 10.0f) * 5.0f;
    int   gap = size + 4;
    for (int i = 0; i < 5; i++)
    {
        Color c = (i < (int)filled) ? Palette::STAR_ON : Palette::STAR_OFF;
        DrawRectanglePro(
            { (float)(x + i * gap + size / 2), (float)(y + size / 2),
              (float)size * 0.8f, (float)size * 0.8f },
            { (float)size * 0.4f, (float)size * 0.4f },
            45.0f, c);
    }
}

void Detail::DrawWrappedText(const string& text, int x, int y,
    int maxW, int fontSize, Color col)
{
    int charsPerLine = maxW / (fontSize / 2 + 1);
    int start = 0;
    int lineY = y;
    while (start < (int)text.size())
    {
        int end = min(start + charsPerLine, (int)text.size());
        if (end < (int)text.size())
        {
            size_t sp = text.rfind(' ', end);
            if (sp != string::npos && (int)sp > start)
                end = (int)sp;
        }
        string line = text.substr(start, end - start);
        DrawText(line.c_str(), x, lineY, fontSize, col);
        lineY += fontSize + 8;
        start = end + 1;
    }
}