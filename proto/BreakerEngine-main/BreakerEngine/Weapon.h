#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.h>
#include "WindowManager.h"

typedef enum {
    WEAPON_KATANA,
    WEAPON_BOMB,
    WEAPON_SHOTGUN,
    WEAPON_BOW
} WeaponType;

typedef enum {
    ATTACK_SLASH,
    ATTACK_AREA,
    ATTACK_SHOT,
    ATTACK_PIERCING
} AttackType;

typedef struct Weapon Weapon;

struct Weapon {
    WeaponType type;
    AttackType attack_type;
    float cooldown;
    float cooldown_timer;
    void (*attack)(Weapon* weapon, sfVector2f position, sfVector2f direction, WindowManager* window);
};

Weapon* CreateWeapon(WeaponType type);
void UpdateWeapon(Weapon* weapon, float deltaTime);
void DestroyWeapon(Weapon** weapon);

#endif