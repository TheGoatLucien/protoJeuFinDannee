#include "Game.h"
#include "GameState.h"
#include "LoadingState.h"
#include "Particles.h"

int main(void) {
    InitResourcesManager("../Ressources");
    StartGame(CreateWindowManager(1920, 1080, "BreakerEngine", sfDefaultStyle, NULL), "Game", "Loading", &ResetLoadingState);
    return 0;
}