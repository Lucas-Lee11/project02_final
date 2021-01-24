#include <SDL2/SDL.h>
#include "entity.h"

#ifndef RENDERING_H_
#define RENDERING_H_

//window stuff
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//each has a respective texture which needs to be initlized indiviually 
enum {
    R_INVIS,
    R_PLAYER,
    R_TILE,
    NUM_TEXTS
};

//renders a texture to the screen
int render_ent(SDL_Renderer * renderer, SDL_Texture ** texs, 
        const struct entity * ent, const double x_ref, const double y_ref);


#endif
