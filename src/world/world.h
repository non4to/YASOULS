#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>

#define MAX_PUSHBOXES 100
#define MAX_HURTBOXES 100
#define MAX_ATKBOXES 100
#define MAX_BLOCKBOXES 100

typedef enum HitboxType {
    BOX_PUSH,
    BOX_HURT,
    BOX_ATK,
    BOX_BLOCK
} HitboxType;

typedef struct Hitbox {
    HitboxType hitboxType;
    bool active;
    Rectangle rect;
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

void world_init(World *w);
void world_add_hitbox(World *w, Hitbox *h);
void world_draw(World *w);
MoveResult world_move(World *w, Hitbox *h, float xGoal, float yGoal);
#endif // WORLD_H