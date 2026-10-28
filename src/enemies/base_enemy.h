#ifndef BASE_ENEMY_H
#define BASE_ENEMY_H

#include <stdbool.h>
#include <raylib.h>
#include "../world/world.h"

typedef struct Enemy {
    float hp;
    float w;
    float h;
    float x;
    float y;
    bool isPlayer; // Útil caso queira diferenciar nas colisões futuramente
    Hitbox pushbox;
    Hitbox hurtbox;
    CombatEventResult combatEvents;
} Enemy;

void enemy_init(Enemy *e, World *w, float x, float y);
void enemy_update(Enemy *e, World *w, float dt);
void enemy_draw(Enemy *e);
void enemy_on_hit(void *owner, Hitbox *attacker);
void enemy_on_deflected(void *owner, Hitbox *attacker);

#endif // BASE_ENEMY_H