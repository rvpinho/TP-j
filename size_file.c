#include "funcionarios.h"

int sizeFile(FILE *file, int contSizeFile) {

    int bytesAUX = 0;

    while(!feof(file)) {

        fseek(file, bytesAUX * sizeof(TFunc), SEEK_SET);

        TFunc *aux = le_funcionario(file);
        if(aux != NULL) {
            contSizeFile++;
        }

        bytesAUX++;
    }

    return contSizeFile;
}
