#include "App.h"

App::App()
{
    state = MENU;
}

void App::Display()
{
    InitWindow(1920, 1080, "Test");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Update();
        if (state == EXIT) break;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Draw();
        EndDrawing();
    }
    CloseWindow();
}

void App::Update()
{
}

void App::Draw()
{
}
