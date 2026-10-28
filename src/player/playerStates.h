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
void update_block_box_position(Player *p);
extern PlayerState playerBlockState;

//ATK1 STATE
void playerState_atk1_init(Player *p);
void playerState_atk1_update(Player *p, float dt);
void playerState_atk1_draw(Player *p);
void playerState_atk1_exit(Player *p);
void update_atk1_box_position(Player *p);
extern PlayerState playerAtk1State;

//ATK2 STATE
void playerState_atk2_init(Player *p);
void playerState_atk2_update(Player *p, float dt);
void playerState_atk2_draw(Player *p);
void playerState_atk2_exit(Player *p);
void update_atk2_box_position(Player *p);
extern PlayerState playerAtk2State;

//ATK3 STATE
void playerState_atk3_init(Player *p);
void playerState_atk3_update(Player *p, float dt);
void playerState_atk3_draw(Player *p);
void playerState_atk3_exit(Player *p);
void update_atk3_box_position(Player *p);
extern PlayerState playerAtk3State;

//CHARGEATK STATE
void playerState_chargeAtk_init(Player *p);
void playerState_chargeAtk_update(Player *p, float dt);
void playerState_chargeAtk_draw(Player *p);
void playerState_chargeAtk_exit(Player *p);
void update_chargeAtk_box_position(Player *p);
extern PlayerState playerChargeAtkState;

void init_states_textures(Player *p);
#endif