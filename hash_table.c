#include "funcionarios.h"

void hashTable(FILE *file, int numberOfPartition, int sizeFile) {

    rewind(file);

    char partitionName[100];
    char str1[100];
    char str2[100] = ".dat";

    for (int i = 0; i < sizeFile; ++i) {

        TFunc *auxFunc = readRegisterEmployee(file);

        int selectedParticipation = auxFunc->cod % numberOfPartition;

        itoa(selectedParticipation, str1, 10);
        strcat(strcpy(partitionName, "hashTablePartition"), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        FILE *filePartition = fopen(partitionName,"ab+");

        saveRegisterEmployee(auxFunc, filePartition);

        fclose(filePartition);

    }

    for (int i = 0; i < numberOfPartition; ++i) {

        itoa(i, str1, 10);
        strcat(strcpy(partitionName, "hashTablePartition"), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        FILE *filePartition = fopen(partitionName,"rb+");

        printPartitionEmployeeID(filePartition, partitionName);

        fclose(filePartition);
    }
}

