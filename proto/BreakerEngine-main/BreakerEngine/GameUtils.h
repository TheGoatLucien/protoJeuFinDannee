#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <SFML/Graphics.h>
#include <math.h>

#define DEG2RAD (3.14159265358979323846 / 180.0)
#define RAD2DEG (180.0 / 3.14159265358979323846)

float fClamp(float value, float min, float max);
float GameRandFloat(float min, float max);
sfVector2f NormalizeVector2f(sfVector2f vec);
sfVector2f GameGetVectorFromAngle(sfVector2f origin, float magnitude, float angleDeg);

#endif