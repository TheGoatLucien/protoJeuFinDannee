#include "Weapon.h"
#include "Effect.h"
#include "AudioManager.h"
#include <stdlib.h>

static void KatanaAttack(Weapon* weapon, sfVector2f position, sfVector2f direction, WindowManager* window) {
    CreateSlashEffect(position, direction, 100.f, window);
    KSound* sound = GetSound("slash");
    if (sound) KSound_play(sound);
}

static void BombAttack(Weapon* weapon, sfVector2f position, sfVector2f direction, WindowManager* window) {
    CreateExplosionEffect(position, 150.f, window);
    KSound* sound = GetSound("explosion");
    if (sound) KSound_play(sound);
}

static void ShotgunAttack(Weapon* weapon, sfVector2f position, sfVector2f direction, WindowManager* window) {
    CreateShotgunEffect(position, direction, 80.f, window);
    KSound* sound = GetSound("shot");
    if (sound) KSound_play(sound);
}

static void BowAttack(Weapon* weapon, sfVector2f position, sfVector2f direction, WindowManager* window) {
    CreatePiercingEffect(position, direction, 200.f, window);
    KSound* sound = GetSound("arrow");
    if (sound) KSound_play(sound);
}

Weapon* CreateWeapon(WeaponType type) {
    Weapon* weapon = calloc(1, sizeof(Weapon));
    weapon->type = type;
    weapon->cooldown = 0.5f;
    weapon->cooldown_timer = 0.f;

    switch (type) {
    case WEAPON_KATANA:
        weapon->attack_type = ATTACK_SLASH;
        weapon->attack = KatanaAttack;
        break;
    case WEAPON_BOMB:
        weapon->attack_type = ATTACK_AREA;
        weapon->attack = BombAttack;
        break;
    case WEAPON_SHOTGUN:
        weapon->attack_type = ATTACK_SHOT;
        weapon->attack = ShotgunAttack;
        break;
    case WEAPON_BOW:
        weapon->attack_type = ATTACK_PIERCING;
        weapon->attack = BowAttack;
        break;
    }
    return weapon;
}

void UpdateWeapon(Weapon* weapon, float deltaTime) {
    if (weapon->cooldown_timer > 0) {
        weapon->cooldown_timer -= deltaTime;
        if (weapon->cooldown_timer < 0) weapon->cooldown_timer = 0;
    }
}

void DestroyWeapon(Weapon** weapon) {
    free(*weapon);
    *weapon = NULL;
}