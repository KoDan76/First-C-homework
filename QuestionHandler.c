#include "QuestionHandler.h"
#include "debugmalloc.h"
#include <stdlib.h>
#include <stdio.h>

Question *next_question(Question *first, int diff, Question **invalid, Question *inv_out){
    Question *guard;
    int ossz = 0;
    for (guard = first; guard->next != NULL; guard = guard->next){
        if (guard->difficulty == diff){
            ossz++;
        }
    }
    int choise = rand()%ossz;

    for (guard = first; guard != NULL; guard = guard->next){
        if (guard->difficulty == diff)
            choise--;
        if (choise == 0)
            return guard;
    }
    return NULL;
}

void ask_question(int round, Question *Q_pt, int *price_pool){
    printf("\n%d. kerdes %d Ft-ert: \n"
           "%s\n"
           "Lehetseges valaszok: \n"
           "A: %s\n"
           "B: %s\n"
           "C: %s\n"
           "D: %s\n"
           "\nMi a valasza?",
           round, price_pool[round-1], Q_pt->qst, Q_pt->answ_A, Q_pt->answ_B, Q_pt->answ_C, Q_pt->answ_D);
}

void Free_Them_All(Question *first){
    Question *iter;
    iter = first;
    while (iter != NULL) {
        Question *next_one;
        next_one = iter->next;
        free(iter->answ_A);
        free(iter->answ_B);
        free(iter->answ_C);
        free(iter->answ_D);
        free(iter->qst);
        free(iter->category);
        free(iter);
        iter = next_one;
    }
}

