#include <SDL2/SDL.h>

#include "entll.h"
#include "entity.h"

#ifndef STAGE_H
#define STAGE_H

//In tiles
#define STAGE_WIDTH 40
#define STAGE_HEIGHT 20

#define STAGE_RENDER_WIDTH 20
#define STAGE_RENDER_HEIGHT 12

//In pixels
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


#define TILE_SIZE 64


struct stage{
    int data[STAGE_WIDTH][STAGE_HEIGHT];

    struct entll * entll;
    struct entity * player;

    SDL_Point camera;

};

struct stage * init_stage(char * filename);
int load_tiles(struct stage * stage, char * filename);
int render_stage (SDL_Renderer * renderer, struct stage * stage);
int render_tiles(SDL_Renderer * renderer, struct stage * stage);
int update_camera (struct stage * stage);
struct stage * free_stage(struct stage * stage);

#endif
