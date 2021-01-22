#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "stage.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


/*
Creates a new stage struct
Returns a pointer to the new struct
*/
struct stage * init_stage(char * filename){

    struct stage * stage = malloc(sizeof(struct stage));

    load_tiles(stage, filename);

    stage->player = init_entity(PLAYER_HEIGHT, PLAYER_WIDTH);

    SDL_Point cam = {0,0};
    stage->camera = cam;

    return stage;

}


/*
Reads from a file to get level data
Returns 1 on success, -1 on failure
*/
int load_tiles(struct stage * stage, char * filename){

    FILE * fp = fopen(filename, "r");

    int x,y;
    char d[1];

    for(y = 0; y < STAGE_HEIGHT; y++){
        for(x = 0; x < STAGE_WIDTH; x++){
            fscanf(fp, "%d", &(stage->data[x][y]));
        }
        fscanf(fp, "%c", d);
    }

    fclose(fp);

    return 1;
}

/*
Renders the stage
Returns 1 on success, -1 on failure
*/
int render_stage (SDL_Renderer * renderer, struct stage * stage, SDL_Texture * player_tex){

    update_camera(stage);

    //Wipe the previous screen
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    render_tiles(renderer, stage);
    render_entity(renderer, player_tex, stage->player);

    //Present updated render
    SDL_RenderPresent(renderer);

    //add a slight delay between frames
    SDL_Delay(50);

    return 1;
}

int update_camera (struct stage * stage){
    stage->camera.x = MIN(MAX(stage->camera.x, 0), (STAGE_WIDTH * TILE_SIZE) - WINDOW_WIDTH);
	stage->camera.y = MIN(MAX(stage->camera.y, 0), (STAGE_HEIGHT * TILE_SIZE) - WINDOW_HEIGHT);

    return 1;
}

int render_tiles(SDL_Renderer * renderer, struct stage * stage){
    update_camera(stage);


    int x_start = (stage->camera.x % TILE_SIZE) * -1;
    int x_end = x_start + STAGE_RENDER_WIDTH * TILE_SIZE + (x_start == 0 ? 0 : TILE_SIZE);

    int y_start = (stage->camera.y % TILE_SIZE) * -1;
	int y_end = y_start + STAGE_RENDER_HEIGHT * TILE_SIZE + (y_start == 0 ? 0 : TILE_SIZE);

    int map_x = stage->camera.x / TILE_SIZE;
    int map_y = stage->camera.y / TILE_SIZE;

    int x,y;
    for(y = y_start; y < y_end; y += TILE_SIZE){
        for(x = x_start; x < x_end; x += TILE_SIZE){

            if(map_x >= 0 && map_x < STAGE_WIDTH && map_y >= 0 && map_y < STAGE_HEIGHT){

                int n = stage->data[map_x][map_y] * 35;

                //printf("%d\t", n);

                if(n > 0){
                    int color[3];
                    color[0] = 0; color[1] = 0; color[2] = 0;
                    color[n%3] = n;

                    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);

                    SDL_Rect dstrect = {x, y, TILE_SIZE, TILE_SIZE};
                    SDL_RenderFillRect(renderer, &dstrect);

                }


            }

            map_x++;


        }

        //printf("\n");
        map_x = stage->camera.x / TILE_SIZE;
        map_y++;

    }

    //printf("\n\n");

    return 1;
}


/*
Frees the stage struct
Returns a NULL pointer
*/
struct stage * free_stage(struct stage * stage){
    free_entity(stage->player);
    free(stage);

    return NULL;

}
