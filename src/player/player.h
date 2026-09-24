#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "basePlayerState.h"
#include <raylib.h>
#include <raymath.h>

typedef struct Player {
    float hp;
    float sta;
    float x;
    float y;
    float dx;
    float dy;
    float acc;
    float maxSpd;
    bool isPlayer;
    bool flip; 
    PlayerState *currentState;
} Player;

void player_init(Player *p, float x, float y, float acc, float maxSpd);
void change_state(Player *p, PlayerState *newState);
Vector2 get_movement_input();

#endif
