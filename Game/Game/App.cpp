#include "App.h"
void App::Display() {
    InitWindow(1920, 1080, "Test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        Update();
        if (state == EXIT) break;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Draw();
        EndDrawing();
    }
    CloseWindow();
}
void App::Draw() {
    switch (state) {
    case MENU:
        menu.Draw(state);
        break;
    default:
        break;
    }
}