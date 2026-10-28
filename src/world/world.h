#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>

#define MAX_PUSHBOXES 100
#define MAX_HURTBOXES 100
#define MAX_ATKBOXES 100
#define MAX_BLOCKBOXES 100
#define MAX_TARGETS 10

typedef struct CombatEventResult {
    bool gotHit;
    void *gotHitBy;
    bool gotDeflected;
    void *gotDeflectedBy;
} CombatEventResult;

typedef enum HitboxOwnerType {
    PLAYER,
    ENEMY,
    SCENARY
} HitboxOwnerType;

typedef enum HitboxType {
    BOX_PUSH,
    BOX_HURT,
    BOX_ATK,
    BOX_BLOCK
} HitboxType;

typedef struct Hitbox {
    void *owner;
    HitboxType hitboxType;
    HitboxOwnerType hitboxOwnerType;
    bool active;
    Rectangle rect;
    void *targetsHit[MAX_TARGETS];
    void (*on_hit)(void *owner, struct Hitbox *attacker);
    void (*on_deflected)(void *owner, struct Hitbox *attacker);
} Hitbox;

typedef struct MoveResult {
    Vector2 position;
    bool hitGround;  // Collided with ground
    bool hitCeiling; // Collided with ceiling
    bool hitLeft;    // Collided with left
    bool hitRight;   // Collided with right
} MoveResult;

typedef struct World {
    Hitbox *pushboxes[MAX_PUSHBOXES];
    Hitbox *hurtboxes[MAX_HURTBOXES];
    Hitbox *atkboxes[MAX_ATKBOXES];
    Hitbox *blockboxes[MAX_BLOCKBOXES];
    int pushboxesCount;
    int hurtboxesCount;
    int atkboxesCount;
    int blockboxesCount;
} World;

void add2HitList(Hitbox *attacker, Hitbox *receiver);
bool was_hit_before(Hitbox *attacker, Hitbox *receiver);
void world_init(World *w);
void world_add_hitbox(World *w, Hitbox *h);
void world_draw(World *w);
void world_update(World *w);
void world_check_atks(World *w);
void reset_combat_event_results(CombatEventResult *c);
MoveResult world_move(World *w, Hitbox *h, float xGoal, float yGoal);
#endif // WORLD_H