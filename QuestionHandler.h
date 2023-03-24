#ifndef QUESTIONHANDLER_H_INCLUDED
#define QUESTIONHANDLER_H_INCLUDED

typedef struct Question{
    int difficulty;
    char *qst;
    char *answ_A;
    char *answ_B;
    char *answ_C;
    char *answ_D;
    char correct;
    char *category;
    struct Question *next;
} Question;

Question *next_question(Question *first, int diff,  Question  **invalid, Question *inv_out);

void ask_question(int round, Question  *Q_pt, int *price_pool);

void Free_Them_All(Question *first);


#endif
