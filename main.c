
#include <stdlib.h>

#include "ordenacao_busca.h"
#include "lista.h"
#include "particoes.h"
#include "intercalacao.h"
#include "arvore_binaria.h"

int menu(){
    int op;

    printf("\n\n**************MENU************** \n\nBASE DE DADOS\n");

    printf("\nDigite 1 para utilizar a base de dados funcionario de teste.");
    printf("\nDigite 2 se desejar imprimir a base de dados funcionario.");
    printf("\nDigite 3 se desejar imprimir o índice primário da base de funcionarios.");

/*
    printf("\n\nINTERPOLAÇÃO\n");
    printf("\nDigite 4 para utilizar a estrutura de interpolação teste.");
    printf("\nDigite 5, 6  para gerar particões ordenadas utilizando, respectivamente, os métodos: classificação interna ou seleção natural.");
    printf("\nDigite 7 para criar uma pilha com o conteúdo das partições geradas.");
    printf("\nDigite 8, 9 para gerar intercalar as partições ordenadas utilizando, respectivamente, os métodos: intercalação basico, intercalacao arvore de vencedores.");
*/
    printf("\n\nINSERTION SORT E ÁRVORE BINÁRIA, ARVORE B\n");
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


    int op = menu();
    int nFunc, codF;

    int nParticoes, nElementos;
    Lista  * nomes = NULL;

    TPilha **vetPilhas;
    int crioubase = 0, crioulistadenomes = 0, criouparticoes = 0, crioupilhas = 0;

    //ponteiro para salvar o início da lista de nomes
    Lista *prox;
    int *vetTopo;

    while(op!=-1){
        switch (op){
            case (1):
                //criando a base de dados de funcionários teste e o arquivo de índice primário
                nFunc = 5;
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
            case (4):
                nParticoes = 10;
                nElementos = 2;
                printf("\n\nA estrutura de interpolação será composta por 10 arquivos de no máximo 2 elementos.\n");
                nomes = cria("p1.dat", cria("p2.dat", cria("p3.dat", cria("p4.dat", cria("p5.dat",  cria("p6.dat",  cria("p7.dat",  cria("p8.dat",  cria("p9.dat",  cria("p10.dat", NULL))))))))));
                crioulistadenomes = 1;
                imprime(nomes);
                break;
            case (5):
                if(crioulistadenomes){
                    //cria as particões que contém a base de dados de funcionários usando o método classificação interna
                    printf("\n\nGerando partições, utilizando o método de classificação interna.\n");
                    classificacao_interna(arq, nomes, nElementos, nFunc);
                    //salvando o ponteiro para o início da lista de nomes
                    prox = nomes;
                    criouparticoes=1;
                }else printf("Lista de nomes de arquivos inexistente para gerar partições, crie a estrutura de interpolação utilizando a opção 4 do menu!!!\n");
                break;
            case (6):
                if(crioulistadenomes){
                    printf("\n\nGerando partições, utilizando o método selecao natural.\n");
                    selecao_natural(arq, nomes, nElementos, nFunc,1);

                    //salvando o ponteiro para o início da lista de nomes
                    prox = nomes;
                    criouparticoes=1;
                }else printf("Lista de nomes de arquivos inexistente para gerar partições, crie a estrutura de interpolação utilizando a opção  4 do menu!!!\n");
                break;
           case (7):
                if(criouparticoes){
                    //criando pilha com o conteúdo das partições geradas
                    vetPilhas = (TPilha **) malloc(sizeof(TPilha *) * (nParticoes));
                    vetTopo = (int *) malloc(sizeof(int) * (nParticoes));
                    for(int p = 0 ; p < nParticoes ; p++){
                        //alocando a memória para salvar uma pilha para cada particao
                        vetPilhas[p] = (TPilha *) malloc(sizeof(TPilha) * (nElementos));
                        //abrindo primeira partição para leitura
                        FILE *part = fopen(nomes->nome, "rb+");
                        printf("Partição %s \n", nomes->nome);
                        nomes = nomes->prox;
                        //imprimindo os funcionários gravados nas partições
                        imprime_base_dados_funcionarios(part, nElementos);
                        //inicializando os topos das pilhas
                        vetTopo[p] = -1;
                        //criando pilha através da leitura da partição
                        cria_pilha_particao(vetPilhas[p], part, nElementos, &vetTopo[p]);
                        //fechando a partição
                        fclose(part);
                    }
                    crioupilhas = 1;
                    nomes = prox;
                }else printf("Partições não foram criadas, crie as partições utilizando as opções 5 ou 6  do menu!!!\n");
                break;
            case (8):
                if(criouparticoes){
                    printf("\n\nIntercalando as partições, utilizando o método de intercalação basico.\n");
                    intercalacao_basico("arquivo_intercalado.dat", nParticoes, nomes);
                    //imprimindo o arquivo intercalado
                    FILE *fi = fopen("arquivo_intercalado.dat","rb+");
                    imprime_base_dados_funcionarios(fi,nFunc);
                    fclose(fi);
                }else printf("Partições não foram criadas, crie as partições utilizando as opções 5 ou 6 do menu!!!\n");
                break;
            case (9):
                printf("Método a ser implementado na parte I do trabalho.\n");
                if(criouparticoes){
                    if(crioupilhas){
                        intercalacao_arvore_de_vencedores(vetPilhas, vetTopo, "arquivo_intercalado.dat", nParticoes);
                    }else printf("As pilhas das partições geradas não foram criadas, crie as pilhas utilizando as opções 7!!!\n");
                }else printf("Partições não foram criadas, crie as partições utilizando as opções 5 ou 6  do menu!!!\n");


                //imprimindo o arquivo intercalado
                FILE *fi = fopen("arquivo_intercalado.dat","rb+");
                imprime_base_dados_funcionarios(fi,nFunc);
                fclose(fi);
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

                //ordenando a base de dados utilizando ordenação direta no arquivo com o método inseriton sort
                /*if(crioubase==1){
                    insertion_sort_disco(arq, nFunc);
                    imprime_base_dados_funcionarios(arq, nFunc);
                    //procurando por um funcionário na base de dados usando o método de busca binária
                    int busca_codigo;
                    printf("\n\nInforme o codigo do funcionário procurado (digite -1 caso não queira procurar um funcionário): ");
                    scanf("%d", &busca_codigo);
                    if(busca_codigo!= -1){
                        TFunc* func = busca_binaria(busca_codigo, arq, nFunc);
                        imprime_funcionario(func);
                        free(func);
                    }
                }else printf("Base de dados inexistente para ser ordenada, crie utilizando a opção 1 do menu!!!\n");*/
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
                int numberOfPartition;
                char *partitionName[100];
                char str1[100];
                char str2[100] = ".dat";

                printf("\nDigite o numero de partições da Hash Table (Hash Function): ");
                scanf("%i", &numberOfPartition);

                makePartitionHashTable(numberOfPartition);
                hashTable(arq, numberOfPartition, nFunc);

                printf("Hash Table criada com sucesso");

                int flagAux = 0;

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
                            printEmployee(funcSearchHashTable);
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

                fclose(file);

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

    for(int p = 0; p <nParticoes; p++){
        free(vetPilhas[p]);
	}
	free(vetPilhas);

    fclose(arqIndicePrimario);
    fclose(arqIndicePrimarioNaoOrdenado);
    fclose(arqArvoreBinariaExterna);
    fclose(arq);

    return 0;
}
