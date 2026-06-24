#include "Menu.h"
#include <cmath>
#include <algorithm>
using namespace std;

Menu::Menu(const vector<Film>& catalogue)
    : films(catalogue),
    hoveredCard(-1),
    hoveredNav(-1),
    scrollY(0.0f),
    nextState(MENU),
    selectedFilm(-1)
{
    navLinks = { "Home", "Movies", "My Bookings", "About" };
}

int Menu::CalcCols(int screenW) const
{
    int cols = (screenW - SIDE_PAD * 2 + CARD_GAP) / (CARD_W + CARD_GAP);
    return max(1, cols);
}

int Menu::GridStartY() const
{
    return SECTION_Y + 46 - (int)scrollY;
}

void Menu::Update()
{
    nextState = MENU;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int cols = CalcCols(screenW);
    int rows = ((int)films.size() + cols - 1) / cols;

    float wheel = GetMouseWheelMove();
    scrollY -= wheel * 36.0f;
    scrollY = max(scrollY, 0.0f);

    int totalGridH = rows * (CARD_H + CARD_GAP);
    int gridAreaH = screenH - (SECTION_Y + 46);
    float maxScroll = max(0.0f, (float)(totalGridH - gridAreaH));
    scrollY = min(scrollY, maxScroll);

    Vector2 mouse = GetMousePosition();
    hoveredCard = -1;

    int startX = SIDE_PAD;
    int startY = GridStartY();

    for (int i = 0; i < (int)films.size(); i++)
    {
        int col = i % cols;
        int row = i / cols;
        int cx = startX + col * (CARD_W + CARD_GAP);
        int cy = startY + row * (CARD_H + CARD_GAP);

        Rectangle r = { (float)cx, (float)cy, (float)CARD_W, (float)CARD_H };
        if (CheckCollisionPointRec(mouse, r))
        {
            hoveredCard = i;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                selectedFilm = i;
                nextState = DETAIL;
            }
            break;
        }
    }

    hoveredNav = -1;
    int linkX = screenW - SIDE_PAD;

    for (int i = (int)navLinks.size() - 1; i >= 0; i--)
    {
        int tw = MeasureText(navLinks[i].c_str(), 16);
        linkX -= tw + 32;
        Rectangle r = { (float)linkX, 0, (float)(tw + 32), (float)NAVBAR_H };
        if (CheckCollisionPointRec(mouse, r))
        {
            hoveredNav = i;
            break;
        }
    }
}

void Menu::Draw()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    DrawNavbar(screenW);
    DrawSectionHeader(screenW);
    DrawGrid(screenW, screenH);
}

void Menu::DrawNavbar(int screenW)
{
    DrawRectangle(0, 0, screenW, NAVBAR_H, Palette::NAV);
    DrawRectangle(0, NAVBAR_H - 2, screenW, 2, Palette::ACCENT);

    int logoX = SIDE_PAD;
    int logoY = NAVBAR_H / 2 - 14;
    DrawRectangle(logoX, logoY, 28, 28, Palette::ACCENT);
    DrawText("C", logoX + 8, logoY + 4, 20, WHITE);
    DrawText("CINEBOOK", logoX + 38, NAVBAR_H / 2 - 9, 19, Palette::TEXT_HI);

    int linkX = screenW - SIDE_PAD;
    for (int i = (int)navLinks.size() - 1; i >= 0; i--)
    {
        const char* label = navLinks[i].c_str();
        int tw = MeasureText(label, 16);
        linkX -= tw + 32;

        bool   hov = (hoveredNav == i);
        Color  col = hov ? Palette::ACCENT : Palette::TEXT_MID;

        DrawText(label, linkX + 16, NAVBAR_H / 2 - 8, 16, col);
        if (hov)
            DrawRectangle(linkX + 16, NAVBAR_H / 2 + 11, tw, 2, Palette::ACCENT);
    }
}

void Menu::DrawSectionHeader(int screenW)
{
    const char* title = "Now Showing";
    DrawText(title, SIDE_PAD, SECTION_Y, 26, Palette::TEXT_HI);
    int tw = MeasureText(title, 26);
    DrawRectangle(SIDE_PAD, SECTION_Y + 32, tw, 3, Palette::ACCENT);

    char badge[32];
    snprintf(badge, sizeof(badge), "%d films", (int)films.size());
    DrawText(badge,
        SIDE_PAD + tw + 18,
        SECTION_Y + 4, 14, Palette::TEXT_DIM);
}

