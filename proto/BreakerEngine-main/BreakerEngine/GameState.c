#include "GameState.h"

#include "Effect.h"

static Player* player1;
static Player* player2;
static sfView* view1;
static sfView* view2;

static void SetupSplitScreen(WindowManager* window, sfView** view1, sfView** view2) {
    *view1 = sfView_create();
    *view2 = sfView_create();
    sfView_setSize(*view1, (sfVector2f) { 1920, 1080 });
    sfView_setSize(*view2, (sfVector2f) { 1920, 1080 });
    sfView_setViewport(*view1, (sfFloatRect) { 0, 0, 0.5f, 1 });
    sfView_setViewport(*view2, (sfFloatRect) { 0.5f, 0, 0.5f, 1 });
}

void InitGame(WindowManager* window) {
    player1 = CreatePlayer(1, (sfVector2f) { 200, 540 }, "player1.png");
    player2 = CreatePlayer(2, (sfVector2f) { 1720, 540 }, "player2.png");
    SetupSplitScreen(window, &view1, &view2);
    LoadSceneSound("Game", NULL, NULL);
}

void UpdateEventGame(WindowManager* window, sfEvent* evt) {
    // Pas d'événements spécifiques
}

void UpdateGame(WindowManager* window) {
    UpdatePlayer(player1, window);
    UpdatePlayer(player2, window);
    UpdateEffects(window);
    sfView_setCenter(view1, player1->position);
    sfView_setCenter(view2, player2->position);
}

void RenderGame(WindowManager* window) {
    window->Clear(window, sfBlack);
    window->SetCustomView(window, view1);
    RenderPlayer(player1, window);
    RenderPlayer(player2, window);
    RenderEffects(window);
    window->SetCustomView(window, view2);
    RenderPlayer(player1, window);
    RenderPlayer(player2, window);
    RenderEffects(window);
    window->Display(window);
}

void UIRenderGame(WindowManager* window) {
    // Pas d'UI
}

void DestroyGame(WindowManager* window) {
    DestroyPlayer(&player1);
    DestroyPlayer(&player2);
    sfView_destroy(view1);
    sfView_destroy(view2);
    ClearEffects();
    ClearSceneSound();
}

REGISTER_STATE(Game);