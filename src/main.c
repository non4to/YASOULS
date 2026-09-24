#include <raylib.h>
#include <stdbool.h>
#include "player/player.h"
//erase this down later
#include <stdio.h>


void update(Player *p, float dt) {
    p->currentState->update(p, dt);
}

void draw(Player *p) {
    p->currentState->draw(p); 
}


int main(void) {
    int width = 600;
    int heigh = 400;
    char *title = "YASOULS";

    Player player;
    player_init(&player, 50.0, 50.0, 1.0, 2.0);

    InitWindow(width, heigh, title);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(GRAY);

        update(&player, dt);
        draw(&player);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

