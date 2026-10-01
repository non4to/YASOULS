#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "basePlayerState.h"
#include <raylib.h>
#include <raymath.h>
#include "../world/world.h"

typedef struct Player {
    float hp;
    float sta;
    float w;
    float h;
    float x;
    float y;
    float dx;
    float dy;
    float atkTimer;
    bool onFloor;
    float speed;
    bool isPlayer;
    bool flip; 
    Texture2D spritesheet;
    PlayerState *currentState;
    Hitbox pushbox;
    Hitbox atk1box;
    Hitbox hurtbox;
} Player;

typedef struct ActionResult {
    bool jump;
    bool atk;
    bool block;
} ActionResult;

int get_horizontal_input(void);
float get_dx_variation_from_input(Player *p, int inputValue, float dt);
float get_gravity(void);
void player_init(Player *p, World *w, float x, float y);
void player_update(Player *p, World *w, float dt);
void player_draw(Player *p);
void change_state(Player *p, PlayerState *newState);
void update_player_position(Player *p, World *w, float goalX, float goalY);
ActionResult get_input_actions(void);
#endif
