#include <SDL2/SDL.h>

#ifndef  PLAYER_H
#define PLAYER_H

struct player{
    float x;
    float y;

    float dx;
    float dy;

    int onGround;
    SDL_Texture *texture;
}

#endif
