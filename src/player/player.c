#include "player.h"
#include "playerStates.h"
#include <raylib.h>
#include <raymath.h>

void player_init(Player *p, float x, float y, float acc, float maxSpd){
    p -> hp  = 100;
    p -> sta = 100;
    p -> x   = x;
    p -> y   = y;
    p -> dx  = 0;
    p -> dy  = 0;
    p -> acc = acc;
    p -> maxSpd = maxSpd;  
    p -> isPlayer = true;
    p -> flip = false;
    p->currentState = &playerIdleState;
    p->currentState->init(p);
}

void change_state(Player *p, PlayerState *newState){
    p->currentState->exit(p);
    p->currentState = newState;
    p->currentState->init(p);
}

Vector2 get_movement_input() { 
    Vector2 direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_RIGHT)) direction.x += 1.0f;
    if (IsKeyDown(KEY_LEFT)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_UP)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_DOWN)) direction.y += 1.0f;

    if (Vector2Length(direction) > 0.0f) {
        direction = Vector2Normalize(direction);
    }
    return direction;
}
