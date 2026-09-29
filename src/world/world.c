#include "world.h"

void world_init(World *w) {
    w->pushboxesCount = 0;
    w->hurtboxesCount = 0;
    w->atkboxesCount = 0;
    w->blockboxesCount = 0;
}

void world_add_hitbox(World *w, Hitbox *h) {
    switch (h->hitboxType)
    {
    case BOX_PUSH:
        if (w->pushboxesCount < MAX_PUSHBOXES) {
            w->pushboxes[w->pushboxesCount] = h;
            w->pushboxesCount++;
        }
        break;
    case BOX_HURT:
        if (w->hurtboxesCount < MAX_HURTBOXES) {
            w->hurtboxes[w->hurtboxesCount] = h;
            w->hurtboxesCount++;
        }
        break;
    case BOX_ATK:
        if (w->atkboxesCount < MAX_ATKBOXES) {
            w->atkboxes[w->atkboxesCount] = h;
            w->atkboxesCount++;
        }
        break;
    case BOX_BLOCK:
        if (w->blockboxesCount < MAX_BLOCKBOXES) {
            w->blockboxes[w->blockboxesCount] = h;
            w->blockboxesCount++;
        }
        break;
    }
}

MoveResult world_move(World *w, Hitbox *h, float xGoal, float yGoal) {
    //To move, only the pushboxes are checked!
    MoveResult output = {(Vector2){xGoal, yGoal}, false, false, false, false};
    Rectangle testRectX = {output.position.x, h->rect.y, h->rect.width, h->rect.height};


    //First, check X collisions
    for (int i=0; i < w->pushboxesCount; i++) {
        Hitbox *aPushBox = w->pushboxes[i]; //just the adress
        if (h == aPushBox) continue;         //ignore self
        if (CheckCollisionRecs(testRectX, aPushBox->rect)) {
            if (xGoal > h->rect.x) { //going right, touch other left
                output.position.x = aPushBox->rect.x - h->rect.width;
                output.hitRight = true;
            } else if (xGoal < h->rect.x) { //going left, touch other right
                output.position.x = aPushBox->rect.x + aPushBox->rect.width;
                output.hitLeft = true;
            }
            break;
        }
    }

    Rectangle testRectY = {output.position.x, output.position.y, h->rect.width, h->rect.height};
    //Then, check Y collisions
    for (int i=0; i < w->pushboxesCount; i++) {
        Hitbox *aPushBox = w->pushboxes[i]; //just the adress
        if (h == aPushBox) continue;         //ignore self
        if (CheckCollisionRecs(testRectY, aPushBox->rect)) {
            if (yGoal > h->rect.y) { //going down, touch other top
                output.position.y = aPushBox->rect.y - h->rect.height;
                output.hitGround = true;
            } else if (yGoal < h->rect.y) { //going up, touch other botton
                output.position.y = aPushBox->rect.y + aPushBox->rect.height;
                output.hitCeiling = true;
            }
            break;
        }
    }

    //onFloorCheck
    //The collision doesnt really count the border, so this checks if 1 pixel would be inside anything.
    //If it would, it is still hitting the groud!
    if (!output.hitGround) {
        Rectangle groundTestRect = {output.position.x, output.position.y + 1.0f, h->rect.width, h->rect.height};
        for (int i = 0; i < w->pushboxesCount; i++) {
            Hitbox *aPushBox = w->pushboxes[i];
            if (h == aPushBox) continue;
            if (CheckCollisionRecs(groundTestRect, aPushBox->rect)) {
                output.hitGround = true;
                break;
            }
        }
    }

    return output;
}

void world_draw(World *w) {
    //draw all push boxes
    for (int i=0; i < w->pushboxesCount; i++) {
        DrawRectangleLines(w->pushboxes[i]->rect.x, w->pushboxes[i]->rect.y, w->pushboxes[i]->rect.width, w->pushboxes[i]->rect.height, BLACK);                   
    }
}