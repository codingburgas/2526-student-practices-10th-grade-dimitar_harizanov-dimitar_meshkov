#include "App.h"
#include "FilmCatalogue.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor / Destructor
// ─────────────────────────────────────────────────────────────────────────────
App::App()
    : state(MENU), menu(nullptr)
{
    // Menu is created here so it loads film data before the window opens.
    // Add other screen constructors below as the project grows.
    menu = new Menu(FilmCatalogue::GetAll());
}

App::~App()
{
    delete menu;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Display – window + game loop
// ─────────────────────────────────────────────────────────────────────────────
void App::Display()
{
    InitWindow(1280, 780, "CineBook");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Update();
        if (state == EXIT) break;

        BeginDrawing();
        ClearBackground(Palette::BG);
        Draw();
        EndDrawing();
    }

    CloseWindow();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Update – delegate to active screen, then handle any state change
// ─────────────────────────────────────────────────────────────────────────────
void App::Update()
{
    switch (state)
    {
    case MENU:
        menu->Update();
        HandleStateChange(menu->GetNextState());
        break;

    case DETAIL:
        // TODO: create and delegate to a DetailScreen
        // detail->Update();
        // HandleStateChange(detail->GetNextState());
        break;

    case BOOKING:
        // TODO: create and delegate to a BookingScreen
        break;

    case EXIT:
        break;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Draw – delegate to active screen
// ─────────────────────────────────────────────────────────────────────────────
void App::Draw()
{
    switch (state)
    {
    case MENU:
        menu->Draw();
        break;

    case DETAIL:
        // TODO: detail->Draw();
        // For now, show a placeholder
        DrawText("Detail screen – coming soon",
                 GetScreenWidth() / 2 - 160, GetScreenHeight() / 2, 24,
                 Palette::TEXT_HI);
        DrawText("(Press ESC to go back)",
                 GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 40, 16,
                 Palette::TEXT_DIM);
        if (IsKeyPressed(KEY_ESCAPE))
            state = MENU;
        break;

    case BOOKING:
        // TODO: booking->Draw();
        DrawText("Booking screen – coming soon",
                 GetScreenWidth() / 2 - 160, GetScreenHeight() / 2, 24,
                 Palette::TEXT_HI);
        if (IsKeyPressed(KEY_ESCAPE))
            state = MENU;
        break;

    case EXIT:
        break;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  HandleStateChange – react to transitions requested by screens
// ─────────────────────────────────────────────────────────────────────────────
void App::HandleStateChange(Appstate newState)
{
    if (newState == state) return;

    // Future: tear down old screen, init new one if needed
    state = newState;
}
