#include "funcionarios.h"

void deleteHashTable(int employerID, int partitionID) {

    char partitionName[100];
    char str1[100];
    char str2[100] = ".dat";
    int totalCompararisons = 0;

    itoa(partitionID, str1, 10);
    strcat(strcpy(partitionName, "hashTablePartition"), str1);
    strcat(strcpy(partitionName, partitionName), str2);

    FILE *filePartition = fopen(partitionName,"r+b");

    TFunc *auxFunc = sequentialFetch(employerID, filePartition, &totalCompararisons);

    if (auxFunc != NULL) {

        fseek(filePartition, (totalCompararisons - 1) * sizeof(TFunc), SEEK_SET);

        TFunc funcHashDelet;

        funcHashDelet.cod = 999999999;
        sprintf(funcHashDelet.nome, "%s", auxFunc->nome);
        sprintf(funcHashDelet.cpf, "%s", auxFunc->cpf);
        sprintf(funcHashDelet.data_nascimento, "%s", auxFunc->data_nascimento);
        funcHashDelet.salario = auxFunc->salario;

        salva_funcionario(&funcHashDelet, filePartition);

        printf("\nEmployee deleted successfully.");
    } else {
        printf("\nEmployee id not exist in the Hash Table.");
    }

    fclose(filePartition);
}
