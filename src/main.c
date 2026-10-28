#include <raylib.h>
#include <stdbool.h>
#include "player/player.h"
#include "enemies/base_enemy.h"
#include "world/world.h"

//erase this down later
#include <stdio.h>

void update(Player *p, Enemy *e, World *w, float dt) {
    player_update(p, w, dt);
    enemy_update(e, w, dt);
    world_update(w);



}

void draw(Player *p, Enemy *e, World *w) {
    player_draw(p);

    //Collisions DEBUG
    world_draw(w);


}

int main(void) {
    const int gameWidth  = 400;
    const int gameHeight = 200;
    int screenWidth = gameWidth * 3;
    int screenHeight = gameHeight * 3;

    char *title = "YASOULS";
    InitWindow(screenWidth, screenHeight, title);
    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    World world;
    world_init(&world);
    Player player;
    player_init(&player, &world, 50, 100);
    Enemy enemy1;
    enemy_init(&enemy1, &world, 30, 140);

    //Test platforms
    Hitbox plat1 = {NULL, BOX_PUSH, SCENARY, true, (Rectangle){200,gameHeight-40,200,20}};
    world_add_hitbox(&world, &plat1);
    Hitbox plat2 = {NULL, BOX_PUSH, SCENARY,  true, (Rectangle){300,gameHeight-120,100,20}};
    world_add_hitbox(&world, &plat2);
    Hitbox plat3 = {NULL, BOX_PUSH, SCENARY,  true, (Rectangle){0,gameHeight-140,200,20}};
    world_add_hitbox(&world, &plat3);
    Hitbox floor1 = {NULL, BOX_PUSH, SCENARY,  true, (Rectangle){0,gameHeight-20,gameWidth,20}};
    world_add_hitbox(&world, &floor1);
    //End test platforms

    // //Test HurtBoxes
    //     // Hitbox body1 = {NULL, BOX_PUSH, true, (Rectangle){520,340,20,40}};
    //     Hitbox hurt1 = {NULL, BOX_HURT, ENEMY, true, (Rectangle){30,gameHeight-40,20,20}};
    //     // world_add_hitbox(&world, &body1);
    //     world_add_hitbox(&world, &hurt1);
    // //End testHurtBoxes

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        BeginDrawing();
        update(&player, &enemy1, &world, dt);
        BeginTextureMode(target);
            ClearBackground(WHITE);
            draw(&player, &enemy1, &world);
        EndTextureMode();
        ClearBackground(WHITE);
        Rectangle srcRec = { 0.0f, 0.0f, (float)gameWidth, (float)-gameHeight };
        Rectangle destRec = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(target.texture, srcRec, destRec, origin, 0.0f, WHITE);
        EndDrawing();
    }
    UnloadRenderTexture(target);
    UnloadTexture(player.spritesheet);
    CloseWindow();
    return 0;
}

