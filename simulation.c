//goal is to no use any sdl stuff here
#include "input.h"
#include "simulator.h"

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

int main() {
    int fd[2];
    if(establish_processer_connection(fd, WELL_KNOWN_PIPE != 0)) {
        fprintf("Error connecting to input reader!\n");

        //should be fine just to return here
        return 1;
    }

    //initilzing shared memory stuff
    int shmd = shmget(KEY, 0, 0);
    if(shmd == -1) {
        fprintf(stderr, "Error creating shared memory: %s\n", strerror(errno));

        close_fd(fd);
        SDL_DestroyWindow(window), window = NULL;
        SDL_DestroyRenderer(renderer);

        return 1;
    }
    struct entity * ents = shmat(shmd, 0, 0);

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
            struct entll * cur_ent = unloaded;
            while(cur_ent) {
                //process cur_ent
                update_ent(cur_ent, loaded, unloaded, gamestate, keycode);

                cur_ent=cur_ent->next;
            }
            cur_ent = loaded;
            while(cur_ent) {
                //process cur_ent
                update_ent(cur_ent, loaded, unloaded, gamestate, keycode);

                cur_ent = cur_ent->next;
            }

            //set keycode to next keycode
            keycode = ctoi(++input_pointer);
        }

        //shared memory list stuff
        int i;
        struct entll * out_ent = loaded;
        for(i = 0; i < MAX_ENTS && out_ent; i++) {
            cp_entity(&ents[i], out_ent->ent);
            out_ent = out_ent->next;
        }
        ents[MIN(i,MAX_ENTS)] = NULL;

    }

    //program has terminated, just need to clean up
    shmdt(ents);

    close(fd[0]), fd[0] = NULL;
    close(fd[1]), fd[1] = NULL;

    destroy_entll_children(unloaded);
    destroy_entll_children(loaded);

    return 0;
}
