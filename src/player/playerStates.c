#include <raylib.h>
#include "player.h"
#include "playerStates.h"

//erase these down 
#include <stdio.h>

// IDLE STATE
void playerState_idle_init(Player *p) {

}

void playerState_idle_update(Player *p, float dt){
    int movementInput = get_horizontal_input();
    int jumpPressed = jump_pressed();
    if (jumpPressed) {
        change_state(p, &playerJumpState);
    } else if (movementInput!=0) {
        change_state(p, &playerMoveState);
    }
}

void playerState_idle_draw(Player *p) {
    DrawRectangle((int)p->x, (int)p->y, (int)p->w, (int)p->h, RED);
}

void playerState_idle_exit(Player *p){
}

PlayerState playerIdleState = {
    .init = playerState_idle_init,
    .update = playerState_idle_update,
    .draw = playerState_idle_draw,
    .exit = playerState_idle_exit
};
///////////////////////////////////////////////////////////////////
// MOVE STATE
void playerState_move_init(Player *p) {

}

void playerState_move_update(Player *p, float dt){
    int movementInput = get_horizontal_input();
    int jumpPressed = jump_pressed();
    if (jumpPressed) {
        change_state(p, &playerJumpState); 
    } else if (movementInput==0.0) {
        change_state(p, &playerIdleState);
    } else {
        p->dx += get_dx_variation_from_input(p, movementInput, dt);
    }
}

void playerState_move_draw(Player *p) {
    DrawRectangle((int)p->x, (int)p->y, (int)p->w, (int)p->h, GREEN);
}

void playerState_move_exit(Player *p){
}

PlayerState playerMoveState = {
    .init = playerState_move_init,
    .update = playerState_move_update,
    .draw = playerState_move_draw,
    .exit = playerState_move_exit
};
///////////////////////////////////////////////////////////////////
// JUMP STATE
void playerState_jump_init(Player *p) {
    p -> onFloor = false;
    p->dy = -450.0f;
}

void playerState_jump_update(Player *p, float dt) {
    int movementInput = get_horizontal_input();
    if (movementInput!=0) p->dx += 0.75 * get_dx_variation_from_input(p, movementInput, dt);
    if (p->onFloor) change_state(p, &playerIdleState);
    if (p->dy > 0) change_state(p, &playerFallState);
}

void playerState_jump_draw(Player *p) {
    DrawRectangle((int)p->x, (int)p->y, (int)p->w, (int)p->h, YELLOW);
}

void playerState_jump_exit(Player *p){
    p -> onFloor = true;
}

PlayerState playerJumpState = {
    .init = playerState_jump_init,
    .update = playerState_jump_update,
    .draw = playerState_jump_draw,
    .exit = playerState_jump_exit
};
///////////////////////////////////////////////////////////////////
// FALLING STATE
void playerState_fall_init(Player *p) {

}

void playerState_fall_update(Player *p, float dt) {
    int movementInput = get_horizontal_input();
    if (movementInput!=0) p->dx += 0.75 * get_dx_variation_from_input(p, movementInput, dt);
    if (p->onFloor) change_state(p, &playerIdleState);
}

void playerState_fall_draw(Player *p) {
    DrawRectangle((int)p->x, (int)p->y, (int)p->w, (int)p->h, ORANGE);

}

void playerState_fall_exit(Player *p){
}

PlayerState playerFallState = {
    .init = playerState_fall_init,
    .update = playerState_fall_update,
    .draw = playerState_fall_draw,
    .exit = playerState_fall_exit
};