#include <SDL2/SDL.h>

#include "entity.h"

#ifndef STAGE_H
#define STAGE_H

//In pixels
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define TILE_SIZE 64

//In tiles
#define STAGE_WIDTH 40
#define STAGE_HEIGHT 20

#define STAGE_RENDER_WIDTH WINDOW_WIDTH / TILE_SIZE + 1
#define STAGE_RENDER_HEIGHT WINDOW_HEIGHT / TILE_SIZE + 1




struct stage{
    int data[STAGE_WIDTH][STAGE_HEIGHT];

    struct entity * ent_arr;

};

struct stage * init_stage(SDL_Renderer * renderer, char * filename, struct entity * ents);
int load_tiles(struct stage * stage, char * filename);
int render_stage (SDL_Renderer * renderer, struct stage * stage);
//int render_tiles(SDL_Renderer * renderer, struct stage * stage);
void update_camera (struct entity * camera);
struct stage * free_stage(struct stage * stage);

#endif
