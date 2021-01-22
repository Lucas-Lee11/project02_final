#include <SDL2/SDL.h>

#include <stdio.h>

#include "entity.h"

/*
 * Allocates and creates entity struct. The sprite path is a bmp file. Initializes all fields to 0
 * Returns: pointer to the created struct or NULL on failier
*/
struct entity * init_entity(const int id, const int height, const int width) {
    struct entity * ent = malloc(sizeof(struct entity));

    ent->height = height;
    ent->width = width;

    ent->x = 0;
    ent->y = 0;
    ent->x_vel = 0;
    ent->y_vel = 0;
    ent->x_acc = 0;
    ent->y_acc = 0;

    ent->id = id;
    ent->type = GENERIC;

    return ent;
}

/*
 * Frees an entity
 * Returns: null pointer
*/

struct entity * free_entity(struct entity * ent) {
    free(ent);

    return NULL;
}

/*
 * Updates velocity and position once
 * Returns: void
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

int render_entity(SDL_Renderer * renderer, SDL_Texture * tex,  struct entity * ent) {
    //creates a rectangle for where to render based on location and size
    SDL_Rect dstrect = {ent->x, ent->y, ent->height, ent->width};

    int out = SDL_RenderCopy(renderer, tex, NULL, &dstrect);

    return out;
}

/*
 * copies entity from src to dest
 * Retruns: void
*/

void cp_entity(struct entity dest, const struct entity src) {
    dest->id = src->id;
    dest->type = src->type;

    dest->x = src->x;
    dest->y = src->y;
    dest->x_vel = src->x_vel;
    dest->y_vel = src->y_vel;
    dest->x_acc = src->x_acc;
    dest->y_acc = src->y_acc;

    dest->height = src->height;
    dest->width = src->width;

    dest->collision = src->collision;
    dest->action_state = src->action_state;
}
