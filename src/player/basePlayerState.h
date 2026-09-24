#ifndef BASE_PLAYER_STATE_H

#define BASE_PLAYER_STATE_H

typedef struct Player Player;

typedef struct PlayerState {
    void (*init)(Player *p);
    void (*update)(Player *p, float dt);
    void (*draw)(Player *p);
    void (*exit)(Player *p);
} PlayerState;

#endif