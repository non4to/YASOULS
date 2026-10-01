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
        change_state(p, &playerJumpState);
    } else if (imputs.atk) {
        change_state(p, &playerAtk1State);
    } else if (imputs.block) {
        change_state(p, &playerBlockState);
    } else if (movementInput!=0) {
        change_state(p, &playerMoveState);
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
        change_state(p, &playerJumpState); 
    } else if (imputs.atk) {
        change_state(p, &playerAtk1State);
    } else if (imputs.block) {
        change_state(p, &playerBlockState);
    } else if (movementInput==0.0) {
        change_state(p, &playerIdleState);
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
        change_state(p, &playerAtk1State);
    } else if (p->onFloor) {
        change_state(p, &playerIdleState);
    } else if (p->dy > 0) {
        change_state(p, &playerFallState);
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
        change_state(p, &playerAtk1State);
    } else if (p->onFloor) {
        change_state(p, &playerIdleState);
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
}

void playerState_block_update(Player *p, float dt) {
    float movementMulti = PLAYER_MOVEMENT_FLOOR_MULTIPLIER;
    if (!p->onFloor) movementMulti = PLAYER_MOVEMENT_AIR_MULTIPLIER;
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions(); 
    animation_update(&playerBlockState.animate, dt);
    if (movementInput!=0) p->dx += movementMulti * get_dx_variation_from_input(p, movementInput, dt);
    if (imputs.atk) {
        change_state(p, &playerAtk1State);
    } else if (imputs.jump) {
        change_state(p, &playerJumpState);
    } else if (!imputs.block) {
        if (p->onFloor) {
        change_state(p, &playerIdleState);
        } else { change_state(p, &playerFallState); }
    }
    
}

void playerState_block_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_BLOCK_SPRITE_OFFSET_X, p->y + PLAYER_BLOCK_SPRITE_OFFSET_Y};
    animation_draw(&playerBlockState.animate, position, p->flip);

}

void playerState_block_exit(Player *p){
}

PlayerState playerBlockState = {
    .init = playerState_block_init,
    .update = playerState_block_update,
    .draw = playerState_block_draw,
    .exit = playerState_block_exit
};
///////////////////////////////////////////////////////////////////
// ATK1 STATE
void playerState_atk1_init(Player *p) {
    animation_init(&playerAtk1State.animate);
    p->atkTimer = 0;
    p->atk1box.active = true;    
    update_atk1_box_position(p);
}

void playerState_atk1_update(Player *p, float dt) {
    p->atkTimer += dt;
    float movementMulti = PLAYER_MOVEMENT_FLOOR_MULTIPLIER;
    if (!p->onFloor) movementMulti = PLAYER_MOVEMENT_AIR_MULTIPLIER;
    int movementInput = get_horizontal_input();
    ActionResult imputs = get_input_actions();
    animation_update(&playerAtk1State.animate, dt);
    if (movementInput!=0) {
        bool currentFlip = p->flip;    
        p->dx += movementMulti * get_dx_variation_from_input(p, movementInput, dt);
        p->flip = currentFlip;
    }
    if (p->atkTimer > ATK1_DURATION) change_state(p, &playerIdleState);
}

void playerState_atk1_draw(Player *p) {
    Vector2 position = {p->x + PLAYER_ATK1_SPRITE_OFFSET_X, p->y + PLAYER_ATK1_SPRITE_OFFSET_Y};
    animation_draw(&playerAtk1State.animate, position, p->flip);

}

void playerState_atk1_exit(Player *p){
    p->atk1box.active = false; 
}

void update_atk1_box_position(Player *p){
    float offsetX = PLAYER_ATK1_BOX_X_OFFSET;
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
}