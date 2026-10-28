#include <raylib.h>
#include "player.h"
#include "playerStates.h"

//erase these down 
#include <stdio.h>

///////////////////////////////////////////////////////////////////
// CONSTS
static const Vector2 FrameSize = {FRAME_WIDTH, FRAME_HEIGHT};

static const int idleSpriteSheetLineNumber = 0;
static const int idleFinalFrameIndex = 7;
static const bool idleLoop = true;
static const float idleFrameTimes[] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f}; 

static const int moveSpriteSheetLineNumber = 1;
static const int moveFinalFrameIndex = 7;
static const bool moveLoop = true;
static const float moveFrameTimes[] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f}; 

static const int jumpSpriteSheetLineNumber = 2;
static const int jumpFinalFrameIndex = 3;
static const bool jumpLoop = false;
static const float jumpFrameTimes[] = {0.1f, 0.1f, 0.1f, 0.1f}; 

static const int fallSpriteSheetLineNumber = 3;
static const int fallFinalFrameIndex = 4;
static const bool fallLoop = false;
static const float fallFrameTimes[] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f}; 

static const int blockSpriteSheetLineNumber = 4;
static const int blockFinalFrameIndex = 3;
static const bool blockLoop = false;
static const float blockFrameTimes[] = {0.05f, 0.05f, 0.1f, 0.1f, 0.1f}; 

static const int atk1SpriteSheetLineNumber = 5;
static const int atk1FinalFrameIndex = 2;
static const bool atk1Loop = false;
static const float atk1FrameTimes[] = {0.1f, 0.1f, 0.1f}; 

static const int atk2SpriteSheetLineNumber = 6;
static const int atk2FinalFrameIndex = 1;
static const bool atk2Loop = false;
static const float atk2FrameTimes[] = {0.15f, 0.15f}; 

static const int atk3SpriteSheetLineNumber = 7;
static const int atk3FinalFrameIndex = 9;
static const bool atk3Loop = false;
static const float atk3FrameTimes[] = {0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.3f, 0.1f, 0.1f}; 

static const int chargeAtkSpriteSheetLineNumber = 8;
static const int chargeAtkFinalFrameIndex = 7;
static const bool chargeAtkLoop = false;
static const float chargeAtkFrameTimes[] = {0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f}; 
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// IDLE STATE
void playerState_idle_init(Player *p) {
    animation_init(&playerIdleState.animate);
}

void playerState_idle_update(Player *p, float dt){
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions(); 
    animation_update(&playerIdleState.animate, dt);
    if (imputs.jump) {
        player_change_state(p, &playerJumpState);
    } else if (imputs.Satk) {
        player_change_state(p, &playerChargeAtkState);
    } else if (imputs.atk) {
        player_change_state(p, &playerAtk1State);
    } else if (imputs.block) {
        player_change_state(p, &playerBlockState);
    } else if (movementInput!=0) {
        player_change_state(p, &playerMoveState);
    } 
}

void playerState_idle_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_IDLE_SPRITE_OFFSET_X, p->y + PLAYER_IDLE_SPRITE_OFFSET_Y};
    animation_draw(&playerIdleState.animate, position, p->flip);
}

void playerState_idle_exit(Player *p){
}

PlayerState playerIdleState = {
    .init = playerState_idle_init,
    .update = playerState_idle_update,
    .draw = playerState_idle_draw,
    .exit = playerState_idle_exit,
};
///////////////////////////////////////////////////////////////////
// MOVE STATE
void playerState_move_init(Player *p) {
    animation_init(&playerMoveState.animate);

}

void playerState_move_update(Player *p, float dt){
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions(); 
    animation_update(&playerMoveState.animate, dt);
    if (imputs.jump) {
        player_change_state(p, &playerJumpState); 
    } else if (imputs.atk) {
        player_change_state(p, &playerAtk1State);
    } else if (imputs.block) {
        player_change_state(p, &playerBlockState);
    } else if (imputs.Satk) {
        player_change_state(p, &playerChargeAtkState);
    } else if (p->dy !=0) {
        player_change_state(p, &playerFallState); 
    } else if (movementInput==0.0) {
        player_change_state(p, &playerIdleState);
    } else {
        p->dx += get_dx_variation_from_input(p, movementInput, dt);
    }
}

