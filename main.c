#include <stdio.h>
#include <stdlib.h>

// LISTAS CIRCULARES
/*1. Definir los tipos necesarios para implementar una lista circular de enteros y realizar a través
de funciones correctamente parametrizadas los siguientes procesos:
a. Indicar si está ordenada ascendentemente. */

typedef struct nodoc {
    int entero;
    struct nodoc *sig;
} NODOC;

typedef NODOC *TLISTAC;

void llenaLista (TLISTAC *pult);
void muestraLista (TLISTAC ult);
void procesaLista (TLISTAC ult);

int main()
{
    TLISTAC lista = NULL;
    llenaLista(&lista);
    muestraLista(lista);
    procesaLista(lista);
    return 0;
}

void llenaLista (TLISTAC *pult)
{
    TLISTAC nuevo;
    int auxInt;
    FILE *arch = fopen("listaInicial.txt", "r");
    if (arch == NULL)
        printf("error al abrir archivo\n");
    else {
        while (!feof(arch) && fscanf(arch,"%d",&auxInt)==1) {
            nuevo = (TLISTAC)malloc(sizeof(NODOC));
            nuevo->entero = auxInt;
            if (*pult == NULL) {        // VACIA
                *pult = nuevo; (*pult)->sig = nuevo; 
            }
            else {
                nuevo->sig = (*pult)->sig;
                (*pult)->sig = nuevo;
                //act = nuevo; */
            }
        }
        fclose(arch);
        //free(aux);
    }
}

void muestraLista (TLISTAC ult)
{
    TLISTAC aux;
    if (ult != NULL) {
        aux = ult;
        do {
            aux = aux->sig;
            printf("%d\t", aux->entero);
        } while (aux != ult);
    }
    printf("\n");
}

void procesaLista (TLISTAC ult)
{
    TLISTAC act = ult->sig;
    while (act != ult && act->entero < act->sig->entero) {
        act = act->sig;
    }
    if (act == ult) {
        printf("lista ordenada\n");
    }
    else {
        printf("lista NO ordenada \n");
    }
}