void Menu::DrawGrid(int screenW, int screenH)
{
    int cols = CalcCols(screenW);
    int startX = SIDE_PAD;
    int startY = GridStartY();

    BeginScissorMode(0, NAVBAR_H + 1, screenW, screenH - NAVBAR_H - 1);

    for (int i = 0; i < (int)films.size(); i++)
    {
        int col = i % cols;
        int row = i / cols;
        int cx = startX + col * (CARD_W + CARD_GAP);
        int cy = startY + row * (CARD_H + CARD_GAP);

        if (cy + CARD_H < NAVBAR_H) continue;
        if (cy > screenH + CARD_H) continue;

        DrawCard(films[i], cx, cy, hoveredCard == i);
    }

    EndScissorMode();

    int rows = ((int)films.size() + cols - 1) / cols;
    int totalGridH = rows * (CARD_H + CARD_GAP);
    int gridAreaH = screenH - (SECTION_Y + 46);
    DrawScrollBar(screenW, screenH, totalGridH, gridAreaH);
}

void Menu::DrawCard(const Film& film, int x, int y, bool hovered)
{
    Color bg = hovered ? Palette::CARD_HOV : Palette::CARD;

    DrawRectangle(x + 4, y + 6, CARD_W, CARD_H, { 0, 0, 0, 70 });

    DrawRectangle(x, y, CARD_W, CARD_H, bg);

    DrawRectangle(x, y, CARD_W, CARD_POSTER, film.posterColor);

    for (int i = 0; i < 48; i++)
    {
        unsigned char alpha = (unsigned char)((i / 48.0f) * 220);
        DrawRectangle(x, y + CARD_POSTER - 48 + i, CARD_W, 1,
            { bg.r, bg.g, bg.b, alpha });
    }

    int gnW = MeasureText(film.genre.c_str(), 11) + 14;
    DrawRectangle(x + 10, y + 10, gnW, 21, { 0, 0, 0, 150 });
    DrawText(film.genre.c_str(), x + 17, y + 14, 11, Palette::ACCENT);

    int durW = MeasureText(film.duration.c_str(), 10) + 12;
    DrawRectangle(x + CARD_W - durW - 8, y + 10, durW, 19, { 0, 0, 0, 150 });
    DrawText(film.duration.c_str(), x + CARD_W - durW - 2, y + 13,
        10, Palette::TEXT_MID);

    int infoY = y + CARD_POSTER + 10;

    DrawText(film.title.c_str(), x + 12, infoY, 15, Palette::TEXT_HI);

    string dir = "Dir. " + film.director;
    DrawText(dir.c_str(), x + 12, infoY + 19, 10, Palette::TEXT_DIM);

    DrawStars(film.rating, x + 12, infoY + 36, 9);
    char rBuf[8];
    snprintf(rBuf, sizeof(rBuf), "%.1f", film.rating);
    DrawText(rBuf, x + 76, infoY + 36, 10, Palette::TEXT_MID);

    string d = film.description;
    if ((int)d.size() > 56) d = d.substr(0, 53) + "...";
    DrawText(d.substr(0, min((int)d.size(), 27)).c_str(),
        x + 12, infoY + 53, 10, Palette::TEXT_DIM);
    if ((int)d.size() > 27)
        DrawText(d.substr(27).c_str(), x + 12, infoY + 66, 10, Palette::TEXT_DIM);

    int btnY = y + CARD_H - 36;
    int btnX = x + 12;
    int btnW = CARD_W - 24;
    int btnH = 26;

    Color btnBg = hovered ? Palette::ACCENT : Color{ 45, 18, 25, 255 };
    Color btnTxt = hovered ? WHITE : Color{ 190, 70, 90, 255 };

    DrawRectangle(btnX, btnY, btnW, btnH, btnBg);
    const char* lbl = "Book Now";
    int         lblW = MeasureText(lbl, 13);
    DrawText(lbl, btnX + btnW / 2 - lblW / 2, btnY + 6, 13, btnTxt);

    if (hovered)
        DrawRectangle(x, y, 3, CARD_H, Palette::ACCENT);
}

void Menu::DrawStars(float rating, int x, int y, int size)
{
    float filled = (rating / 10.0f) * 5.0f;
    int   gap = size + 3;

    for (int i = 0; i < 5; i++)
    {
        Color c = (i < (int)filled) ? Palette::STAR_ON : Palette::STAR_OFF;
        DrawRectanglePro(
            { (float)(x + i * gap + size / 2),
              (float)(y + size / 2),
              (float)size * 0.8f, (float)size * 0.8f },
            { (float)size * 0.4f, (float)size * 0.4f },
            45.0f, c
        );
    }
}

void Menu::DrawScrollBar(int screenW, int screenH,
    int totalGridH, int gridAreaH)
{
    if (totalGridH <= gridAreaH) return;     

    float ratio = (float)gridAreaH / totalGridH;
    int   barH = (int)(gridAreaH * ratio);
    float travel = (float)(gridAreaH - barH);
    float maxSc = (float)(totalGridH - gridAreaH);
    int   barY = (SECTION_Y + 46) + (int)(travel * (scrollY / maxSc));

    DrawRectangle(screenW - 6, SECTION_Y + 46, 4,
        gridAreaH, { 30, 30, 50, 200 });
    DrawRectangle(screenW - 6, barY, 4, barH, Palette::ACCENT);
}