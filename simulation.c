//goal is to no use any sdl stuff here
#include "input.h"
#include "simulator.h"
#include "entll.h"
#include "entity.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <unistd.h>

#include <errno.h>
#include <string.h>

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

int main() {
    int fd[2];
    if(establish_processer_connection(fd, WELL_KNOWN_PIPE) != 0) {
        fprintf(stderr, "Error connecting to input reader!\n");

        //should be fine just to return here
        return 1;
    }

    //initilzing shared memory stuff
    int shmd = shmget(KEY, 0, 0);

    printf("shmd: %d\n", shmd);

    if(shmd == -1) {
        fprintf(stderr, "Error creating shared memory: %s\n", strerror(errno));

        close(fd[0]), close(fd[1]);
        fd[0] = fd[1] = 0;

        return 1;
    }
    struct entity * ents = shmat(shmd, 0, 0);

    struct entll * unloaded = init_entll();
    struct entll * loaded = init_entll();

    //brain is on the fizzle. this is where we will finish taking input and setting up shared memeory which the renderer can read from and render the entities in there.

    char running = 1;
    int gamestate = 0;

    while(running) {
        //readed keycodes from 
        //ASSUMES ONLY ONE SEQUENCE OF KEYS IS READ AT ONCE 

        int keycode;

        read(fd[1], &keycode, sizeof(int));
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
                //update_ent(cur_ent, loaded, unloaded, gamestate, keycode);

                cur_ent = cur_ent->next;
            }

            read(fd[1], &keycode, sizeof(int));
        }

        //shared memory list stuff
        int i;
        struct entll * out_ent = loaded;
        for(i = 0; i < MAX_ENTS && out_ent; i++) {
            cp_entity(&ents[i], &(out_ent->ent));
            out_ent = out_ent->next;
        }

        struct entity * null_ent = init_entity(0,0);
        cp_entity(&ents[MIN(i,MAX_ENTS)], null_ent);
    }

    //program has terminated, just need to clean up
    shmdt(ents);

    close(fd[0]),close(fd[1]);

    destroy_entll_children(unloaded);
    destroy_entll_children(loaded);

    return 0;
}
