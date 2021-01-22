//goal is to no use any sdl stuff here
#include "input.h"
#include "entll.h"
#include "entity.h"

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
