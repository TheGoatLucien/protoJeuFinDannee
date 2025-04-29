#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "WindowManager.h"
#include "Player.h"

void InitGame(WindowManager* window);
void UpdateEventGame(WindowManager* window, sfEvent* evt);
void UpdateGame(WindowManager* window);
void RenderGame(WindowManager* window);
void UIRenderGame(WindowManager* window);
void DestroyGame(WindowManager* window);

#endif