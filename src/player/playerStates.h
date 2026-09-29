#ifndef PLAYER_STATES_H

#define PLAYER_STATES_H
#include "player.h"

//IDLE STATE
void playerState_idle_init(Player *p);
void playerState_idle_update(Player *p, float dt);
void playerState_idle_draw(Player *p);
void playerState_idle_exit(Player *p);
extern PlayerState playerIdleState;

//MOVE STATE
void playerState_move_init(Player *p);
void playerState_move_update(Player *p, float dt);
void playerState_move_draw(Player *p);
void playerState_move_exit(Player *p);
extern PlayerState playerMoveState;

//JUMP STATE
void playerState_jump_init(Player *p);
void playerState_jump_update(Player *p, float dt);
void playerState_jump_draw(Player *p);
void playerState_jump_exit(Player *p);
extern PlayerState playerJumpState;

//FALL STATE
void playerState_fall_init(Player *p);
void playerState_fall_update(Player *p, float dt);
void playerState_fall_draw(Player *p);
void playerState_fall_exit(Player *p);
extern PlayerState playerFallState;

#endif