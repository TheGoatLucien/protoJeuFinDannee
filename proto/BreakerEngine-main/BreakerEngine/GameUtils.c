#include "GameUtils.h"
#include <stdlib.h>

float fClamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float GameRandFloat(float min, float max) {
    return min + (rand() / (float)RAND_MAX) * (max - min);
}

sfVector2f NormalizeVector2f(sfVector2f vec) {
    float mag = sqrt(vec.x * vec.x + vec.y * vec.y);
    if (mag == 0) return vec;
    return (sfVector2f) { vec.x / mag, vec.y / mag };
}

sfVector2f GameGetVectorFromAngle(sfVector2f origin, float magnitude, float angleDeg) {
    float rad = angleDeg * DEG2RAD;
    return (sfVector2f) { origin.x + magnitude * cos(rad), origin.y + magnitude * sin(rad) };
}