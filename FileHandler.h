#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "QuestionHandler.h"

bool Resize(char  **string, int size);

char *GetString(FILE *fp);

Question *GetFile(void);

#endif
