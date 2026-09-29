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
    bool onFloor;
    float speed;
    bool isPlayer;
    bool flip; 
    PlayerState *currentState;
    Hitbox pushbox;
} Player;

bool jump_pressed(void);
int get_horizontal_input(void);
float get_dx_variation_from_input(Player *p, int inputValue, float dt);
float get_gravity(void);
void player_init(Player *p, float w, float h, float x, float y, float speed);
void player_update(Player *p, World *w, float dt);
void player_draw(Player *p);
void change_state(Player *p, PlayerState *newState);
void update_player_position(Player *p, World *w, float goalX, float goalY);

#endif
