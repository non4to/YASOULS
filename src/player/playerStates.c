#include <raylib.h>
#include "player.h"
#include "playerStates.h"

//erase these down 
#include <stdio.h>

// IDLE STATE
void playerState_idle_init(Player *p) {
    printf("Started player idle!");
}

void playerState_idle_update(Player *p, float dt){
    Vector2 movementInput = get_movement_input();
    if (movementInput.x!=0.0f||movementInput.y!=0.0f) {
        change_state(p, &playerMoveState);
    }
}

void playerState_idle_draw(Player *p) {
    DrawRectangle((int)p->x, (int)p->y, 20, 60, RED);
}

void playerState_idle_exit(Player *p){
    printf("Exit player idle!");
}

PlayerState playerIdleState = {
    .init = playerState_idle_init,
    .update = playerState_idle_update,
    .draw = playerState_idle_draw,
    .exit = playerState_idle_exit
};

// MOVE STATE
void playerState_move_init(Player *p) {
    printf("Started player move!");
}

void playerState_move_update(Player *p, float dt){
    Vector2 movementInput = get_movement_input();
    if (movementInput.x==0.0f&&movementInput.y==0.0f) {
        change_state(p, &playerIdleState);
    } else {
        p->x += movementInput.x * 100.0f * dt;
        p->y += movementInput.y * 100.0f * dt;
    }
}

void playerState_move_draw(Player *p) {
    DrawRectangle((int)p->x, (int)p->y, 20, 60, GREEN);
}

void playerState_move_exit(Player *p){
    printf("Exit player move!");
}

PlayerState playerMoveState = {
    .init = playerState_move_init,
    .update = playerState_move_update,
    .draw = playerState_move_draw,
    .exit = playerState_move_exit
};