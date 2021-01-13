#include <SDL2/SDL.h>

#ifndef  PLAYER_H
#define PLAYER_H

#define PLAYER_IMG_PATH "./player.bmp"
#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 50

struct player{
    float x;
    float y;

    float dx;
    float dy;

    int height;
    int width;

    int onGround;
    SDL_Texture *texture;
};

struct player * init_player(SDL_Renderer * renderer);
struct player * free_player(struct player * player);
int render_player(SDL_Renderer * renderer, struct player * player);

#endif
