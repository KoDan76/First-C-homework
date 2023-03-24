#ifndef MENUHANDLER_H_INCLUDED
#define MENUHANDLER_H_INCLUDED

#include "QuestionHandler.h"
#include "gameplay.h"

void help(void);

char Menu_Exception(char user_command);

char Exception(char user_command);

void Command_Menu(char user_command, Question *Q_pt, Bools *Game_State);

void New_Game(Question  *first, User *player);

void Ranklist(User *first);

void Main_Menu(void);

#endif