void playerState_move_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_MOVE_SPRITE_OFFSET_X, p->y + PLAYER_MOVE_SPRITE_OFFSET_Y};
    animation_draw(&playerMoveState.animate, position, p->flip);
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
    animation_init(&playerJumpState.animate);
    p -> onFloor = false;
    p->dy = -450.0f;
}

void playerState_jump_update(Player *p, float dt) {
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions(); 
    animation_update(&playerJumpState.animate, dt);
    if (movementInput!=0) p->dx += PLAYER_MOVE_MOVEMENT_AIR_MULTIPLIER * get_dx_variation_from_input(p, movementInput, dt);
    if (imputs.atk) {
        player_change_state(p, &playerAtk1State);
    } else if (p->onFloor) {
        player_change_state(p, &playerIdleState);
    } else if (p->dy > 0) {
        player_change_state(p, &playerFallState);
    }
}

void playerState_jump_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_JUMP_SPRITE_OFFSET_X, p->y + PLAYER_JUMP_SPRITE_OFFSET_Y};
    animation_draw(&playerJumpState.animate, position, p->flip);
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
    animation_init(&playerFallState.animate);   
}

void playerState_fall_update(Player *p, float dt) {
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions(); 
    animation_update(&playerFallState.animate, dt);
    if (movementInput!=0) p->dx += PLAYER_MOVE_MOVEMENT_AIR_MULTIPLIER * get_dx_variation_from_input(p, movementInput, dt);
        if (imputs.atk) {
        player_change_state(p, &playerAtk1State);
    } else if (p->onFloor) {
        player_change_state(p, &playerIdleState);
    }
}

void playerState_fall_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_FALL_SPRITE_OFFSET_X, p->y + PLAYER_FALL_SPRITE_OFFSET_Y};
    animation_draw(&playerFallState.animate, position, p->flip);

}

void playerState_fall_exit(Player *p){
}

PlayerState playerFallState = {
    .init = playerState_fall_init,
    .update = playerState_fall_update,
    .draw = playerState_fall_draw,
    .exit = playerState_fall_exit
};
///////////////////////////////////////////////////////////////////
// BLOCKING STATE
void playerState_block_init(Player *p) {
    animation_init(&playerBlockState.animate);   
    p->blockbox.active = true;
}

void playerState_block_update(Player *p, float dt) {
    float movementMulti = PLAYER_MOVEMENT_FLOOR_MULTIPLIER;
    if (!p->onFloor) movementMulti = PLAYER_MOVEMENT_AIR_MULTIPLIER;
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions(); 
    animation_update(&playerBlockState.animate, dt);
    // if (movementInput!=0) p->dx += movementMulti * get_dx_variation_from_input(p, movementInput, dt);
    if (imputs.atk) {
        player_change_state(p, &playerAtk1State);
    } else if (imputs.Satk) {
        player_change_state(p, &playerChargeAtkState);
    } else if (imputs.jump) {
        player_change_state(p, &playerJumpState);
    } else if (!imputs.block) {
        if (p->onFloor) {
        player_change_state(p, &playerIdleState);
        } else { player_change_state(p, &playerFallState); }
    }
    
}

void playerState_block_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_BLOCK_SPRITE_OFFSET_X, p->y + PLAYER_BLOCK_SPRITE_OFFSET_Y};
    animation_draw(&playerBlockState.animate, position, p->flip);

}

void playerState_block_exit(Player *p){
    p->blockbox.active = false;
}

