#ifndef SIMULATOR_H_
#define SIMULATOR_H_

//maximum number of entities which can be on screen at once
//the plus 1 is there as the first entity will always be a camera entity which gives the reference point for rendering the other entities
enum{MAX_ENTS=128+1}

//Key for shmget, probably shoud make a better key but I don't really understand how to use ftok for this
enum{KEY=234980}

#endif
