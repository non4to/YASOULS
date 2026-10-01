#include <raylib.h>
#include <stdbool.h>
#include "player/player.h"
#include "world/world.h"

//erase this down later
#include <stdio.h>

void update(Player *p, World *w, float dt) {
    player_update(p, w, dt);


}

void draw(Player *p, World *w) {
    player_draw(p);

    //Collisions DEBUG
    world_draw(w);

}

int main(void) {
    int screenWidth = 600;
    int screenHeight = 400;
    char *title = "YASOULS";
    InitWindow(screenWidth, screenHeight, title);

    World world;
    world_init(&world);
    Player player;
    player_init(&player, &world, 50, 100);

    //Test platforms
    Hitbox plat1 = {NULL, BOX_PUSH, true, (Rectangle){400,380,200,20}};
    world_add_hitbox(&world, &plat1);
    Hitbox plat2 = {NULL, BOX_PUSH, true, (Rectangle){550,300,50,20}};
    world_add_hitbox(&world, &plat2);
    Hitbox floor1 = {NULL, BOX_PUSH, true, (Rectangle){0,screenHeight,screenWidth,20}};
    world_add_hitbox(&world, &floor1);
    //End test platforms
    //Test HurtBoxes
        // Hitbox body1 = {NULL, BOX_PUSH, true, (Rectangle){520,340,20,40}};
        // Hitbox hurt1 = {NULL, BOX_HURT, true, (Rectangle){523,350,14,30}};
        // world_add_hitbox(&world, &body1);
        // world_add_hitbox(&world, &hurt1);
    //End testHurtBoxes

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        update(&player, &world, dt);
        draw(&player, &world);
        EndDrawing();
    }
    
    UnloadTexture(player.spritesheet);
    CloseWindow();
    return 0;
}

