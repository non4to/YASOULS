#include "player.h"
#include "playerStates.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

static int cont = 0; //debug

float get_gravity(void){
    return 1200.0f;
}

void change_state(Player *p, PlayerState *newState){
    p->currentState->exit(p);
    p->currentState = newState;
    p->currentState->init(p);
}

int get_horizontal_input(void) { 
    int direction = 0;
    if (IsKeyDown(KEY_D)) direction += 1;
    else if (IsKeyDown(KEY_A)) direction -= 1;
    return direction;
}

float get_dx_variation_from_input(Player *p, int inputValue, float dt) { 
    return inputValue * p->speed * dt;
}

bool jump_pressed(void){
    return IsKeyPressed(KEY_SPACE);
}

void update_player_position(Player *p, World *w, float goalX, float goalY) {

    MoveResult collisionResult = world_move(w, &p->pushbox, goalX, goalY);
    p->x = collisionResult.position.x;
    p->y = collisionResult.position.y;

    if (collisionResult.hitRight || collisionResult.hitLeft) {
        p->dx = 0;
    }

    if (collisionResult.hitCeiling || collisionResult.hitGround) {
        p->dy = 0;
    }
    
    p->onFloor = collisionResult.hitGround;
    
    p->pushbox.rect.x = p->x;
    p->pushbox.rect.y = p->y;
}

void player_init(Player *p, float w, float h, float x, float y, float speed){
    p -> hp  = 100;
    p -> sta = 100;
    p -> h = h;
    p -> w = w;
    p -> x   = x;
    p -> y   = y;
    p -> dx  = 0;
    p -> dy  = 0;
    p -> onFloor = false;
    p -> speed = speed; 
    p -> isPlayer = true;
    p -> flip = false;
    p-> currentState = &playerIdleState;
    p-> currentState->init(p);
    p -> pushbox = (Hitbox){BOX_PUSH, true, {p->x, p->y, p->w, p->h}};
}

void player_update(Player *p, World *w, float dt){
    p->dx = 0;
    p->currentState->update(p, dt);
    if (!p->onFloor) p->dy += get_gravity() * dt;

    float goalX = p->x + p->dx;
    float goalY = p->y + p->dy * dt;
    update_player_position(p, w, goalX, goalY);

}

void player_draw(Player *p){
    p->currentState->draw(p);
    //DEBUG
    DrawRectangleLines(p->pushbox.rect.x, p->pushbox.rect.y, p->pushbox.rect.width, p->pushbox.rect.height, BLACK);                   

}