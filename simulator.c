//goal is to no use any sdl stuff here
#include "input.h"
#include "entll.h"
#include "entity.h"
#include "rendering.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#define MOVEMENT_EPSILON 0.2

/*
 * rounds small numbers to 0
 * Returns: void
*/

void round_ep(double * n) {
    *n = fabs(*n) < MOVEMENT_EPSILON ? 0 : *n;
}


/*
 * updates position and surroundings of a player
 * Returns: void
*/

void update_player(struct entity * ent, 
        struct entll * loaded, struct entll * unloaded, 
        int * gamestate, int input_key) {

    const double dacc = 0.3;
    const double ddacc = 0.1;
    //change  acceleration
    switch(input_key) {
        case P_UP:
            ent->y_acc -= dacc;
            break;
        case P_DOWN:
            ent->y_acc += dacc;
            break;
        case P_RIGHT:
            ent->x_acc += dacc;
            break;
        case P_LEFT:
            ent->x_acc -= dacc;
            break;
        default:
            break;
    }
    ent->x_vel += ent->x_acc;
    ent->x += ent->x_vel;
    ent->y += ent->y_vel;
    ent->y_vel += ent->y_acc;

    ent->x_acc -= ent->x_acc * ddacc;
    ent->x_vel -= ent->x_vel * ddacc;
    ent->y_acc -= ent->y_acc * ddacc;
    ent->y_vel -= ent->y_vel * ddacc;

    //making getting to 0 if you are less than some epsilon
    round_ep(&(ent->x_acc));
    round_ep(&(ent->y_acc));
    round_ep(&(ent->x_vel));
    round_ep(&(ent->y_vel));
}

/*
 * updates both the given entitiy and other entities as needed with one tick of the game
 * this function is badically just to choose the right actual updater function based on type
 * Returns: void
*/

void update_ent(struct entll * ent, 
        struct entll * loaded, struct entll * unloaded, 
        int * gamestate, int input_key) {

    switch(ent->ent.type) {
        case PLAYER:
            update_player(&(ent->ent), loaded, unloaded, gamestate, input_key);
            break;
        default:
            break;
    }

    return;
}

/*
 * loads tiles onto the front of the given entll
 * Returns: pointer to dest
*/

struct entll * load_tiles(struct entll * dest, const int height, const int width, const int tile_size, const char * level_path) {
    FILE * fp = fopen(level_path, "r");

    if(fp == NULL) {
        fprintf(stderr, "Error loading level_path: %s\n", strerror(errno)); 

        return dest;
    }

    int tile_code; 
    char dump;

    int x, y;
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            fscanf(fp, "%d", &tile_code);
            if(tile_code == 0) continue;

            struct entity * tmp = init_entity(tile_size, tile_size);
            tmp->type = TILE;
            tmp->x = x * tile_size;
            tmp->y = y * tile_size;
            tmp->rend_id = R_TILE;

            dest = push(dest, tmp);

            free_entity(tmp);
        }

        fscanf(fp, "%c", &dump);
    }

    fclose(fp);

    return dest;
}
