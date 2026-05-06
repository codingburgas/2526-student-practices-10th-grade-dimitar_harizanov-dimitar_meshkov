#include "App.h"
#include "FilmCatalogue.h"

App::App()
    : state(MENU), menu(nullptr)
{
    menu = new Menu(FilmCatalogue::GetAll());
}

App::~App()
{
    delete menu;
}

void App::Display()
{
    InitWindow(1920, 1080, "CineBook");
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

void App::Update()
{
    switch (state)
    {
    case MENU:
        menu->Update();
        HandleStateChange(menu->GetNextState());
        break;

    case DETAIL:
        break;

    case BOOKING:
        break;

    case EXIT:
        break;
    }
}

void App::Draw()
{
    switch (state)
    {
    case MENU:
        menu->Draw();
        break;

    case DETAIL:
        DrawText(" ",
                 GetScreenWidth() / 2 - 160, GetScreenHeight() / 2, 24,
                 Palette::TEXT_HI);
        DrawText(" ",
                 GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 40, 16,
                 Palette::TEXT_DIM);
        if (IsKeyPressed(KEY_ESCAPE))
            state = MENU;
        break;

    case BOOKING:
        DrawText("",
                 GetScreenWidth() / 2 - 160, GetScreenHeight() / 2, 24,
                 Palette::TEXT_HI);
        if (IsKeyPressed(KEY_ESCAPE))
            state = MENU;
        break;

    case EXIT:
        break;
    }
}

void App::HandleStateChange(Appstate newState)
{
    if (newState == state) return;

    state = newState;
}
