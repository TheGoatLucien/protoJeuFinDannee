#include "Effect.h"
#include "GameUtils.h"
#include <stdlib.h>

static List* effects = NULL;

static Effect* CreateEffect(sfVector2f position, float duration) {
    Effect* effect = calloc(1, sizeof(Effect));
    effect->position = position;
    effect->duration = duration;
    if (!effects) effects = list_create(sizeof(Effect*), NULL);
    list_push_back(effects, &effect);
    return effect;
}

void CreateSlashEffect(sfVector2f position, sfVector2f direction, float range, WindowManager* window) {
    Effect* effect = CreateEffect(position, 0.2f);
    effect->particles = CreateParticles(20);
    for (int i = 0; i < 20; i++) {
        float angle = atan2(direction.y, direction.x) + (GameRandFloat(-0.5f, 0.5f) * DEG2RAD);
        sfVector2f velocity = GameGetVectorFromAngle(position, GameRandFloat(50.f, 100.f), angle * RAD2DEG);
        AddParticle(effect->particles, position, velocity, sfWhite, 5.f, 0.2f);
    }
}

void CreateShotgunEffect(sfVector2f position, sfVector2f direction, float range, WindowManager* window) {
    Effect* effect = CreateEffect(position, 0.3f);
    effect->particles = CreateParticles(15);
    for (int i = 0; i < 15; i++) {
        float angle = atan2(direction.y, direction.x) + (GameRandFloat(-0.3f, 0.3f) * DEG2RAD);
        sfVector2f velocity = GameGetVectorFromAngle(position, GameRandFloat(80.f, 120.f), angle * RAD2DEG);
        AddParticle(effect->particles, position, velocity, sfYellow, 4.f, 0.3f);
    }
}

void CreatePiercingEffect(sfVector2f position, sfVector2f direction, float range, WindowManager* window) {
    Effect* effect = CreateEffect(position, 0.4f);
    effect->particles = CreateParticles(10);
    sfVector2f end_pos = { position.x + direction.x * range, position.y + direction.y * range };
    for (int i = 0; i < 10; i++) {
        sfVector2f pos = { position.x + direction.x * range * (i / 10.f), position.y + direction.y * range * (i / 10.f) };
        sfVector2f velocity = { direction.x * 50.f, direction.y * 50.f };
        AddParticle(effect->particles, pos, velocity, sfGreen, 3.f, 0.4f);
    }
}

void CreateExplosionEffect(sfVector2f position, float range, WindowManager* window) {
    Effect* effect = CreateEffect(position, 0.5f);
    effect->particles = CreateParticles(30);
    for (int i = 0; i < 30; i++) {
        float angle = GameRandFloat(0, 360);
        sfVector2f velocity = GameGetVectorFromAngle(position, GameRandFloat(50.f, 150.f), angle);
        AddParticle(effect->particles, position, velocity, sfRed, 6.f, 0.5f);
    }
}

void UpdateEffects(WindowManager* window) {
    if (!effects) return;
    for (int i = list_size(effects) - 1; i >= 0; i--) {
        Effect* effect = *(Effect**)list_get(effects, i);
        effect->duration -= DeltaTime;
        if (effect->duration <= 0) {
            effect->particles->Destroy(&effect->particles);
            free(effect);
            list_erase(effects, i);
            continue;
        }
        UpdateParticles(effect->particles, DeltaTime);
    }
}

void RenderEffects(WindowManager* window) {
    if (!effects) return;
    for (size_t i = 0; i < list_size(effects); i++) {
        Effect* effect = *(Effect**)list_get(effects, i);
        window->DrawParticles(window, effect->particles, NULL);
    }
}

void ClearEffects(void) {
    if (!effects) return;
    for (size_t i = 0; i < list_size(effects); i++) {
        Effect* effect = *(Effect**)list_get(effects, i);
        effect->particles->Destroy(&effect->particles);
        free(effect);
    }
    list_destroy(&effects);
}