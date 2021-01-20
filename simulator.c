//goal is to no use any sdl stuff here
#include "input.h"

int main() {
    int fd[2];
    if(establish_processer_connection(fd, WELL_KNOWN_PIPE != 0)) {
        fprintf("Error connecting to input reader!\n");

        //should be fine just to return here
        return 1;
    }

    struct entity unloaded = init_entll();
    struct entity loaded = init_entll();

    //brain is on the fizzle. this is where we will finish taking input and setting up shared memeory which the renderer can read from and render the entities in there.


    return 0;
}
