#include <SDL2/SDL.h>

#include <stdio.h>

#include "entity.h"

/*
 * Allocates and creates entity struct. The sprite path is a bmp file. Initializes all fields to 0
 * Returns: pointer to the created struct or NULL on failier
*/
struct entity * init_entity(SDL_Renderer * renderer, const char * sprite_path) {
    struct entity * ent = malloc(sizeof(struct entity));

    ent->height = 0;
    ent->width = 0;

    ent->x = 0;
    ent->y = 0;
    ent->x_vel = 0;
    ent->y_vel = 0;
    ent->x_acc = 0;
    ent->y_acc = 0;

    //creates texture from the sprite file
    SDL_Surface * surf = SDL_LoadBMP(sprite_path);
    if(surf == NULL) {
        fprintf(stderr, "Error Loading Sprite File: %s\n", SDL_GetError());

        free(ent);
        //free_entity(ent); not needed 
        return NULL;
    }

    ent->texture = SDL_CreateTextureFromSurface(renderer, surf);
    if(ent->texture == NULL) {
        fprintf(stderr, "Error Creating Texture From Surface: %s\n", SDL_GetError());

        SDL_FreeSurface(surf);
        free(ent);
        return NULL;
    }

    SDL_FreeSurface(surf);

    return ent;
}

/*
 * Frees an entity
 * Returns: null pointer
*/
struct entity * free_entity(struct entity * ent) {
    SDL_DestroyTexture(ent->texture);
    free(ent);

    return NULL;
}

/*
 * Updates velocity and position once
 * Returns: nothing
*/

void update_position(struct entity * ent) {
    ent->x_vel += ent->x_acc;
    ent->y_vel += ent->y_acc;

    ent->x += ent->x_vel;
    ent->y += ent->y_vel;
}

/*
 * Renderes an entity
 * Returns: 0 on success or -1 on failier
*/
int render_entity(SDL_Renderer * renderer, const struct entity * ent) {
    //creates a rectangle for where to render based on location and size
    SDL_Rect dstrect = {ent->x, ent->y, ent->height, ent->width};

    return SDL_RenderCopy(renderer, ent->texture, NULL, &dstrect);
}
