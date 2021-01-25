#include <SDL2/SDL.h>
#include "entity.h"

#ifndef RENDERING_H_
#define RENDERING_H_

//window stuff
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define TILE_SIZE 64

//each has a respective texture which needs to be initlized indiviually
enum {
    R_INVIS,
    R_PLAYER,
    R_TILE,
    NUM_TEXTS
};

//renders a texture to the screen
int render_ent(SDL_Renderer * renderer, SDL_Texture ** texs,
        const struct entity * ent, const double x_refi, const double y_refi,
        const int win_width, const int win_height,
        const int stage_width, const int stage_height,
        const int tile_size);


#endif
