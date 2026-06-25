#include "App.h"
#include "FilmCatalogue.h"

App::App()
    : state(MENU),   // start on the menu; auth is only required when booking
    login(nullptr), signup(nullptr), authPrompt(nullptr),
    menu(nullptr), detail(nullptr), booking(nullptr),
    selectedFilmIdx(-1)
{
    catalogue  = FilmCatalogue::GetAll();
    login      = new Login();
    signup     = new Signup();
    authPrompt = new AuthPrompt();
    menu       = new Menu(catalogue);
    detail     = new Detail();
    booking    = new Booking();
}

App::~App()
{
    delete login;
    delete signup;
    delete authPrompt;
    delete menu;
    delete detail;
    delete booking;
}

void App::Display()
{
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);
    InitWindow(1280, 720, "CineBook");
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
    case LOGIN:
        login->Update();
        HandleStateChange(login->GetNextState());
        break;

    case SIGNUP:
        signup->Update();
        HandleStateChange(signup->GetNextState());
        break;

    case AUTH_PROMPT:
        authPrompt->Update();
        HandleStateChange(authPrompt->GetNextState());
        break;

    case MENU:
        menu->Update();
        HandleStateChange(menu->GetNextState());
        break;

    case DETAIL:
        detail->Update();
        HandleStateChange(detail->GetNextState());
        break;

    case BOOKING:
        booking->Update();
        HandleStateChange(booking->GetNextState());
        break;

    case EXIT:
        break;
    }
}

void App::Draw()
{
    switch (state)
    {
    case LOGIN:       login->Draw();   break;
    case SIGNUP:      signup->Draw();  break;
    case AUTH_PROMPT:
        // Render the film detail page underneath, then the modal overlay on top
        detail->Draw();
        authPrompt->Draw();
        break;
    case MENU:        menu->Draw();    break;
    case DETAIL:      detail->Draw();  break;
    case BOOKING:     booking->Draw(); break;
    case EXIT:        break;
    }
}

void App::HandleStateChange(Appstate newState)
{
    if (newState == state) return;

    // MENU -> DETAIL: remember which film was selected
    if (newState == DETAIL && state == MENU)
    {
        selectedFilmIdx = menu->GetSelectedFilm();
        if (selectedFilmIdx >= 0 && selectedFilmIdx < (int)catalogue.size())
            detail->SetFilm(catalogue[selectedFilmIdx]);
        state = DETAIL;
        return;
    }

    // DETAIL "Book Now" click -> show auth prompt instead of going straight to booking
    if (newState == BOOKING && state == DETAIL)
    {
        state = AUTH_PROMPT;
        return;
    }

    // LOGIN -> MENU (after successful login): proceed to booking now that user is authenticated
    if (newState == MENU && state == LOGIN)
    {
        login->Reset();
        if (selectedFilmIdx >= 0 && selectedFilmIdx < (int)catalogue.size())
            booking->SetFilm(catalogue[selectedFilmIdx]);
        state = BOOKING;
        return;
    }

    // SIGNUP -> MENU (after successful sign-up): proceed to booking
    if (newState == MENU && state == SIGNUP)
    {
        if (selectedFilmIdx >= 0 && selectedFilmIdx < (int)catalogue.size())
            booking->SetFilm(catalogue[selectedFilmIdx]);
        state = BOOKING;
        return;
    }

    // AUTH_PROMPT dismissed (ESC / click outside / X) -> back to detail
    // AUTH_PROMPT -> LOGIN / SIGNUP handled by normal state transition below

    // BOOKING -> MENU (after booking confirmed or back pressed to menu)
    // All other transitions fall through to the simple assignment
    state = newState;
}
