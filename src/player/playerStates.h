#ifndef PLAYER_STATES_H

#define PLAYER_STATES_H
#include "player.h"
#include "player_config.h"

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

//BLOCK STATE
void playerState_block_init(Player *p);
void playerState_block_update(Player *p, float dt);
void playerState_block_draw(Player *p);
void playerState_block_exit(Player *p);
extern PlayerState playerBlockState;

//ATK1 STATE
void playerState_atk1_init(Player *p);
void playerState_atk1_update(Player *p, float dt);
void playerState_atk1_draw(Player *p);
void playerState_atk1_exit(Player *p);
void update_atk1_box_position(Player *p);
extern PlayerState playerAtk1State;

void init_states_textures(Player *p);
#endif