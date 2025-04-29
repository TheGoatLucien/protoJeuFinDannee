#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.h>
#include "WindowManager.h"
#include "Particles.h"
#include "List.h"

typedef struct Effect Effect;

struct Effect {
    Particles* particles;
    float duration;
    sfVector2f position;
};

void CreateSlashEffect(sfVector2f position, sfVector2f direction, float range, WindowManager* window);
void CreateShotgunEffect(sfVector2f position, sfVector2f direction, float range, WindowManager* window);
void CreatePiercingEffect(sfVector2f position, sfVector2f direction, float range, WindowManager* window);
void CreateExplosionEffect(sfVector2f position, float range, WindowManager* window);
void UpdateEffects(WindowManager* window);
void RenderEffects(WindowManager* window);
void ClearEffects(void);

#endif