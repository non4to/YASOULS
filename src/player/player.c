#include "player.h"
#include "playerStates.h"
#include "player_config.h"
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
    if (inputValue > 0) {
        p->flip = false;
    } else if (inputValue < 0) { 
        p->flip = true;
    }
    return inputValue * p->speed * dt;
}

ActionResult get_input_actions(void){
    return (ActionResult){
        .atk = IsMouseButtonPressed(MOUSE_BUTTON_LEFT),
        .block = IsMouseButtonDown(MOUSE_BUTTON_RIGHT),
        .jump = IsKeyPressed(KEY_SPACE)
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
    p -> onFloor = false;
    p -> speed = PLAYER_SPEED; 
    p -> isPlayer = true;
    p -> flip = false;  
    p-> currentState = &playerIdleState;
    p-> currentState->init(p);
    p-> spritesheet = LoadTexture(spritesheetAddress);
    p -> pushbox = (Hitbox){p, BOX_PUSH, true, 
                        {p->x, 
                        p->y,
                        PLAYER_PUSH_BOX_WIDTH,
                        PLAYER_PUSH_BOX_HEIGHT}
                    };
    p -> atk1box = (Hitbox) {p, BOX_ATK, false,
                        {p->x + PLAYER_ATK1_BOX_X_OFFSET, 
                        p->y + PLAYER_ATK1_BOX_X_OFFSET,
                        PLAYER_ATK1_BOX_WIDTH,
                        PLAYER_ATK1_BOX_HEIGHT}
                    };
    p -> hurtbox = (Hitbox) {p, BOX_HURT, true,
                        {p->x + PLAYER_HURT_BOX_X_OFFSET,
                        p->y + PLAYER_HURT_BOX_Y_OFFSET,
                        PLAYER_HURT_BOX_WIDTH,
                        PLAYER_HURT_BOX_HEIGHT}
                    };

    world_add_hitbox(w, &p->pushbox);
    world_add_hitbox(w, &p->atk1box);
    world_add_hitbox(w, &p->hurtbox);
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