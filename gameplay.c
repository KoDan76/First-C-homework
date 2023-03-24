#include "gameplay.h"
#include "debugmalloc.h"

void voting (Question *Curr_Q){
    int sc_threshold = 2;
    if (Curr_Q->difficulty > 10){
        sc_threshold = 15;
    }
    const int margin_of_error = 22;
    const int size_of_crowd = 100;

    int special_case = rand()%size_of_crowd;

    int votes['D'-'A'+1] = {0};
    int remaining;

    if (special_case > sc_threshold) {
        remaining = rand()%margin_of_error;
        votes[Curr_Q->correct - 'A'] = size_of_crowd - remaining;

        for (char i = 'A'; i <= 'D'; ++i){
            if(Curr_Q->correct != i){
                votes[i-'A'] = rand()%remaining;
                remaining = remaining - votes[i-'A'];
            }
        }
    } else {
        remaining = rand()%margin_of_error + size_of_crowd / 3;
        votes[Curr_Q->correct - 'A'] = size_of_crowd - remaining;

        for (char i = 'A'; i <= 'D'; ++i){
            if(Curr_Q->correct != i){
                votes[i-'A'] = rand()%remaining;
                remaining = remaining - votes[i-'A'];
            }
        }
    }

    printf("A szavazas eredmenye a kovetkezo: \n");
    for(int i='A'; i <= 'D'; i++){
        printf("%c lehetosegre %d db nezo szavazott.\n", i, votes[i-'A']);
    }
    printf("%d nezo semelyikre sem szavazott.", remaining);
    printf("Valyon kik valasztottak helyesen?");
}

void ex_machina(Question *Curr_Q){
    printf("Hivas...\n");
    printf("A helyes válasz minden bizonnyal a %c \n", Curr_Q->correct);
}

void halving(Question *Curr_Q){
    char other_one = rand()%4+'A';
    while (other_one == Curr_Q->correct){
        other_one = rand()%4+'A';
    }

    if (other_one > Curr_Q->correct){
        printf("Megmaradt valaszlehetosegek: \n  %c  %c", Curr_Q->correct, other_one);
    } else {
        printf("Megmaradt valaszlehetosegek: \n  %c  %c", other_one, Curr_Q->correct);
    }
    printf("\nVajon melyik lehet a helyes?\n");
}

bool check(Question *Curr_Q, char answ){
    if (answ == Curr_Q->correct){
        printf("\nHelyes valasz! Gratulalunk!\n");
        return false;
    };
    printf("Rossz valasz. %c volt a helyes :(", Curr_Q->correct);
    return true;
}
