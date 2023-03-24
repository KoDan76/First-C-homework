#ifndef USERHANDLER_H_INCLUDED
#define USERHANDLER_H_INCLUDED

#include <stdbool.h>

typedef struct User {
    char* name;
    int money;
    int last_money;
    int result;
    int last_result;
    struct User *next;
} User;

User *All_Users(void);

void Free_User(User *first);

char *Din_Copy(char *copy);

User *Load_User(User **first);

void Put_User(User *first);

bool Compare_By(User *moving1, User* moving2, char user_command);

void List_Sort(User *first, char user_command);


#endif
