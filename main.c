
#include <stdlib.h>

#include "ordenacao_busca.h"
#include "lista.h"
#include "particoes.h"
#include "arvore_binaria.h"
#include "arvore_binaria.h"
#include "arvore_binaria.h"
#include "arvore_binaria.h"
#include "make_partition_hash_table.c"

int menu(){
    int op;

    printf("\n\n**************MENU************** \n\nBASE DE DADOS\n");

    printf("\nDigite 1 para utilizar a base de dados funcionario de teste.");
    printf("\nDigite 2 se desejar imprimir a base de dados funcionario.");
    printf("\nDigite 3 se desejar imprimir o índice primário da base de funcionarios.");

    printf("\n\nÁRVORE BINÁRIA, ARVORE B\n");
    printf("\nDigite 10 para criar árvores binárias em memória interna e externa.");
    printf("\nDigite 11 para buscar um funcionario pela chave.");
    printf("\nDigite 12 para excluir um funcionario pela chave.");

    printf("\n\nTABELA HASH\n");
    printf("\nDigite 13 para criar árvores binárias em memória interna e externa.");

    printf("\nDigite -1 para sair: ");
    scanf("%d", &op);

    return op;

}

int main(){

    /*criando um arquivo lógico para abir para leitura e escrita o arquivo binário*/
    FILE* arq = fopen("base_funcionarios.dat", "wb+");
    if(arq == NULL) {
        printf("Arquivo base_funcionarios.dat não encontrado.\n");
        return 1;
    }

    /*criando um arquivo lógico para abir para leitura e escrita do arquivo de indice primario ordenado*/
    FILE* arqIndicePrimario = fopen("IndicePrimarioFunc.dat", "wb+");
    if(arqIndicePrimario == NULL) {
        printf("Arquivo IndicePrimarioFunc.dat não encontrado.\n");
        return 1;
    }

    /*criando um arquivo lógico para abir para leitura e escrita do arquivo de indice primario não ordenado*/
    FILE* arqIndicePrimarioNaoOrdenado = fopen("IndicePrimarioFuncNaoOrdenado.dat", "wb+");
    if(arqIndicePrimarioNaoOrdenado == NULL) {
        printf("Arquivo IndicePrimarioFuncNaoOrdenado.dat não encontrado.\n");
        return 1;
    }

    /*criando um arquivo lógico para abir para leitura e escrita da árvore binária externa*/
    FILE* arqArvoreBinariaExterna = fopen("ArvoreBinariaExternaFunc.dat", "wb+");
    if(arqArvoreBinariaExterna == NULL) {
        printf("Arquivo ArvoreBinariaExternaFunc.dat não encontrado.\n");
        return 1;
    }

    int crioubase =0;

    int op = menu();
    int nFunc, codF;

    int nParticoes, nElementos;
    Lista  * nomes = NULL;

    //ponteiro para salvar o início da lista de nomes
    Lista *prox;
    int *vetTopo;

    // variaveis da hash table
    int numberOfPartition = 0;
    char *partitionName[100];
    char str1[100];
    char str2[100] = ".dat";
    int flagAux = 0;

    while(op!=-1){
        switch (op){
            case (1):
                //criando a base de dados de funcionários teste e o arquivo de índice primário
                nFunc = 50; //
                cria_base_dados_funcionarios_teste(arq, arqIndicePrimario, arqIndicePrimarioNaoOrdenado, nFunc);
                crioubase = 1;
                break;
            case (2):
                //imprime a base de dados dos funcionários
                if(crioubase==1)
                    imprime_base_dados_funcionarios(arq, nFunc);
                else  printf("Base de dados inexistente para ser impressa, crie utilizando a opção 1 do menu!!!\n");
                break;
            case (3):
                //imprime o arquivo de índices primários
                if(crioubase==1){
                    printf("\nArquivo ordenado\n ch:rrn\n");
                    imprime_indice_primario_funcionarios(arqIndicePrimario,nFunc);
                    printf("\nArquivo não ordenado\n ch:rrn\n");
                    imprime_indice_primario_funcionarios(arqIndicePrimarioNaoOrdenado,nFunc);
                }else  printf("Indice primario inexistente para ser impresso, será criado após a definição da base de dados utilizando a opção 1 do menu!!!\n");
                break;

            case (10):
                //cria árvore binária em memória utilizando o arquivo de índice primário ordenado
                if(crioubase==1){
                    printf("\nArvore binária em memória pelo arquivo de  índice primário ordenado\n <nopai <noesq><nodireita> >\n");
                    cria_arvore_binaria_indice_primario(arqIndicePrimario,nFunc);
                    printf("\nArvore binária em memória pelo arquivo de índice primário não ordenado\n <nopai <noesq><nodireita> >\n");
                    cria_arvore_binaria_indice_primario(arqIndicePrimarioNaoOrdenado,nFunc);
                    printf("\nArvore binária externa pelo arquivo de base de dados do funcionário\n <nopai <noesq><nodireita> >\n");
                    criar_arvore_binaria_externa(arq,arqArvoreBinariaExterna);
                }else  printf("Arquivo de índice primario inexistente para a criação da arvore binaria, crie utilizando a opção 1 do menu!!!\n");
                break;
            case (11):
                printf("\n\nDeseja buscar no arquivo externo da árvore binária um Funcionario? Informe o codigo do Funcionario.");
                scanf("%d", &codF);
                busca_arvore_binaria_externa(codF, arqArvoreBinariaExterna);

                break;
            case (12):
                printf("\n\nDeseja excluir um Funcionario do arquivo externo da árvore binária? Informe o codigo do Funcionario.");
                scanf("%d", &codF);
                excluir_funcionario_arvore_binaria_externa(codF, arqArvoreBinariaExterna);

                /*printf("Método a ser implementado na parte II do trabalho.\n");
                if(crioubase==1){
                    ;//criar_arvore_B();
                }else printf("Base de dados inexistente para ser ordenada, crie utilizando a opção 1 do menu!!!\n");*/
                break;
            case (13):
                printf("\nDigite o numero de partições da Hash Table (Hash Function): ");
                scanf("%i", &numberOfPartition);

                makePartitionHashTable(numberOfPartition);
                hashTable(arq, numberOfPartition, nFunc);

                printf("Hash Table criada com sucesso");

                while (flagAux != 5) {

                    printf("\n\nInput an option: \n 1 - Inserir funcionario; \n 2 - Buscar funcionario; \n 3 - Deletar funcionario; \n 4 - Imprimir IDs dos funcionarios; \n 5 - Encerrar. \n ----> ");
                    scanf("%i", &flagAux);

                    if (flagAux == 1) {
                        int employeeID;
                        int partitionID;

                        printf("\nInsira o IDdo funcionario: ");
                        scanf("%i", &employeeID);

                        TFunc funcHashIsert;

                        if (employeeID < 0)
                        {
                            printf("\nErro: ID < 0");
                            break;
                        }

                        funcHashIsert.cod = employeeID;

                        char auxName[15];
                        for (int j = 0; j < 15; j++)
                        {
                            auxName[j] = 'a' + (char)(rand() % 26);
                        }

                        sprintf(funcHashIsert.nome, "%s", auxName);
                        sprintf(funcHashIsert.cpf, "111.111.111-11");
                        sprintf(funcHashIsert.data_nascimento, "01/08/2021");
                        funcHashIsert.salario = 1000 + rand() % 10000;

                        partitionID = employeeID % numberOfPartition;

                        insertHashTable(&funcHashIsert, employeeID, partitionID);


                    } else if (flagAux == 2) {

                        int employeeID;
                        int partitionID;

                        printf("\nInsira o id do funcionario: ");
                        scanf("%i", &employeeID);

                        partitionID = employeeID % numberOfPartition;

                        TFunc *funcSearchHashTable = searchHashTable(employeeID, partitionID);

                        if (funcSearchHashTable != NULL) {
                            imprime_funcionario(funcSearchHashTable);
                        } else {
                            printf("\nFuncionario não encontrado");
                        }

                    } else if (flagAux == 3) {

                        int employeeID;
                        int partitionID;

                        printf("\nInsira o id do funcionario: ");
                        scanf("%i", &employeeID);

                        partitionID = employeeID % numberOfPartition;

                        deleteHashTable(employeeID, partitionID);

                    } else if (flagAux == 4) {

                        for (int i = 0; i < numberOfPartition; ++i) {

                            itoa(i, str1, 10);
                            strcat(strcpy(partitionName, "hashTablePartition"), str1);
                            strcat(strcpy(partitionName, partitionName), str2);

                            FILE *filePartition = fopen(partitionName,"rb+");

                            printPartitionEmployeeID(filePartition, partitionName);

                            fclose(filePartition);
                        }

                    } else {
                        printf("Fechando...");
                    }
                }

                fclose(arq);

                break;
            default:
                printf("\nOpção inválida!");
        }
        op = menu();
    }

	while(nomes) {
		prox = nomes->prox;
		free(nomes);
		nomes = prox;
	}

    fclose(arqIndicePrimario);
    fclose(arqIndicePrimarioNaoOrdenado);
    fclose(arqArvoreBinariaExterna);
    fclose(arq);

    return 0;
}