void update_block_box_position(Player *p){
    float offsetX = PLAYER_BLOCK_BOX_X_OFFSET;
    if (p->flip) offsetX = -PLAYER_BLOCK_BOX_X_OFFSET;
    p->blockbox.rect.x = p->x + offsetX;
    p->blockbox.rect.y = p->y + PLAYER_BLOCK_BOX_Y_OFFSET;
}

PlayerState playerBlockState = {
    .init = playerState_block_init,
    .update = playerState_block_update,
    .draw = playerState_block_draw,
    .exit = playerState_block_exit
};
///////////////////////////////////////////////////////////////////
// CHARGE-ATK STATE
void playerState_chargeAtk_init(Player *p) {
    animation_init(&playerChargeAtkState.animate);
    p->atkTimer = 0;
    p->chargeTimer = 0;
    update_chargeAtk_box_position(p);
    for (int i = 0; i < MAX_TARGETS; i++) {
        p->chargeAtkbox.targetsHit[i] = NULL;
    }
}

void playerState_chargeAtk_update(Player *p, float dt) {
    int direction = 1;
    if (p->flip) direction = -1;
    ActionResult imputs = get_input_actions();
    if (playerChargeAtkState.animate.currentFrame >= chargeAtkFinalFrameIndex) {
        player_change_state(p, &playerIdleState);
    } else if ((imputs.Satk)&&(p->atkTimer <= CHARGEATK_DURATION)) {
        p->atkTimer += dt;
        p->chargeTimer += dt;
        if (p->chargeTimer > CHARGEATK_CHARGE_FRAME_DURATION) {
            playerChargeAtkState.animate.currentFrame ^= 1;
            p->chargeTimer = 0;
        }
    } else if ((!imputs.Satk)||(p->atkTimer > CHARGEATK_DURATION)) {
        if (playerChargeAtkState.animate.currentFrame > 1) {
            p->chargeAtkbox.active = true;    
        }
        animation_update(&playerChargeAtkState.animate, dt);
    } 
}

void playerState_chargeAtk_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_CHARGEATK_SPRITE_OFFSET_X, p->y + PLAYER_CHARGEATK_SPRITE_OFFSET_Y};
    animation_draw(&playerChargeAtkState.animate, position, p->flip);
}

void update_chargeAtk_box_position(Player *p){
    float offsetX = PLAYER_PUSH_BOX_WIDTH;
    if (p->flip) offsetX = -PLAYER_CHARGEATK_BOX_WIDTH;
    p->chargeAtkbox.rect.x = p->x + offsetX;
    p->chargeAtkbox.rect.y = p->y + PLAYER_CHARGEATK_BOX_Y_OFFSET;
}

void playerState_chargeAtk_exit(Player *p){
    p->chargeAtkbox.active = false; 
}

PlayerState playerChargeAtkState = {
    .init = playerState_chargeAtk_init,
    .update = playerState_chargeAtk_update,
    .draw = playerState_chargeAtk_draw,
    .exit = playerState_chargeAtk_exit
};

///////////////////////////////////////////////////////////////////
// ATK3 STATE
void playerState_atk3_init(Player *p) {
    animation_init(&playerAtk3State.animate);
    p->atkTimer = 0;
    p->atk3box.active = true;    
    update_atk3_box_position(p);
    for (int i = 0; i < MAX_TARGETS; i++) {
        p->atk3box.targetsHit[i] = NULL;
    }
}

void playerState_atk3_update(Player *p, float dt) {
    int direction = 1;
    if (p->flip) direction = -1;
    p->dx += direction * ATK3_SMALL_DASH;
    p->atkTimer += dt;
    float movementMulti = PLAYER_MOVEMENT_FLOOR_MULTIPLIER;
    if (!p->onFloor) movementMulti = PLAYER_MOVEMENT_AIR_MULTIPLIER;
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions();
    animation_update(&playerAtk3State.animate, dt);
    if (imputs.atk) {p->comboReady = true;}
    if (movementInput!=0) {
        bool currentFlip = p->flip;    
        p->dx += movementMulti * get_dx_variation_from_input(p, movementInput, dt);
        p->flip = currentFlip;
    }
    if (p->atkTimer > ATK3_DURATION) {
        if (p->dy!=0) {player_change_state(p, &playerFallState);
        } else {player_change_state(p, &playerIdleState);
        }
    }    
}

