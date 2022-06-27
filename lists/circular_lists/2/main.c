#include <stdio.h>
#include <stdlib.h>

/*1. Definir los tipos necesarios para implementar una lista circular de enteros y realizar
a través de funciones correctamente parametrizadas los siguientes procesos:
b. Insertar conociendo la direccion del anterior (puntero). Tomar el último como anterior
del primero, y nulo para insertar en una lista vacía.*/

typedef struct nodo {
    struct nodo *sig;
    int entero;
} NODOC;
typedef NODOC *TLISTA;

void llenaLista (TLISTA *pult);
void muestraLista (TLISTA ult);

int main()
{
    TLISTA lista = NULL;
    llenaLista(&lista);
    muestraLista(lista);
    return 0;
}

void llenaLista (TLISTA *pult)
{
    FILE *arch = fopen("listaInicial.txt", "r");
    TLISTA nuevo, ant, act;
    int auxNum;
    if (arch == NULL)
        printf("error al abrir txt\n");
    else {
        while (!feof(arch) && fscanf(arch,"%d", &auxNum)==1) {
            nuevo = (TLISTA)malloc(sizeof(NODOC));
            nuevo->entero = auxNum;
            if (*pult == NULL) { // EMPTY
                *pult = nuevo;
                (*pult)->sig = *pult;
            }
            else {
                if ((*pult)->entero < auxNum) { // at the end
                    nuevo->sig = (*pult)->sig;
                    (*pult)->sig = nuevo;
                    *pult = nuevo;
                }
                else {
                    act = *pult;
                    do {
                        ant = act; act = act->sig;
                    } while (auxNum > act->entero);

                    ant->sig = nuevo;
                    nuevo->sig = act;
                }
            }
        }
        fclose(arch);
    }
}

void muestraLista (TLISTA ult)
{
    TLISTA aux;
    if (ult != NULL) {
        aux = ult;
        do {
            aux = aux->sig;
            printf("%d ", aux->entero);
        } while (aux != ult);
    }
}
