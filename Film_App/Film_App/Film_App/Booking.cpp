#include "Booking.h"
#include <cstdio>
#include <algorithm>
using namespace std;

const char* Booking::DATES[3] = { "Jun 05", "Jun 06", "Jun 07" };
const char* Booking::TIMES[4] = { "12:00", "15:30", "18:00", "21:30" };
const float  Booking::TICKET_PRICE = 12.50f;

Booking::Booking()
    : nextState(BOOKING), hovBack(false), hovConfirm(false),
    selectedDate(0), selectedTime(0),
    seats(ROWS* COLS, false),
    confirmed(false), confirmTimer(0.0f)
{
}

void Booking::SetFilm(const Film& f)
{
    film = f;
    nextState = BOOKING;
    selectedDate = 0;
    selectedTime = 0;
    seats.assign(ROWS * COLS, false);
    confirmed = false;
    confirmTimer = 0.0f;
}

int Booking::CountSelected() const
{
    int n = 0;
    for (bool b : seats) if (b) n++;
    return n;
}

void Booking::Update()
{
    if (confirmed)
    {
        confirmTimer += GetFrameTime();
        if (confirmTimer > 3.2f)
        {
            confirmed = false;
            nextState = MENU;
        }
        return;
    }

    Vector2 mouse = GetMousePosition();
    int     screenW = GetScreenWidth();
    int     screenH = GetScreenHeight();

    Rectangle backBtn = { 48.0f, (float)(NAVBAR_H + 24), 110.0f, 34.0f };
    hovBack = CheckCollisionPointRec(mouse, backBtn);
    if (hovBack && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        nextState = DETAIL;

    int colA = 48;
    int dateY = NAVBAR_H + 130;
    for (int i = 0; i < 3; i++)
    {
        Rectangle r = { (float)(colA + i * 146), (float)dateY, 128.0f, 42.0f };
        if (CheckCollisionPointRec(mouse, r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            selectedDate = i;
    }

    int timeY = dateY + 84;
    for (int i = 0; i < 4; i++)
    {
        Rectangle r = { (float)(colA + i * 136), (float)timeY, 118.0f, 42.0f };
        if (CheckCollisionPointRec(mouse, r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            selectedTime = i;
    }

    int seatOX = colA;
    int seatOY = timeY + 92;
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            int sx = seatOX + c * (SEAT_W + SEAT_GAP);
            int sy = seatOY + r * (SEAT_H + SEAT_GAP);
            Rectangle seat = { (float)sx, (float)sy,
                               (float)SEAT_W, (float)SEAT_H };
            if (CheckCollisionPointRec(mouse, seat)
                && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                seats[r * COLS + c] = !seats[r * COLS + c];
            }
        }
    }

    int btnW = 240, btnH = 52;
    int btnX = screenW - btnW - 48;
    int btnY = screenH - 90;
    Rectangle confirmBtn = { (float)btnX, (float)btnY, (float)btnW, (float)btnH };
    hovConfirm = CheckCollisionPointRec(mouse, confirmBtn);
    if (hovConfirm && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CountSelected() > 0)
    {
        confirmed = true;
        confirmTimer = 0.0f;
    }

    if (IsKeyPressed(KEY_ESCAPE))
        nextState = DETAIL;
}

void Booking::Draw()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    DrawNavbar(screenW);

    if (confirmed)
    {
        int bw = 480, bh = 180;
        int bx = screenW / 2 - bw / 2;
        int by = screenH / 2 - bh / 2;
        DrawRectangle(bx, by, bw, bh, Palette::CARD);
        DrawRectangle(bx, by, 5, bh, Palette::ACCENT);

        const char* line1 = "Booking Confirmed!";
        int w1 = MeasureText(line1, 36);
        DrawText(line1, screenW / 2 - w1 / 2, by + 28, 36, Palette::ACCENT);

        int w2 = MeasureText(film.title.c_str(), 20);
        DrawText(film.title.c_str(), screenW / 2 - w2 / 2, by + 80, 20,
            Palette::TEXT_HI);

        char sub[80];
        snprintf(sub, sizeof(sub), "%d ticket(s)   %s   %s",
            CountSelected(), DATES[selectedDate], TIMES[selectedTime]);
        int w3 = MeasureText(sub, 14);
        DrawText(sub, screenW / 2 - w3 / 2, by + 116, 14, Palette::TEXT_MID);
        return;
    }

    Color backCol = hovBack ? Palette::ACCENT : Palette::TEXT_MID;
    DrawText("< Back", 48, NAVBAR_H + 24, 17, backCol);
    if (hovBack)
        DrawRectangle(48, NAVBAR_H + 45, MeasureText("< Back", 17), 2,
            Palette::ACCENT);

    DrawText("Book Tickets", 48, NAVBAR_H + 72, 26, Palette::TEXT_HI);
    int htw = MeasureText("Book Tickets", 26);
    const char* filmNameStr = film.title.c_str();
    DrawText(filmNameStr, 48 + htw + 16, NAVBAR_H + 79, 17, Palette::ACCENT);

    int colA = 48;
    int dateY = NAVBAR_H + 130;

    DrawText("DATE", colA, dateY - 20, 11, Palette::TEXT_DIM);
    for (int i = 0; i < 3; i++)
    {
        bool  sel = (selectedDate == i);
        Color bg = sel ? Palette::ACCENT : Palette::CARD;
        Color tc = sel ? WHITE : Palette::TEXT_MID;
        int   dx = colA + i * 146;
        DrawRectangle(dx, dateY, 128, 42, bg);
        int tw = MeasureText(DATES[i], 15);
        DrawText(DATES[i], dx + 64 - tw / 2, dateY + 13, 15, tc);
    }

    int timeY = dateY + 84;
    DrawText("SHOWTIME", colA, timeY - 20, 11, Palette::TEXT_DIM);
    for (int i = 0; i < 4; i++)
    {
        bool  sel = (selectedTime == i);
        Color bg = sel ? Palette::ACCENT : Palette::CARD;
        Color tc = sel ? WHITE : Palette::TEXT_MID;
        int   tx = colA + i * 136;
        DrawRectangle(tx, timeY, 118, 42, bg);
        int tw = MeasureText(TIMES[i], 15);
        DrawText(TIMES[i], tx + 59 - tw / 2, timeY + 13, 15, tc);
    }

    int seatOX = colA;
    int seatOY = timeY + 92;

    DrawText("SELECT SEATS", seatOX, seatOY - 22, 11, Palette::TEXT_DIM);

    int screenBarW = COLS * (SEAT_W + SEAT_GAP) - SEAT_GAP;
    DrawRectangle(seatOX, seatOY - 10, screenBarW, 3,
        { 200, 200, 220, 50 });
    int scrlbl = MeasureText("SCREEN", 10);
    DrawText("SCREEN", seatOX + screenBarW / 2 - scrlbl / 2,
        seatOY - 22, 10, { 100, 100, 130, 180 });

    Vector2 mouse = GetMousePosition();
    for (int r = 0; r < ROWS; r++)
    {

        char rowLbl[3] = { (char)('A' + r), '\0' };
        DrawText(rowLbl, seatOX - 22,
            seatOY + r * (SEAT_H + SEAT_GAP) + SEAT_H / 2 - 7,
            14, Palette::TEXT_DIM);

        for (int c = 0; c < COLS; c++)
        {
            int  sx = seatOX + c * (SEAT_W + SEAT_GAP);
            int  sy = seatOY + r * (SEAT_H + SEAT_GAP);
            bool sel = seats[r * COLS + c];
            bool hov = CheckCollisionPointRec(mouse,
                { (float)sx, (float)sy, (float)SEAT_W, (float)SEAT_H });

            Color bg = sel ? Palette::ACCENT
                : (hov ? Palette::CARD_HOV : Palette::CARD);
            DrawRectangle(sx, sy, SEAT_W, SEAT_H, bg);

            char num[4];
            snprintf(num, sizeof(num), "%d", c + 1);
            int nw = MeasureText(num, 10);
            DrawText(num, sx + SEAT_W / 2 - nw / 2,
                sy + SEAT_H / 2 - 6, 10,
                sel ? WHITE : Palette::TEXT_DIM);
        }
    }

    int legY = seatOY + ROWS * (SEAT_H + SEAT_GAP) + 14;
    DrawRectangle(seatOX, legY, 14, 14, Palette::CARD);
    DrawText("Available", seatOX + 20, legY, 12, Palette::TEXT_DIM);
    DrawRectangle(seatOX + 120, legY, 14, 14, Palette::ACCENT);
    DrawText("Selected", seatOX + 140, legY, 12, Palette::TEXT_DIM);

    int sumW = 240;
    int sumX = screenW - sumW - 48;
    int sumY = NAVBAR_H + 110;
    int sumH = 220;
    DrawRectangle(sumX, sumY, sumW, sumH, Palette::CARD);
    DrawRectangle(sumX, sumY, 4, sumH, Palette::ACCENT);

    DrawText("ORDER SUMMARY", sumX + 16, sumY + 16, 11, Palette::TEXT_DIM);
    DrawRectangle(sumX + 16, sumY + 36, sumW - 32, 1,
        { 40, 40, 62, 255 });

    char buf[64];
    snprintf(buf, sizeof(buf), "%s", film.title.c_str());
    DrawText(buf, sumX + 16, sumY + 48, 14, Palette::TEXT_HI);

    snprintf(buf, sizeof(buf), "%s  \xb7  %s", DATES[selectedDate],
        TIMES[selectedTime]);
    DrawText(buf, sumX + 16, sumY + 74, 12, Palette::TEXT_MID);

    snprintf(buf, sizeof(buf), "Seats:  %d", CountSelected());
    DrawText(buf, sumX + 16, sumY + 104, 14, Palette::TEXT_MID);

    snprintf(buf, sizeof(buf), "$%.2f x %d", TICKET_PRICE, CountSelected());
    DrawText(buf, sumX + 16, sumY + 130, 13, Palette::TEXT_DIM);

    DrawRectangle(sumX + 16, sumY + 158, sumW - 32, 1,
        { 40, 40, 62, 255 });

    char totalStr[32];
    snprintf(totalStr, sizeof(totalStr), "Total:  $%.2f",
        CountSelected() * TICKET_PRICE);
    DrawText(totalStr, sumX + 16, sumY + 172, 20, Palette::TEXT_HI);

    int btnW = 240, btnH = 52;
    int btnX = screenW - btnW - 48;
    int btnY = screenH - 90;

    bool  canBook = CountSelected() > 0;
    Color btnBg = (hovConfirm && canBook) ? Palette::ACCENT
        : (canBook ? Color{ 45, 18, 25, 255 }
    : Color{ 25, 25, 40,  255 });
    Color btnTxt = (hovConfirm && canBook) ? WHITE
        : (canBook ? Palette::ACCENT
            : Palette::TEXT_DIM);
    DrawRectangle(btnX, btnY, btnW, btnH, btnBg);
    const char* lbl = canBook ? "Confirm Booking" : "Select a Seat";
    int         lblW = MeasureText(lbl, 16);
    DrawText(lbl, btnX + btnW / 2 - lblW / 2, btnY + 18, 16, btnTxt);
}

void Booking::DrawNavbar(int screenW)
{
    DrawRectangle(0, 0, screenW, NAVBAR_H, Palette::NAV);
    DrawRectangle(0, NAVBAR_H - 2, screenW, 2, Palette::ACCENT);
    DrawRectangle(48, NAVBAR_H / 2 - 14, 28, 28, Palette::ACCENT);
    DrawText("C", 56, NAVBAR_H / 2 - 10, 20, WHITE);
    DrawText("CINEBOOK", 86, NAVBAR_H / 2 - 9, 19, Palette::TEXT_HI);
}