#include <SDL2/SDL.h>

#include "entity.h"
#include "rendering.h"

/*
 * renders the entity on screen based on the entity
 * MAKE SURE THAT TEXTURES ARE BIG ENOUGH, THE SIZE OF NUM_TEXTS
 * if no texture is needed, the texture should be set to NULL and it will be handled with additional casework
 * Returns: 0 on success else -1
*/

int render_ent(SDL_Renderer * renderer, SDL_Texture ** texs, 
        const struct entity * ent, const double x_ref, const double y_ref) {

    int out;

    int x_rel = (int) (ent->x - x_ref);
    int y_rel = (int) (ent->y - y_ref);

    SDL_Texture * tex = texs[ent->rend_id];

    if(tex != NULL) {
        SDL_Rect dstrect = {x_rel, y_rel, ent->x, ent->y};

        out = SDL_RenderCopy(renderer, tex, NULL, &dstrect);
    } else {
        switch(ent->rend_id) {
            case R_TILE:
                SDL_SetRenderDrawColor(renderer, 0, 0, 3, 255);

                SDL_Rect dstrect = {x_rel, y_rel, ent->height, ent->width};

                out = SDL_RenderFillRect(renderer, &dstrect);
                break;
            default:
                break;
        }
    }

    return out;
}
