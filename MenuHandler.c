
#include "debugmalloc.h"
#include "MenuHandler.h"

void help(void){
    printf("Parancsok a jatekban: \n"
           "A - megjeloli az A lehetoseget \n"
           "B - megjeloli a B lehetoseget \n"
           "C - megjeloli a C lehetoseget \n"
           "D - megjeloli a D lehetoseget \n"
           "h - parancsok a jatekban és a menuben.\n"
           "k - megkerdezi a kozonseg velemenyet a jelnlegi kerdesekrol\n"
           "f - a helytelen valaszokbol kettot elvesz\n"
           "t - telefonos segitseget ker Szoro Olszal neves polihisztortol\n"
           "q - visszateres a fomenube\n\n"
           "Parancsok a menuben: \n"
           "R - Ranglista megnyitása\n"
           "N - Uj játék inditasa\n"
           "K - Kilepes az operácios rendszerbe\n\n"
           "Parancsok a Ranglistaban:\n"
           "1 - nev szerint A-Z\n"
           "2 - nev szerint Z-A\n"
           "3 - osszes nyeremeny szerint\n"
           "4 - utolso nyeremeny szerint\n"
           "5 - osszes megvalaszolt kerdesek szerint\n"
           "6 - legutobb megvalaszolt kerdesek szerint\n"
           );
}

char Menu_Exception(char user_command){
    while (user_command != 'h' && user_command != 'k' && user_command != 'n' && user_command != 'r'){
        printf("Helytelen parancs, adjon meg ujat!\n");
        scanf("%c%*[^\n]%*c", &user_command);
        getchar();
    }
    return tolower(user_command);
}

char Exception(char user_command){
    while (user_command != 'a' && user_command != 'b' && user_command != 'c' && user_command != 'd' && user_command != 'h' && user_command != 'k' && user_command != 'f' && user_command != 't' && user_command != 'q'){
        printf("Helytelen parancs, adjon meg ujat!\n");
        scanf("%c%*[^\n]%*c", &user_command);
        getchar();
    }
    return user_command;
}

void Command_Menu(char user_command, Question *Q_pt, Bools *Game_State ){
    bool infiniteLoop = true;
    while (infiniteLoop){
        switch (user_command){
            case 'a':
                Game_State->quit = check(Q_pt,toupper(user_command));
                return;
            case 'b':
                Game_State->quit = check(Q_pt,toupper(user_command));
                return;
            case 'c':
                Game_State->quit = check(Q_pt,toupper(user_command));
                return;
            case 'd':
                Game_State->quit = check(Q_pt,toupper(user_command));
                return;
            case 'f':
                if (Game_State->used_halving){
                    printf("Mar hasznalt felezest. uj parancs:\n");
                } else {
                    halving(Q_pt);
                    Game_State->used_halving = true;
                }
                break;
            case 'k':
                if (Game_State->used_vote){
                    printf("Mar hasznalt kozonseg szavazast. uj parancs:\n");
                } else {
                    voting(Q_pt);
                    Game_State->used_vote = true;
                }
                break;
            case 't':
                if (Game_State->used_phone){
                    printf("Mar hasznalt telefonos segítseget. uj parancs:\n");
                } else {
                    ex_machina(Q_pt);
                    Game_State->used_phone = true;
                }
                break;
            case 'h':
                help();
                printf("uj parancs: \n");
                break;
            case 'q':
                printf("biztos benne, hogy kilep a jatekbol? igen/nem (y/n) \n");
                scanf("%c%*[^\n]%*c", &user_command);
                getchar();
                if (user_command == 'y'){
                    Game_State->quit = true;
                    return;
                }
                break;
        }
        scanf("%c%*[^\n]%*c", &user_command);
        getchar();
        user_command = Exception(user_command);
    }
}

void New_Game(Question *first, User *player){

    int round = 1;
    int price_pool[15]={5000, 10000,25000,50000,100000,200000,300000,500000,800000,1500000,3000000,5000000,10000000,20000000,40000000};
    int price = 0;
    char user_command;
    Bools Game_State = {false,false,false,false};

    printf("Udvozlom a jatekban %s! En vagyok a Pistabacsi es ez itt aaa\n", player->name);
    printf("Legyen On is MILLIOMOS  ;) \n\n");

    Question *invalid[15];
    for (int j = 0; j < 15; ++j ){
        invalid[j] = NULL;
    }

    while(!(Game_State.quit)) {
        Question *Q_pt = next_question(first, round, invalid, invalid[round]);
        ask_question(round, Q_pt, price_pool);
        scanf("%c%*[^\n]%*c", &user_command);
        getchar();
        user_command = tolower(user_command);
        user_command = Exception(user_command);

        Command_Menu(user_command, Q_pt, &Game_State);

        if (!Game_State.quit && round == 15){
            Game_State.won = true;
            break;
        }
        round++;
    }
    if (Game_State.won){
        printf("\nON NYERT!\n");
    } else {
        round = round-2;
    }
    for (int i = 0; i < round/5; i++){
        price += price_pool[i];
    }

    printf("\nGratulálunk: %d kerdesre valaszolt helyesen es %d nyeremennyel tavozhat!\n", round, price);
    player -> last_money  = price;
    player -> last_result = round;
    player -> money  += price;
    player -> result += round;
    return;
}

void Ranklist(User *first){
    printf("\nRANGLISTA\n\n"
           "Mi alapjan szertne rendezni?\n"
           "1 - nev szerint A-Z\n"
           "2 - nev szerint Z-A\n"
           "3 - osszes nyeremeny szerint\n"
           "4 - utolso nyeremeny szerint\n"
           "5 - osszes megválaszolt kerdesek szerint\n"
           "6 - legutobb megvalaszolt kerdesek szerint\n\n");

    char user_command;
    scanf("%c%*[^\n]%*c", &user_command);
    getchar();

    List_Sort(first, user_command);

    User *moving;
    for (moving = first; moving != NULL; moving = moving->next){
        printf("\n%s:   ossznyeremeny: %d   legutobbi nyeremeny: %d  megvalaszolt kerdesek: %d   legutobbi kerdesek: %d\n"
               ,moving->name, moving->money, moving->last_money, moving->result, moving->last_result);

    }
}

void Main_Menu(void){
    printf("\nUdvozoljuk a jatekban! \n");

    char command;
    Question *qst_list;
    User *usr_list;
    command = tolower(command);

    while(command != 'k'){
        printf("\nFomenu:\n"
               "Valasszon az alabbi lehetosegek kozul: \n"
               "Uj jatek (N) \n"
               "(R)nglista \n"
               "(K)lepes \n"
               "Segitseg (h) \n" );

        scanf("%c%*[^\n]%*c", &command);
        getchar();
        command = Menu_Exception(command);

        switch (command){
            case 'r':
                usr_list = All_Users();
                Ranklist(usr_list);
                Free_User(usr_list);
                break;
            case 'k':
                return;
            case 'h':
                help();
                break;
            case 'n':
                qst_list = GetFile();
                usr_list = All_Users();
                New_Game(qst_list, Load_User(&usr_list));
                Free_Them_All(qst_list);
                Put_User(usr_list);
                Free_User(usr_list);
                break;
        }
    }
}

