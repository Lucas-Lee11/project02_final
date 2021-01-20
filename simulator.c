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

    char running = 1;
    int gamestate = 0;
    char in_buff[MAX_KEYS_AT_ONCE];

    while(running) {
        //readed keycodes from 
        //ASSUMES ONLY ONE SEQUENCE OF KEYS IS READ AT ONCE 
        read(fd[1], in_buff, sizeof(in_buff));

        char * input_pointer = in_buff;
        int keycode = ctoi(*input_pointer);
        while(keycode != END) {
            //do processing stuff
            if(keycode == TERMINATE) {
                //terminates the loop as the program should now end
                running = 0;
                break;
            }

            //TODO set up processor function
            //update first unloaded and than loaded nodes
            struct entll * curr_ent = unloaded;
            while(curr_ent) {
                //process cur_ent

                cur_ent=cur_ent->next;
            }
            cur_ent = loaded;
            while(cur_ent) {
                //process cur_ent

                cur_ent = cur_ent->next;
            }

            //set keycode to next keycode
            keycode = ctoi(++input_pointer);
        }

        //TODO update shared memory list

    }

    //program has terminated, just need to clean up
    close(fd[0]), fd[0] = NULL;
    close(fd[1]), fd[1] = NULL;

    destroy_entll_children(unloaded);
    destroy_entll_children(loaded);

    return 0;
}
