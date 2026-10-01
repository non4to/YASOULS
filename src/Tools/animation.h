#ifndef ANIMATION_H
#define ANIMATION_H
#include <raylib.h>

typedef struct Animation {
    Texture *spriteSheet;
    Vector2 frameSize;
    int spriteSheetLineNumber;
    int finalFrameIndex;
    bool loop; 
    float *frameTimes; //ex:. static const float idleTimes[] = { 0.1f, 0.2f, 0.05f, ... };
    float counter;
    int currentFrame;   
} Animation;

Animation create_animation(const Texture *spritesheet, const Vector2 frameSize, 
                            const int spriteSheetLineNumber, const int finalFrameIndex, 
                            const bool loop, const float *frameTimes);
void animation_init(Animation *a);
void animation_update(Animation *a, float dt); 
void animation_draw(Animation *a, Vector2 position, bool flip);
void animation_end(Animation *a);

#endif