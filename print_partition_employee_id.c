#include "funcionarios.h"

void printPartitionEmployeeID(FILE *file, char partitionName[]) {

    printf("\nIDs employee of partition %s: \n --->  ", partitionName);

    for (int i = 0; i < sizeFile(file, 0); ++i) {

        fseek(file, i * sizeof(TFunc), SEEK_SET) ;
        TFunc *aux = le_funcionario(file);

        printf(" %i ", aux->cod);
    }

    printf("\n");
}