void playerState_atk3_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_ATK3_SPRITE_OFFSET_X, p->y + PLAYER_ATK3_SPRITE_OFFSET_Y};
    animation_draw(&playerAtk3State.animate, position, p->flip);
}

void update_atk3_box_position(Player *p){
    float offsetX = PLAYER_PUSH_BOX_WIDTH;
    if (p->flip) offsetX = -PLAYER_ATK3_BOX_WIDTH;
    p->atk3box.rect.x = p->x + offsetX;
    p->atk3box.rect.y = p->y + PLAYER_ATK3_BOX_Y_OFFSET;
}

void playerState_atk3_exit(Player *p){
    p->atk3box.active = false; 
}

PlayerState playerAtk3State = {
    .init = playerState_atk3_init,
    .update = playerState_atk3_update,
    .draw = playerState_atk3_draw,
    .exit = playerState_atk3_exit
};
///////////////////////////////////////////////////////////////////
// ATK2 STATE
void playerState_atk2_init(Player *p) {
    animation_init(&playerAtk2State.animate);
    p->atkTimer = 0;
    p->atk2box.active = true;    
    update_atk2_box_position(p);
    for (int i = 0; i < MAX_TARGETS; i++) {
        p->atk2box.targetsHit[i] = NULL;
    }
}

void playerState_atk2_update(Player *p, float dt) {
    int direction = 1;
    if (p->flip) direction = -1;
    p->dx += direction * ATK2_SMALL_DASH;
    p->atkTimer += dt;
    float movementMulti = PLAYER_MOVEMENT_FLOOR_MULTIPLIER;
    if (!p->onFloor) movementMulti = PLAYER_MOVEMENT_AIR_MULTIPLIER;
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions();
    animation_update(&playerAtk2State.animate, dt);
    if (imputs.atk) {p->comboReady = true;}
    if (movementInput!=0) {
        bool currentFlip = p->flip;    
        p->dx += movementMulti * get_dx_variation_from_input(p, movementInput, dt);
        p->flip = currentFlip;
    }
    if (p->atkTimer > ATK2_DURATION) {
        if (p->comboReady) {player_change_state(p, &playerAtk3State);
        } else if (p->dy!=0) {player_change_state(p, &playerFallState);
        } else {player_change_state(p, &playerIdleState);
        }
    }    
}

void playerState_atk2_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_ATK2_SPRITE_OFFSET_X, p->y + PLAYER_ATK2_SPRITE_OFFSET_Y};
    animation_draw(&playerAtk2State.animate, position, p->flip);
}

void update_atk2_box_position(Player *p){
    float offsetX = PLAYER_PUSH_BOX_WIDTH;
    if (p->flip) offsetX = -PLAYER_ATK2_BOX_WIDTH;
    p->atk2box.rect.x = p->x + offsetX;
    p->atk2box.rect.y = p->y + PLAYER_ATK2_BOX_Y_OFFSET;
}

void playerState_atk2_exit(Player *p){
    p->atk2box.active = false; 
}

PlayerState playerAtk2State = {
    .init = playerState_atk2_init,
    .update = playerState_atk2_update,
    .draw = playerState_atk2_draw,
    .exit = playerState_atk2_exit
};
///////////////////////////////////////////////////////////////////
// ATK1 STATE
void playerState_atk1_init(Player *p) {
    animation_init(&playerAtk1State.animate);
    p->atkTimer = 0;
    p->atk1box.active = true;    
    update_atk1_box_position(p);
    for (int i = 0; i < MAX_TARGETS; i++) {
        p->atk1box.targetsHit[i] = NULL;
    }
}

