#include "funcionarios.h"


TFunc *sequentialFetch(int id, FILE *arq, int *totalComparisons){

int position = 0;

while(!feof(arq)){

    fseek(arq, position* sizeof(TFunc), SEEK_SET);
    TFunc *func = le_funcionario(arq);

    position ++;

    if (func == NULL){

        *totalComparisons +=1;
        return NULL;

    }
    else if (id == func->cod){
        *totalComparisons += 1;
        return func;
    }
    else{
        totalComparisons += 1;
    }
}

    return NULL;
}
