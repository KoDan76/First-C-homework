#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

#include "FileHandler.h"
#include "UserHandler.h"

typedef struct Bools{
    bool quit, used_vote, used_phone, used_halving, won;
} Bools;

void voting (Question  *Curr_Q);

void ex_machina(Question  *Curr_Q);

void halving(Question  *Curr_Q);

bool check(Question  *Curr_Q, char answ);

#endif