void playerState_atk1_update(Player *p, float dt) {
    int direction = 1;
    if (p->flip) direction = -1;
    p->dx += direction * ATK1_SMALL_DASH;
    p->atkTimer += dt;
    float movementMulti = PLAYER_MOVEMENT_FLOOR_MULTIPLIER;
    if (!p->onFloor) movementMulti = PLAYER_MOVEMENT_AIR_MULTIPLIER;
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions();
    animation_update(&playerAtk1State.animate, dt);
    if (imputs.atk) {p->comboReady = true;}
    if (movementInput!=0) {
        bool currentFlip = p->flip;    
        p->dx += movementMulti * get_dx_variation_from_input(p, movementInput, dt);
        p->flip = currentFlip;
    }
    if (p->atkTimer > ATK1_DURATION) {
        if (p->comboReady) {player_change_state(p, &playerAtk2State);
        } else if (!p->dy==0) {player_change_state(p, &playerFallState);
        } else {player_change_state(p, &playerIdleState);
        }
    }    
}

void playerState_atk1_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_ATK1_SPRITE_OFFSET_X, p->y + PLAYER_ATK1_SPRITE_OFFSET_Y};
    animation_draw(&playerAtk1State.animate, position, p->flip);
}

void playerState_atk1_exit(Player *p){
    p->atk1box.active = false; 
}

void update_atk1_box_position(Player *p){
    float offsetX = PLAYER_PUSH_BOX_WIDTH;
    if (p->flip) offsetX = -PLAYER_ATK1_BOX_WIDTH;
    p->atk1box.rect.x = p->x + offsetX;
    p->atk1box.rect.y = p->y + PLAYER_ATK1_BOX_Y_OFFSET;
}

PlayerState playerAtk1State = {
    .init = playerState_atk1_init,
    .update = playerState_atk1_update,
    .draw = playerState_atk1_draw,
    .exit = playerState_atk1_exit
};
///////////////////////////////////////////////////////////////////
// INITIALIZE STATES TEXTURES
void init_states_textures(Player *p) {
    playerIdleState.animate = create_animation(&p->spritesheet, FrameSize, idleSpriteSheetLineNumber,
                            idleFinalFrameIndex, idleLoop, idleFrameTimes);
    playerMoveState.animate = create_animation(&p->spritesheet, FrameSize, moveSpriteSheetLineNumber,
                            moveFinalFrameIndex, moveLoop, moveFrameTimes);
    playerJumpState.animate = create_animation(&p->spritesheet, FrameSize, jumpSpriteSheetLineNumber,
                            jumpFinalFrameIndex, jumpLoop, jumpFrameTimes);
    playerFallState.animate = create_animation(&p->spritesheet, FrameSize, fallSpriteSheetLineNumber,
                            fallFinalFrameIndex, fallLoop, fallFrameTimes);
    playerBlockState.animate = create_animation(&p->spritesheet, FrameSize, blockSpriteSheetLineNumber,
                            blockFinalFrameIndex, blockLoop, blockFrameTimes);
    playerAtk1State.animate = create_animation(&p->spritesheet, FrameSize, atk1SpriteSheetLineNumber,
                            atk1FinalFrameIndex, atk1Loop, atk1FrameTimes);
    playerAtk2State.animate = create_animation(&p->spritesheet, FrameSize, atk2SpriteSheetLineNumber,
                            atk2FinalFrameIndex, atk2Loop, atk2FrameTimes);
    playerAtk3State.animate = create_animation(&p->spritesheet, FrameSize, atk3SpriteSheetLineNumber,
                            atk3FinalFrameIndex, atk3Loop, atk3FrameTimes);
    playerAtk3State.animate = create_animation(&p->spritesheet, FrameSize, atk3SpriteSheetLineNumber,
                            atk3FinalFrameIndex, atk3Loop, atk3FrameTimes);
    playerChargeAtkState.animate = create_animation(&p->spritesheet, FrameSize, chargeAtkSpriteSheetLineNumber,
                            chargeAtkFinalFrameIndex, chargeAtkLoop, chargeAtkFrameTimes);
}