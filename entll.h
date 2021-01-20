#ifndef ENTLL_H_
#define ENTLL_H_

#include "entity.h"

struct entll {
    struct entity ent;
    struct entll * next;
};

struct entll * init_entll();
struct entll * destroy_entll(struct entll * to_free);

#endif