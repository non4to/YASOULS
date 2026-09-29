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
    World world;
    world_init(&world);
    int screenWidth = 600;
    int screenHeight = 400;
    char *title = "YASOULS";

    Player player;
    player_init(&player, 20, 40, 50, 100, 300.0);

    //Test platforms
    Hitbox plat1 = {BOX_PUSH, true, (Rectangle){400,380,200,20}};
    world_add_hitbox(&world, &plat1);
    Hitbox plat2 = {BOX_PUSH, true, (Rectangle){550,300,50,20}};
    world_add_hitbox(&world, &plat2);
    Hitbox floor1 = {BOX_PUSH, true, (Rectangle){0,screenHeight,screenWidth,20}};
    world_add_hitbox(&world, &floor1);
    //End test platforms

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        update(&player, &world, dt);
        draw(&player, &world);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

