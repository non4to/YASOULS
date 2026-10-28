#include "base_enemy.h"
#include <stdio.h>

// Definições temporárias de tamanho (você pode ajustar depois)
#define ENEMY_WIDTH 32
#define ENEMY_HEIGHT 64

#define ENEMY_PUSH_BOX_WIDTH 20
#define ENEMY_PUSH_BOX_HEIGHT 40
#define ENEMY_HURT_BOX_WIDTH 20
#define ENEMY_HURT_BOX_HEIGHT 40

#define ENEMY_HURT_BOX_X_OFFSET 0
#define ENEMY_HURT_BOX_Y_OFFSET 0

void enemy_on_hit(void *owner, Hitbox *attacker) {
    Enemy *e = (Enemy *)owner;
    e->combatEvents.gotHit = true;
    e->combatEvents.gotHitBy = attacker;
}

void enemy_on_deflected(void *owner, Hitbox *attacker) {
    Enemy *e = (Enemy *)owner;
    e->combatEvents.gotDeflected = true;
    e->combatEvents.gotDeflectedBy = attacker->owner;
}

void enemy_init(Enemy *e, World *w, float x, float y) {
    e->hp = 100;
    e->w = ENEMY_WIDTH;
    e->h = ENEMY_HEIGHT;
    e->x = x;
    e->y = y;
    e->isPlayer = false;

    e->pushbox = (Hitbox){
        .owner = e,
        .hitboxType = BOX_PUSH,
        .hitboxOwnerType = ENEMY,
        .active = true,
        .rect = {e->x, e->y, ENEMY_PUSH_BOX_WIDTH, ENEMY_PUSH_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = NULL
    };

    e->hurtbox = (Hitbox){
        .owner = e,
        .hitboxType = BOX_HURT,
        .hitboxOwnerType = ENEMY,
        .active = true,
        .rect = {e->x + ENEMY_HURT_BOX_X_OFFSET, e->y + ENEMY_HURT_BOX_Y_OFFSET, ENEMY_HURT_BOX_WIDTH, ENEMY_HURT_BOX_HEIGHT},
        .on_deflected = NULL,
        .on_hit = enemy_on_hit
    };

    e -> combatEvents = (CombatEventResult) {
        .gotDeflected = false,
        .gotDeflectedBy = NULL,
        .gotHit = false,
        .gotHitBy = NULL,
    };
    world_add_hitbox(w, &e->pushbox);
    world_add_hitbox(w, &e->hurtbox);
}

void enemy_update(Enemy *e, World *w, float dt) {
    if (e->combatEvents.gotHit) {
        printf("ouchie!\n");
        e->combatEvents.gotHit = false;  //TODO: MAKE FIRST STATES TO ENEMY. NEED TO TEST BLOCK AND CREATE PARRY STATEgog
    }
}

void enemy_draw(Enemy *e) {
    DrawRectangle((int)e->x, (int)e->y, (int)e->w, (int)e->h, RED);
}