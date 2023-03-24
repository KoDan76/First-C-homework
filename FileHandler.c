#include "FileHandler.h"
#include "debugmalloc.h"

bool Resize(char **string, int size){
    char *tmpStr =(char*) malloc(size+1 * sizeof(char));
    if (tmpStr != NULL){
        for (int i=0; i<= size; ++i){
            tmpStr[i] = (*string)[i];

        }
        free(*string);
        *string = tmpStr;
        return true;
    }
    return false;
}

char *GetString(FILE *fp){
    char *out;
    out =(char*) malloc(sizeof(char));

    int size = 0;
    fscanf(fp,"%c",&out[size]);

    while (out[size] != ';' && out[size] != '\n' && out[size] != EOF){
        size++;
        if (Resize(&out, size+1)){
            fscanf(fp,"%c", &out[size]);
        }
        else {
            return NULL;
        }

    }
    out[size] = '\0';
    return out;
}

Question *GetFile(void){
    FILE* fp;
    fp = fopen("loim.csv","r");
    char junk[50];
    fgets(junk,50,fp);

    Question *first = NULL;
    Question *Q_list = NULL;

    do{
        Q_list =(Question*) malloc(sizeof(Question));
        fscanf(fp,"%d",&Q_list->difficulty);
        fscanf(fp,"%c",&junk[1]);
        Q_list->qst = GetString(fp);
        Q_list->answ_A = GetString(fp);
        Q_list->answ_B = GetString(fp);
        Q_list->answ_C = GetString(fp);
        Q_list->answ_D = GetString(fp);
        fscanf(fp,"%c",&Q_list->correct);
        fscanf(fp,"%c",&junk[1]);
        Q_list->category = GetString(fp);
        Q_list->next = first;
        first = Q_list;
    } while (first->correct != 'E');
    fclose(fp);
    return first;
}

