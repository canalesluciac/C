#include <stdio.h>
#include <stdlib.h>

/*1. Definir los tipos necesarios para implementar una lista circular de enteros y realizar
a través de funciones correctamente parametrizadas los siguientes procesos:*/

typedef struct nodo {
    struct nodo *sig;
    int entero;
} NODOC;
typedef NODOC *TLISTA;

void llenaLista (TLISTA *pult);
void llenaLista2 (TLISTA *pult);
void muestraLista (TLISTA ult);
int estaOrdenada (TLISTA ult);
NODOC *direccionNodo (TLISTA lista, int nroNodo);
void insertaPorAnt (TLISTA *lista);
void insertaPorSgte (TLISTA *lista);
void insertaPorPosicion (TLISTA *lista);
void eliminaPorValor (TLISTA *lista);
void nuevaListaOrdenada (TLISTA ult1, TLISTA ult2, TLISTA *listaNueva);
void insertaNuevo (TLISTA *listaNueva, TLISTA nuevo);

int main()
{
    TLISTA lista = NULL, lista2 = NULL, listaNueva = NULL;
    llenaLista(&lista); printf("LISTA: "); muestraLista(lista);
    if (estaOrdenada (lista))
        printf("\t1a. lista ordenada\n");
    else
        printf("\t1a. lista NO ordenada\n");
    insertaPorAnt(&lista);
    insertaPorSgte (&lista);
    insertaPorPosicion (&lista);
    eliminaPorValor (&lista);
    llenaLista2(&lista2);
    nuevaListaOrdenada(lista, lista2, &listaNueva);
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
            if (*pult == NULL) { // VACIA
                *pult = nuevo;
                (*pult)->sig = *pult;
            }
            else {
                if ((*pult)->entero < auxNum) { // FINAL
                    nuevo->sig = (*pult)->sig;
                    (*pult)->sig = nuevo;
                    *pult = nuevo;
                }
                else {
                    act = *pult;
                    do {                    //BUSQUEDA
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

void llenaLista2 (TLISTA *pult)
{
    FILE *arch = fopen("listaInicial2.txt", "r");
    TLISTA nuevo, ant, act;
    int auxNum;
    if (arch == NULL)
        printf("error al abrir txt\n");
    else {
        while (!feof(arch) && fscanf(arch,"%d", &auxNum)==1) {
            nuevo = (TLISTA)malloc(sizeof(NODOC));
            nuevo->entero = auxNum;
            if (*pult == NULL) { // VACIA
                *pult = nuevo;
                (*pult)->sig = *pult;
            }
            else {
                if ((*pult)->entero < auxNum) { // FINAL
                    nuevo->sig = (*pult)->sig;
                    (*pult)->sig = nuevo;
                    *pult = nuevo;
                }
                else {
                    act = *pult;
                    do {                        // BUSQUEDA
                        ant = act; act = act->sig;
                    } while (auxNum > act->entero);

                    ant->sig = nuevo;
                    nuevo->sig = act;
                }
            }
        }
        fclose(arch);
        printf ("\nLISTA DOS: "); muestraLista(*pult);
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
    printf("\n\n");
}

int estaOrdenada (TLISTA ult)
{
    /*a. Indicar si está ordenada ascendentemente. */
    TLISTA act = ult->sig;
    while (act != ult && act->entero <= act->sig->entero) {
        act = act->sig;
    }
    if (act == ult) {
        return 1; //ordenada
    }
    else {
        return 0; // no ordenada
    }
}

NODOC *direccionNodo (TLISTA ult, int nroNodo)
{
    int cont;
    NODOC *aux;
    if (nroNodo < 1) { // NODO NO VALIDO (<1)
        aux = NULL;
    }
    else {
        cont = 1; aux = ult->sig;
        while (aux != ult && cont < nroNodo) {
            cont++;  // printf ("\ndireccion de %c = %p\n", aux->dato, &aux->dato);
            aux = aux->sig;
        };
        if (cont != nroNodo)
            aux = NULL;
    }
    return aux;
}

void insertaPorAnt (TLISTA *lista)
{
    /* b. Insertar conociendo la direccion del anterior (puntero).
    Tomar el último como anterior del primero, y nulo para insertar en una lista vacía.*/
    TLISTA ant, nuevo, direc;
    int nroAnt;
    nuevo = (TLISTA)malloc(sizeof(NODOC));
    printf("\n1b. INSERCION CONOCIENDO EL ANTERIOR\n");
    printf("\tposicion del bloque anterior: "); scanf("%d", &nroAnt);
    printf("\tnumero a insertar: "); scanf("%d", &nuevo->entero);
    direc = direccionNodo(*lista,nroAnt);
    if (!direc) {
        if (*lista == NULL) { // VACIA
            nuevo->sig = nuevo;
            *lista = nuevo;
        }
        else                // NO VALIDO
            printf("\tNodo no valido (y lista no esta vacia)\n");
    }
    else {
        if (direc == *lista) { // "FINAL"
            nuevo->sig = (*lista)->sig;
            (*lista)->sig = nuevo;
            *lista = nuevo;
        }
        else {                 // BUSQUEDA
            ant = (*lista)->sig;
            while (ant->sig != (*lista)->sig && direc != ant)
                ant = ant->sig;
            nuevo->sig = ant->sig;
            ant->sig = nuevo;

        }
    }
    printf("\tLISTA: ");
    muestraLista(*lista);
}

void insertaPorSgte (TLISTA *lista)
{
    /*c. Insertar conociendo la dirección del siguiente.
    Tomar el primero como siguiente del último, y nulo para insertar en una lista vacía*/
    TLISTA ant, act, nuevo, direc;
    int nroSgte;
    nuevo = (TLISTA)malloc(sizeof(NODOC));
    printf("\n1c. INSERCION CONOCIENDO EL SIGUIENTE\n");
    printf("\tposicion del bloque siguiente: "); scanf("%d", &nroSgte); fflush(stdin);
    printf("\tnumero a insertar: "); scanf("%d", &nuevo->entero);
    direc = direccionNodo(*lista,nroSgte);
    if (!direc) {
        if (*lista == NULL) { // VACIA
            nuevo->sig = nuevo;
            *lista = nuevo;
        }
        else                // NO VALIDO
            printf("Direccion no valida (y lista no esta vacia)\n");
    }
    else {
        act = (*lista)->sig; ant = (*lista);
        while (act != *lista && direc != act) {
            ant = act; act = act->sig;
        }
        if (direc == act) {
            nuevo->sig = act;
            ant->sig = nuevo;
        }
    }
    printf("\tLISTA: ");
    muestraLista(*lista);
}

void insertaPorPosicion (TLISTA *ult)
{
    int posX, posAct;
    TLISTA act, ant, nuevo;
    /*d. Insertar en la posicion n-ésima (considerar el caso que no pueda hacerlo)*/
    nuevo = (TLISTA)malloc(sizeof(NODOC));
    printf("\n1d. INSERCION POR POSICION\n");
    do { // CONTROL DE POSICION VALIDA
        fflush(stdin);
        printf("\tposicion valida (>=1) donde desea insertar nodo: ");
        scanf("%d", &posX);
    } while (posX<1);
    printf("\tnumero del entero: "); scanf("%d", &nuevo->entero);
    if (*ult == NULL) { // VACIA
        nuevo->sig = nuevo;
        *ult = nuevo;
    }
    else {
        if (posX == 1) { // PRINCIPIO
            nuevo->sig = (*ult)->sig;
            (*ult)->sig = nuevo;
        }
        else {
            ant = (*ult)->sig; act = ant->sig; posAct = 2;
            while (posAct < posX && act != (*ult)->sig) { // BUSQUEDA
                ant = act; act = act->sig; posAct++;
            }
            if (posAct == posX) {
                if (ant == *ult) { // FINAL
                    nuevo->sig = act;
                    ant->sig = nuevo;
                    *ult = nuevo;
                }
                else {          // INTERMEDIO
                    nuevo->sig = act; ant->sig = nuevo;
                }
            }
            else { // IMPOSIBLE
                    printf("\tposicion no permitida\n");
                    free(nuevo);
            }
        }
    }
    printf("\tLISTA: ");
    muestraLista(*ult);
}

void eliminaPorValor (TLISTA *lista)
{
    /*e. Eliminar los nodos que almacenen el valor X retornando la cantidad de eliminaciones.
    (puede no encontrarlo) */
    TLISTA ant, act;
    int valorX, eliminados;
    printf("\n1e. ELIMINACION POR VALOR");
    if (*lista == NULL)
        printf("\t0 nodos eliminados (lista vacia) \n");
    else {
        printf("\n\tvalor X a eliminar: "); scanf("%d", &valorX);
        eliminados = 0; act = *lista;
        if (estaOrdenada(*lista)) {
            do {
                ant = act; act = act->sig;
            } while (act != *lista && valorX > act->entero); // BUSQUEDA ORDENADA

            while (act->entero == valorX) { // ELIMINA 1+
                ant->sig = act->sig;
                if (act == *lista)
                    *lista = ant;
                free(act);
                act = ant->sig;
                eliminados++;
            }
        }
        else { // NO ORDENADA
            ant = act; act = act->sig;
            do {
                if (act->entero == valorX) {
                    if (act->sig == act) { // UNICO
                        free(act); *lista = NULL;
                    }
                    else {
                        ant->sig = act->sig;
                        if (act == *lista) {
                            *lista = ant;
                        }
                        free(act);
                        act = ant->sig;
                    }
                    eliminados++;
                }
                else { // AVANCE NORMAL
                    ant = act; act = act->sig;
                }
            } while (ant != *lista);
        }
        printf("\t%d nodos eliminados \n", eliminados);
        if (!eliminados)
            printf("\t(valor no encontrado)\n");
    }
    printf("\tLISTA: ");
    muestraLista(*lista);
}

void nuevaListaOrdenada (TLISTA l1, TLISTA l2, TLISTA *listaNueva)
{
    TLISTA nuevo, ultimo1 = l1, ultimo2 = l2, antUlt1 = NULL, antUlt2 = NULL;
    /*f. Obtener una lista circular ordenada a partir de dos listas circulares ordenadas*/
    if (estaOrdenada(l1) && estaOrdenada(l2)) {
        l1 = l1->sig; l2 = l2->sig;
        do {
            nuevo = (TLISTA)malloc(sizeof(NODOC));
            if (l1->entero  <  l2->entero) {
                nuevo->entero = l1->entero;
                insertaNuevo(listaNueva,nuevo); antUlt1 = l1;
                l1 = l1->sig;
            }
            else {
                nuevo->entero = l2->entero;
                insertaNuevo(listaNueva,nuevo);
                if (l1->entero  == l2->entero) { // MISMO VALOR
                    antUlt1 = l1; l1 = l1->sig;
                } antUlt2 = l2;
                l2 = l2->sig;
            }
        } while (antUlt1 != ultimo1 && antUlt1 != ultimo2);
        while (antUlt1 != ultimo1) { // NODOS PENDIENTES
            nuevo = (TLISTA)malloc(sizeof(NODOC));
            nuevo->entero = l1->entero;
            insertaNuevo(listaNueva,nuevo);
            antUlt1 = l1; l1 = l1->sig;
        }
        while (antUlt2 != ultimo2) {
            nuevo = (TLISTA)malloc(sizeof(NODOC));
            nuevo->entero = l2->entero;
            insertaNuevo(listaNueva,nuevo);
            antUlt2 = l2; l2 = l2->sig;
        }
        printf("\t2f. LISTA NUEVA: "); muestraLista(*listaNueva);
    }
    else {
        printf("1f. Una o ambas listas de entrada NO estan ordenadas.\n");
    }
}

void insertaNuevo (TLISTA *listaNueva, TLISTA nuevo)
{
    if (*listaNueva == NULL) { // VACIA
        *listaNueva = nuevo;
        (*listaNueva)->sig = *listaNueva;
    }
    else {
        nuevo->sig = (*listaNueva)->sig;
        (*listaNueva)->sig = nuevo;
        *listaNueva = nuevo;
    }
    //printf("%d ", (*listaNueva)->entero);
}
