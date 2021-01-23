#include <SDL2/SDL.h>

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include "entity.h"


/*
 * Allocates and creates entity struct. The sprite path is a bmp file. Initializes all fields to 0
 * Returns: pointer to the created struct or NULL on failier
*/
struct entity * init_entity(const int height, const int width) {
    struct entity * ent = malloc(sizeof(struct entity));

    int fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1) {
        fprintf(stderr, "Error opening /dev/urandom: %s\n", strerror(errno));

        free(ent);

        return NULL;
    }

    read(fd, &(ent->id), sizeof(ent->id));

    ent->height = height;
    ent->width = width;

    ent->x = 0;
    ent->y = 0;
    ent->x_vel = 0;
    ent->y_vel = 0;
    ent->x_acc = 0;
    ent->y_acc = 0;

    ent->type = GENERIC;

    close(fd);

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

//FIXME add in a slightly better spot oppoosed to entity where it might not fit
/*


 * Renderes an entity
 * Returns: 0 on success or -1 on failier
 

int render_entity(SDL_Renderer * renderer, struct stage * stage, struct entity * ent) {

    int out;

    double cam_x = stage->ent_arr[0].x;
    double cam_y = stage->ent_arr[0].y;

    int rel_x = (int) (ent->x - cam_x);
    int rel_y = (int) (ent->y - cam_y);

    if(ent->type == PLAYER){
        SDL_Surface * surf = SDL_LoadBMP(PLAYER_IMG_PATH);
        if(surf == NULL) {
            fprintf(stderr, "Error Loading Sprite File: %s\n", SDL_GetError());

            free(ent);
            //free_entity(ent); not needed
            return -1;
        }

        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
        if(texture == NULL) {
            fprintf(stderr, "Error Creating Texture From Surface: %s\n", SDL_GetError());

            SDL_FreeSurface(surf);
            free(ent);
            return -1;
        }

        SDL_FreeSurface(surf);


        //creates a rectangle for where to render based on location and size
        SDL_Rect dstrect = {rel_x, rel_y, ent->height, ent->width};

        out = SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_DestroyTexture(texture);
    }
    else if(ent->type == TILE){
        int n = stage->data[(int)ent->x/TILE_SIZE][(int)ent->y/TILE_SIZE] * 35;

        if(n > 0){
            //printf("%d %d %d\n", y ,x, n);
            int color[3];
            color[0] = 0; color[1] = 0; color[2] = 0;
            color[n%3] = n;

            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);

            //printf("%d %d\n",x ,y );
            SDL_Rect dstrect = {rel_x, rel_y, TILE_SIZE, TILE_SIZE};
            out = SDL_RenderFillRect(renderer, &dstrect);

        }

    }

    return out;
}
*/

/*
 * copies entity from src to dest
 * Retruns: void
*/

void cp_entity(struct entity * dest, const struct entity * src) {
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


