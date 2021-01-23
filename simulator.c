//goal is to no use any sdl stuff here
#include "input.h"
#include "entll.h"
#include "entity.h"

#include <stdio.h>

#include <string.h>
#include <errno.h>
//TODO: THE ACTUAL GAME UPDATER FUNCTIONS GO HERE

/*
 * updates both the given entitiy and other entities as needed with one tick of the game
 * this function is badically just to choose the right actual updater function based on type
 * Returns: void
*/

void update_ent(struct entll * ent, 
        struct entll * loaded, struct entll * unloaded, 
        int gamestate, int input_key) {
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

            struct entity * tmp = init_entity(tile_size, tile_size);
            tmp->type = TILE;
            tmp->x = x * tile_size;
            tmp->y = y * tile_size;

            dest = push(dest, tmp);

            free_entity(tmp);
        }

        fscanf(fp, "%c", &dump);
    }

    fclose(fp);

    return dest;
}
