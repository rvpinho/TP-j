#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "funcionarios.h"

TFunc *funcionario(int cod, char *nome, char *cpf, char *data, double salario){
	TFunc *funcionario = (TFunc *) malloc(sizeof(TFunc));
	if (funcionario) memset(funcionario, 0, sizeof(TFunc));
	funcionario->cod = cod;
	strcpy(funcionario->nome, nome);
	strcpy(funcionario->cpf, cpf);
	strcpy(funcionario->data_nascimento, data);
	funcionario->salario = salario;
	return funcionario;
}

int tamanho_registro() {
  return sizeof(TFunc);
}

void imprime_funcionario(TFunc *funcionario){
	printf("%d, %s, %s, %s, %lf \n", funcionario->cod, funcionario->nome, funcionario->cpf, funcionario->data_nascimento, funcionario->salario);
}

void salva_funcionario(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func→nome ao invés de &func→nome, pois string já é ponteiro
    fwrite(func->nome, sizeof(char),sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char),sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char),sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
    fflush(out);
}

TFunc *le_funcionario(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    int result =fread(&func->cod, sizeof(int), 1, in);
   // printf("result %d func->cod %d \n" , result, func->cod);
    if (0 >= result) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);

    return func;

}

void cria_base_dados_funcionarios(FILE* arq, FILE* arqIndicePrimario, FILE* arqIndicePrimarioNaoOrdenado, int nFunc){

    int cod;
    char nome_funcionario[TAM_NOME];
    char cpf[15];
    char data_nascimento[11];
    double salario;
    int chaves[nFunc+1];

    for (int i = 0; i < nFunc; i++) {
        printf("\n\n Informe o codigo do funcionário (%d):\n", i);
        scanf("%d", &cod);
        printf("\n\n Informe o nome do funcionário (%d):\n", i);
        scanf("%s", nome_funcionario);
        printf("Informe o cpf do funcionário:\n");
        scanf("%s", cpf);
        printf("Informe a data de nascimento do funcionário:\n");
        scanf("%s", data_nascimento);
        printf("Informe o salário do funcionário:\n");
        scanf("%lf", &salario);
        TFunc *func = funcionario(cod,nome_funcionario,cpf,data_nascimento,salario) ;
        fseek(arq, (i) * tamanho_registro(), SEEK_SET);
        salva_funcionario(func, arq);
        chaves[func->cod-1] = i;
        fwrite(&func->cod,sizeof(int), 1, arqIndicePrimarioNaoOrdenado);  //escreve a chave
        fwrite(&i, sizeof(int), 1, arqIndicePrimarioNaoOrdenado); //escreve o rrn
  }
   for(int f = 1 ; f <=nFunc; f++){
        fwrite(&f, sizeof(int), 1, arqIndicePrimario);
        fwrite(&chaves[f], sizeof(int), 1, arqIndicePrimario);
    }
}
int numero_aleatorio_unico(int chaves[], int nFunc){
    int numero_aleatorio;
    while (1) {
        numero_aleatorio = rand() % 1000; // gera um número aleatório
        int found = 0;
        for (int i = 0; i < nFunc; i++) {
            if (chaves[i] == numero_aleatorio) {
                found = 1; // encontrou o número no vetor
                break;
            }
        }
        if (!found) {
            return numero_aleatorio; // retorna o número se não estiver no vetor
        }
    }
}
void cria_base_dados_funcionarios_teste(FILE* arq, FILE* arqIndicePrimario,  FILE* arqIndicePrimarioNaoOrdenado, int nFunc){
    int i = 0;
    int chaves[nFunc+1];
    TFunc *f;

   /* for (int i = 1; i <= nFunc; i++)
    {
        f = funcionario(i, "Funcionario", "000.000.000-00", "27/05/1989", 5000.00);
        salva_funcionario(f, arq);
    }
    fflush(arq);*/

    int numero_aleatorio =0;
    char nome[] = "Funcionario";

    for(int i =0; i<nFunc; i++){
        // cria e preenche arquivo de funcionario
        // cria a string formatada
        snprintf(nome,sizeof(nome)+3,"Funcionario%d",i);

        numero_aleatorio = numero_aleatorio_unico(chaves, nFunc);

        TFunc *func = funcionario(numero_aleatorio, nome,"000.000.000-00","27/05/1989",5000);
        fseek(arq, (i) * tamanho_registro(), SEEK_SET);
        salva_funcionario(func, arq);
        // cria e preenche arquivo de chaves

       chaves[i]= func->cod;
        fwrite(&func->cod,sizeof(int), 1, arqIndicePrimario);  //escreve a chave
        fwrite(&i, sizeof(int), 1, arqIndicePrimario); //escreve o rrn
        free(func);
    }

    //escrevendo o arquivo de indice primario (chave e rrn) ordenado pela chave
    int aux = nFunc;
    for(int f = 1 ; f <=nFunc; f++){
        fwrite(&f, sizeof(int), 1, arqIndicePrimarioNaoOrdenado);  //escreve a chave
        fwrite(&chaves[aux], sizeof(int), 1, arqIndicePrimarioNaoOrdenado); //escreve o rrn
        aux--;
    }

}

void imprime_base_dados_funcionarios(FILE *arq, int nFunc) {
    rewind(arq);
    int i = 0;
    fseek(arq,  0 * sizeof (TFunc), SEEK_SET);
    if(arq != NULL) {

        int aux = 1;
        do{
            fseek(arq, (i) * tamanho_registro(), SEEK_SET);
            TFunc *func = le_funcionario(arq);
            if(func){
                imprime_funcionario(func);
                i++;
                free(func);
            }else aux = 0;
        }while(aux);
    }
    else printf("Erro ao abrir arquivo\n");
}

void imprime_indice_primario_funcionarios(FILE *arqIndicePrimario, int nFunc) {
    rewind(arqIndicePrimario);
    for(int i = 1 ; i <= nFunc ; i++){
        int chave, byteoffset;
        fread(&chave, sizeof(int), 1, arqIndicePrimario);
        fread(&byteoffset, sizeof(int), 1, arqIndicePrimario);
        printf("%d: %d\n", chave, byteoffset);
    }
}

