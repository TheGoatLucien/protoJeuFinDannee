#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.h>
#include "WindowManager.h"
#include "Weapon.h"

typedef struct Player Player;

struct Player {
    int id;
    sfVector2f position;
    sfSprite* sprite;
    Weapon* primary_weapon;
    Weapon* secondary_weapon;
};

Player* CreatePlayer(int id, sfVector2f position, const char* sprite_path);
void UpdatePlayer(Player* player, WindowManager* window);
void RenderPlayer(Player* player, WindowManager* window);
void DestroyPlayer(Player** player);

#endif