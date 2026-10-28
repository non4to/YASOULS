#include "player.h"
#include "playerStates.h"
#include "player_config.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

static int cont = 0; //debug

void player_on_hit(void *owner, Hitbox *attacker) {
    Player *p = (Player *)owner;
    p->combatEvents.gotHit = true;
    p->combatEvents.gotHitBy = attacker;
}

void player_on_deflected(void *owner, Hitbox *attacker) {
    Player *p = (Player *)owner;
    p->combatEvents.gotDeflected = true;
    p->combatEvents.gotDeflectedBy = attacker;
}

float get_gravity(void){
    return 1200.0f;
}

void player_change_state(Player *p, PlayerState *newState){
    reset_combat_event_results(&p->combatEvents);
    p->currentState->exit(p);
    p->currentState = newState;
    p->currentState->init(p);
    p->comboReady = false;
}

int get_horizontal_input(void) { 
    int direction = 0;
    if (IsKeyDown(KEY_D)) direction += 1;
    else if (IsKeyDown(KEY_A)) direction -= 1;
    return direction;
}

float get_dx_variation_from_input(Player *p, int inputValue, float dt) { 
    if (inputValue > 0) {
        p->flip = false;
    } else if (inputValue < 0) { 
        p->flip = true;
    }
    return inputValue * p->speed * dt;
}

ActionResult get_input_actions(void){
    return (ActionResult){
        .atk = IsKeyPressed(KEY_J),//IsMouseButtonPressed(MOUSE_BUTTON_LEFT),
        .Satk = IsKeyDown(KEY_K),//IsMouseButtonReleased(MOUSE_BUTTON_RIGHT),
        .block = IsKeyDown(KEY_L),//IsMouseButtonDown(MOUSE_BUTTON_RIGHT),
        .jump = IsKeyPressed(KEY_I)
    };
}

void update_player_position(Player *p, World *w, float goalX, float goalY) {
    MoveResult collisionResult = world_move(w, &p->pushbox, goalX, goalY);
    p->pushbox.rect.x = collisionResult.position.x;
    p->pushbox.rect.y = collisionResult.position.y;
    p->x = p->pushbox.rect.x;
    p->y = p->pushbox.rect.y;

    p->hurtbox.rect.x = p->x + PLAYER_HURT_BOX_X_OFFSET;
    p->hurtbox.rect.y = p->y + PLAYER_HURT_BOX_Y_OFFSET;
    if (p->atk1box.active) update_atk1_box_position(p);
    if (p->atk2box.active) update_atk2_box_position(p);
    if (p->atk3box.active) update_atk3_box_position(p);
    if (p->blockbox.active) update_block_box_position(p);
    // if (p->chargeAtkbox.active) update_chargeAtk_box_position(p);

    if (collisionResult.hitRight || collisionResult.hitLeft) {
        p->dx = 0;
    }

    if (collisionResult.hitCeiling || collisionResult.hitGround) {
        p->dy = 0;
    }
    
    p->onFloor = collisionResult.hitGround;
}

void player_init(Player *p, World *w, float x, float y){
    p -> hp  = 100;
    p -> sta = 100;
    p -> h = PLAYER_HEIGHT;
    p -> w = PLAYER_WIDTH;
    p -> x   = x;
    p -> y   = y;
    p -> dx  = 0.0f;
    p -> dy  = 0.0f;
    p -> atkTimer = 0.0f;
    p -> chargeTimer = 0.0f;
    p -> onFloor = false;
    p -> speed = PLAYER_SPEED; 
    p -> isPlayer = true;
    p -> flip = false;  
    p -> comboReady = false;
    p-> currentState = &playerIdleState;
    p-> currentState->init(p);
    p-> spritesheet = LoadTexture(spritesheetAddress);
    SetTextureFilter(p->spritesheet, TEXTURE_FILTER_POINT);

    p -> pushbox = (Hitbox){
        .owner = p,
        .hitboxType = BOX_PUSH,
        .hitboxOwnerType = PLAYER,
        .active = true,
        .rect = {p->x, p->y, PLAYER_PUSH_BOX_WIDTH, PLAYER_PUSH_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = NULL
        };

    p -> atk1box = (Hitbox) {
        .owner = p,
        .hitboxType = BOX_ATK,
        .hitboxOwnerType = PLAYER,
        .active = false,
        .rect ={p->x, p->y + PLAYER_ATK1_BOX_Y_OFFSET, PLAYER_ATK1_BOX_WIDTH, PLAYER_ATK1_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = NULL
        };

    p -> atk2box = (Hitbox) {
        .owner = p,
        .hitboxType = BOX_ATK,
        .hitboxOwnerType = PLAYER,
        .active = false,
        .rect = {p->x, p->y + PLAYER_ATK2_BOX_Y_OFFSET, PLAYER_ATK2_BOX_WIDTH, PLAYER_ATK2_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = NULL
        };

    p -> atk3box = (Hitbox) {
        .owner = p,
        .hitboxType = BOX_ATK,
        .hitboxOwnerType = PLAYER,
        .active = false,
        .rect = {p->x, p->y + PLAYER_ATK3_BOX_Y_OFFSET, PLAYER_ATK3_BOX_WIDTH, PLAYER_ATK3_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = NULL
        };
                        
    p -> chargeAtkbox = (Hitbox) {
        .owner = p,
        .hitboxType = BOX_ATK,
        .hitboxOwnerType = PLAYER,
        .active = false,
        .rect = {p->x, p->y + PLAYER_CHARGEATK_BOX_Y_OFFSET, PLAYER_CHARGEATK_BOX_WIDTH, PLAYER_CHARGEATK_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = NULL
        };
                     
    p -> blockbox = (Hitbox) {
        .owner = p,
        .hitboxType = BOX_BLOCK,
        .hitboxOwnerType = PLAYER,
        .active = false,
        .rect = {p->x + PLAYER_BLOCK_BOX_X_OFFSET, p->y + PLAYER_BLOCK_BOX_Y_OFFSET, PLAYER_BLOCK_BOX_WIDTH, PLAYER_BLOCK_BOX_HEIGHT},
        .on_deflected = player_on_deflected,
        .on_hit = NULL
        };
           
                        
    p -> hurtbox = (Hitbox) {
        .owner = p,
        .hitboxType = BOX_HURT,
        .hitboxOwnerType = PLAYER,
        .active = false,
        .rect = {p->x + PLAYER_HURT_BOX_X_OFFSET, p->y + PLAYER_HURT_BOX_Y_OFFSET, PLAYER_HURT_BOX_WIDTH, PLAYER_HURT_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = player_on_hit
        };

    p -> combatEvents = (CombatEventResult) {
        .gotDeflected = false,
        .gotDeflectedBy = NULL,
        .gotHit = false,
        .gotHitBy = NULL,
    };

    world_add_hitbox(w, &p->pushbox);
    world_add_hitbox(w, &p->atk1box);
    world_add_hitbox(w, &p->atk2box);
    world_add_hitbox(w, &p->atk3box);
    world_add_hitbox(w, &p->chargeAtkbox);
    world_add_hitbox(w, &p->hurtbox);
    world_add_hitbox(w, &p->blockbox);
    init_states_textures(p);
    
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