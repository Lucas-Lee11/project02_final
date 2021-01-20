#include <SDL2/SDL.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "stage.h"

/*
Copies over new fd to original fd
Returns a backup of the original fd
*/
int redirect_file_descriptor(int orignial_fd, int new_fd) {
    int backup_fd = dup(orignial_fd);
    dup2 (new_fd, orignial_fd);
    return backup_fd;
}


/*
Creates a new stage struct
Returns a pointer to the new struct
*/
struct stage * init_stage(char * filename){

    struct stage * stage = malloc(sizeof(struct stage));

    load_tiles(stage, filename);

    return stage;

}


/*
Reads from a file to get level data
Returns 1 on success, -1 on failure
*/
int load_tiles(struct stage * stage, char * filename){

    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        printf("Error: %d  %s\n",errno, strerror(errno));
        return -1;
    }

    int dup_stdin = redirect_file_descriptor(STDIN_FILENO, fd);

    int x,y;
    char d[1];

    printf("Reading data\n");

    for(y = 0; y < STAGE_HEIGHT; y++){
        for(x = 0; x < STAGE_WIDTH; x++){
            scanf("%d", &(stage->data[x][y]));
            //printf("%d ", stage->data[x][y]);
        }
        scanf("%c", d);
        //printf("%c", *d);

    }

    dup2(STDIN_FILENO, dup_stdin);
    close(fd);

    return 1;
}

/*
Renders the stage
Returns 1 on success, -1 on failure
*/

int render_stage (SDL_Renderer * renderer, struct stage * stage){

    int x,y;

    for(y = 0; y < STAGE_HEIGHT; y++){
        for(x = 0; x < STAGE_WIDTH; x++){
            int n = stage->data[x][y] * 35;

            if(n > 0){
                int color[3];
                color[0] = 0; color[1] = 0; color[2] = 0;
                color[n%3] = n;

                SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);

                int nx = TILE_SIZE * x;
                int ny = TILE_SIZE * y;

                SDL_Rect dstrect = {nx, ny, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &dstrect);

            }
        }

    }

    return 1;

}


/*
Frees the stage struct
Returns a NULL pointer
*/
struct stage * free_stage(struct stage * stage){
    free(stage);

    return NULL;

}
