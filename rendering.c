#include <SDL2/SDL.h>

#include "entity.h"
#include "rendering.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/*
 * renders the entity on screen based on the entity
 * MAKE SURE THAT TEXTURES ARE BIG ENOUGH, THE SIZE OF NUM_TEXTS
 * if no texture is needed, the texture should be set to NULL and it will be handled with additional casework
 * Returns: 0 on success else -1
*/

int render_ent(SDL_Renderer * renderer, SDL_Texture ** texs, 
        const struct entity * ent, const double x_refi, const double y_refi,
        const int win_width, const int win_height, const int tile_size) {

    int x_ref = x_refi - win_width/2;
    int y_ref = y_refi - win_height/2;

    x_ref = MIN(MAX(x_ref, 0), (win_width * tile_size) - win_width);
    y_ref = MIN(MAX(y_ref, 0), (win_height * tile_size) - win_height);

    int out;

    int x_rel = (int) (ent->x - x_ref);
    int y_rel = (int) (ent->y - y_ref);

    SDL_Texture * tex = texs[ent->rend_id];

    if(tex != NULL) {
        SDL_Rect dstrect = {x_rel, y_rel, ent->height, ent->width};

        out = SDL_RenderCopy(renderer, tex, NULL, &dstrect);
    } else {
        switch(ent->rend_id) {
            case R_TILE:
                SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255);

                SDL_Rect dstrect = {x_rel, y_rel, ent->height, ent->width};

                out = SDL_RenderFillRect(renderer, &dstrect);
                break;
            default:
                break;
        }
    }

    return out;
}
