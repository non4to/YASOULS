#include "animation.h"

Animation create_animation(const Texture *spritesheet, const Vector2 frameSize, 
                            const int spriteSheetLineNumber, const int finalFrameIndex, 
                            const bool loop, const float *frameTimes) {
    return (Animation){spritesheet, frameSize, spriteSheetLineNumber, finalFrameIndex, loop, frameTimes, 0, 0};                                
}

void animation_init(Animation *a) {
    a->counter = 0;
    a->currentFrame = 0;
}

void animation_update(Animation *a, float dt) {
    a->counter += dt;
    float currentMaxTime = a->frameTimes[a->currentFrame];
    if (a->counter > currentMaxTime) {
        if (a->currentFrame == a->finalFrameIndex) {
            if(a->loop) {a->currentFrame = 0;}
        } else {a->currentFrame++;}
        a->counter -= currentMaxTime; //this is to the case of when dt > currentMaxTime. This counts the exceed time for the next frame! This way frames dont all get delayed too much if the timer exceeds.
    }
}

void animation_draw(Animation *a, Vector2 position, bool flip) {
    int reverse = 1;
    if (flip) {reverse = -1;}    
    Rectangle frameRec = {
        .x = (float)a->currentFrame *a->frameSize.x,
        .y = (float)a->spriteSheetLineNumber *a->frameSize.y,
        .width = a->frameSize.x * reverse,
        .height = a->frameSize.y
    };
    DrawTextureRec(*a->spriteSheet, frameRec, position, WHITE);
}