#include "Player.h"
#include "GameUtils.h"
#include <stdlib.h>

Player* CreatePlayer(int id, sfVector2f position, const char* sprite_path) {
    Player* player = calloc(1, sizeof(Player));
    player->id = id;
    player->position = position;
    player->sprite = sfSprite_create();
    sfTexture* texture = GetTexture(sprite_path);
    sfSprite_setTexture(player->sprite, texture, sfTrue);
    sfSprite_setOrigin(player->sprite, (sfVector2f) { 32, 32 });
    sfSprite_setPosition(player->sprite, position);

    if (id == 1) {
        player->primary_weapon = CreateWeapon(WEAPON_KATANA);
        player->secondary_weapon = CreateWeapon(WEAPON_BOMB);
    }
    else {
        player->primary_weapon = CreateWeapon(WEAPON_SHOTGUN);
        player->secondary_weapon = CreateWeapon(WEAPON_BOW);
    }
    return player;
}

void UpdatePlayer(Player* player, WindowManager* window) {
    float speed = 200.f * DeltaTime;
    sfVector2f movement = { 0, 0 };

    if (player->id == 1) {
        if (sfKeyboard_isKeyPressed(sfKeyA)) movement.x -= speed;
        if (sfKeyboard_isKeyPressed(sfKeyD)) movement.x += speed;
        if (sfKeyboard_isKeyPressed(sfKeyW)) movement.y -= speed;
        if (sfKeyboard_isKeyPressed(sfKeyS)) movement.y += speed;
        if (sfKeyboard_isKeyPressed(sfKeySpace) && player->primary_weapon->cooldown_timer <= 0) {
            sfVector2f mouse_pos = window->GetMousePos(window);
            sfVector2f direction = NormalizeVector2f((sfVector2f) { mouse_pos.x - player->position.x, mouse_pos.y - player->position.y });
            player->primary_weapon->attack(player->primary_weapon, player->position, direction, window);
            player->primary_weapon->cooldown_timer = player->primary_weapon->cooldown;
        }
        if (sfKeyboard_isKeyPressed(sfKeyE) && player->secondary_weapon->cooldown_timer <= 0) {
            sfVector2f mouse_pos = window->GetMousePos(window);
            sfVector2f direction = NormalizeVector2f((sfVector2f) { mouse_pos.x - player->position.x, mouse_pos.y - player->position.y });
            player->secondary_weapon->attack(player->secondary_weapon, player->position, direction, window);
            player->secondary_weapon->cooldown_timer = player->secondary_weapon->cooldown;
        }
    }
    else {
        if (sfKeyboard_isKeyPressed(sfKeyLeft)) movement.x -= speed;
        if (sfKeyboard_isKeyPressed(sfKeyRight)) movement.x += speed;
        if (sfKeyboard_isKeyPressed(sfKeyUp)) movement.y -= speed;
        if (sfKeyboard_isKeyPressed(sfKeyDown)) movement.y += speed;
        if (sfKeyboard_isKeyPressed(sfKeyReturn) && player->primary_weapon->cooldown_timer <= 0) {
            sfVector2f mouse_pos = window->GetMousePos(window);
            sfVector2f direction = NormalizeVector2f((sfVector2f) { mouse_pos.x - player->position.x, mouse_pos.y - player->position.y });
            player->primary_weapon->attack(player->primary_weapon, player->position, direction, window);
            player->primary_weapon->cooldown_timer = player->primary_weapon->cooldown;
        }
        if (sfKeyboard_isKeyPressed(sfKeyR) && player->secondary_weapon->cooldown_timer <= 0) {
            sfVector2f mouse_pos = window->GetMousePos(window);
            sfVector2f direction = NormalizeVector2f((sfVector2f) { mouse_pos.x - player->position.x, mouse_pos.y - player->position.y });
            player->secondary_weapon->attack(player->secondary_weapon, player->position, direction, window);
            player->secondary_weapon->cooldown_timer = player->secondary_weapon->cooldown;
        }
    }

    player->position.x += movement.x;
    player->position.y += movement.y;
    player->position.x = fClamp(player->position.x, 0, 1920);
    player->position.y = fClamp(player->position.y, 0, 1080);
    sfSprite_setPosition(player->sprite, player->position);

    UpdateWeapon(player->primary_weapon, DeltaTime);
    UpdateWeapon(player->secondary_weapon, DeltaTime);
}

void RenderPlayer(Player* player, WindowManager* window) {
    window->DrawSprite(window, player->sprite, NULL);
}

void DestroyPlayer(Player** player) {
    sfSprite_destroy((*player)->sprite);
    DestroyWeapon(&(*player)->primary_weapon);
    DestroyWeapon(&(*player)->secondary_weapon);
    free(*player);
    *player = NULL;
}