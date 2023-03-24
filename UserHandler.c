#include "FileHandler.h"
#include "UserHandler.h"
#include "debugmalloc.h"

User *All_Users(void){
    FILE* fp;
    fp = fopen("users.txt","r");
    User *first = NULL;
    User *U_list = NULL;

    if (feof(fp)){
        fclose(fp);
        return NULL;
    }
    char tmp[121];
    char junk;

    fscanf(fp,"%c",&junk);
    while (!feof(fp)){
        U_list = (User*) malloc(sizeof(User));
        U_list->name = GetString(fp);
        fgets(tmp,120,fp);
        sscanf(tmp,"%d;%d;%d;%d\n", &U_list->money, &U_list->last_money, &U_list->result, &U_list->last_result);
        fscanf(fp,"%c",&junk);
        U_list->next = first;
        first = U_list;
    }
    return first;
    fclose(fp);
}

void Free_User(User *first){
    while (first != NULL) {
        User *next_one;
        next_one = first->next;
        free(first->name);
        free(first);
        first = next_one;
    }
}

char *Din_Copy(char *copy){
    int size = 0;
    while (copy[size] != '\0'){
        size++;
    }

    char *out = malloc((size+1) * sizeof(char));
    for (int i = 0; i < size; ++i){
        out[i] = copy[i];
    }
    out[size] = 0;
    return out;
}

User *Load_User(User **first){
    printf("Adjon meg egy mar meglevo, vagy uj felhasznalonevet! (max 30 karakter) \n");
    char to_find[31];
    gets(to_find);

    User *moving;
    for (moving = *first; moving != NULL; moving = moving->next){
        if (strcmp(moving->name,to_find) == 0){
            printf("\n %s felhasznalo betoltese . . .", moving->name);
            moving->last_result = 0;
            moving->last_money = 0;
            return moving;
        }
    }
    printf("\n uj felhasznalo betoltese . . .\n\n");
    User *new_one;
    new_one = (User*) malloc(sizeof(User));
    new_one->name = Din_Copy(to_find);
    new_one->money = 0;
    new_one->last_money = 0;
    new_one->result = 0;
    new_one->last_result = 0;
    new_one->next = *first;
    *first = new_one;
    return *first;
}

void Put_User(User *first){
    FILE* fp;
    fp = fopen("users.txt","w");
    User *moving;

    for(moving = first; moving != NULL; moving = moving->next){
        fprintf(fp," %s;%d;%d;%d;%d\n",
                moving->name,
                moving->money,
                moving->last_money,
                moving->result,
                moving->last_result);
    }
    fclose(fp);
}

bool Compare_By(User *first, User* second, char user_command){
    switch(user_command){
        case '1':
            return strcmp(first->name,second->name) > 0;
        case '2':
            return strcmp(first->name,second->name) < 0;
        case '3':
            return second->money > first->money;
        case '4':
            return second->last_money > first->last_money;
        case '5':
            return second->result > first->result;
        case '6':
            return second->last_result > first->last_result;
    }
    return false;
}
 // source tag: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
void swap_data(User *first, User *second){

    char *tmp_name      = first->name;
    int tmp_last_result = first->last_result;
    int tmp_result      = first->result;
    int tmp_last_money  = first->last_money;
    int tmp_money       = first->money;

    first->name         = second->name;
    first->last_result  = second->last_result;
    first->last_money   = second->last_money;
    first->money        = second->money;
    first->result       = second->result;

    second->name        = tmp_name;
    second->last_result = tmp_last_result;
    second->last_money  = tmp_last_money;
    second->result      = tmp_result;
    second->money       = tmp_money;
}

void List_Sort(User *first, char user_command){
    bool swapped;
    User *moving;
    User *last = NULL;

    if (first == NULL)
        return;

    do
    {
        swapped = 0;
        moving = first;
        while (moving->next != last) {
            if (Compare_By(moving,moving->next,user_command)) {
                swap_data(moving, moving->next);
                swapped = true;
            }
            moving = moving->next;
        }
        last = moving;
    }
    while (swapped);
}
// source tag;
