#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*2. Definir los tipos necesarios para implementar una lista doble de caracteres
y realizar a través de funcones correctamente parametrizadas los siguientes procesos: */

typedef char TELEMENTOLD;

typedef struct nodold {
    TELEMENTOLD dato;
    struct nodold *ant, *sig;
} NODOLD;

typedef struct tlistad {
    NODOLD *pri, *ult; // pri->ant y ult->sig son NULOS
} TLISTAD;

void iniciaLista (TLISTAD *lista);
void nodoNuevo (TLISTAD *lista, NODOLD *nuevo);
void llenaPorCabeza (TLISTAD *lista);
void llenaLista (TLISTAD *lista);
void llenaLista2 (TLISTAD *lista);
void muestraLista (TLISTAD lista);
void recorreInverso (TLISTAD lista);
int estaOrdenada (TLISTAD lista);
int ordenadaDescendente (TLISTAD lista);
NODOLD *direccionNodo (TLISTAD lista, int nroNodo);
void insertaPorAnterior (TLISTAD *lista);
void insertaPorSgte (TLISTAD *lista);
void insertaPorPosicion (TLISTAD *lista);
void eliminaPorValor (TLISTAD *lista);
void generaLista (TLISTAD lista, TLISTAD lista2, TLISTAD *listinha);
int esPalindroma (TLISTAD lista);

int main()
{
    TLISTAD lista, lista2, lista3;
    iniciaLista(&lista); llenaLista(&lista);// llenaPorCabeza (&lista);
    muestraLista(lista); recorreInverso(lista);
    if (ordenadaDescendente(lista))
        printf("\t2a. lista ordenada descendentemente\n");
    else
        printf("\t2a. lista NO ordenada descendentemente\n");
    insertaPorAnterior(&lista); insertaPorSgte(&lista); insertaPorPosicion(&lista);
    eliminaPorValor(&lista);
    iniciaLista(&lista2); llenaLista2(&lista2); iniciaLista(&lista3); generaLista(lista, lista2, &lista3);
    if (esPalindroma(lista))
        printf("\t2g. Lista ES palindroma\n");
    else
        printf("\t2g. Lista NO es palindroma\n");
    return 0;
}

void iniciaLista (TLISTAD *lista)
{
    lista->pri = NULL;
    lista->ult = NULL;
}

void nodoNuevo (TLISTAD *lista, NODOLD *nuevo)
{
    NODOLD *aux;
    if (lista->pri == NULL  || nuevo->dato <= lista->pri->dato) { // PRINCIPIO
        nuevo->sig = lista->pri;
        nuevo->ant = NULL;
        if (lista->pri == NULL) // VACIA
            lista->ult = nuevo;
        else                    // 1ER ELEMENTO
            lista->pri->ant = nuevo;
        lista->pri = nuevo;
    }
    else {
        if (nuevo->dato > lista->ult->dato) { // FINAL
            nuevo->ant = lista->ult; nuevo->sig = NULL;
            lista->ult->sig = nuevo;
            lista->ult = nuevo;
        }
        else {                  // BUSQUEDA
            aux = lista->pri;
            while (nuevo->dato > aux->dato)
                aux = aux->sig;
            nuevo->sig = aux; nuevo->ant = aux->ant;
            aux->ant->sig = nuevo; aux->ant = nuevo;
        }
    }
}

void llenaPorCabeza (TLISTAD *lista)
{
    NODOLD *nuevo;
    char carAux;
    FILE *arch = fopen("listaInicial.txt", "r");
    if (arch == NULL)
        printf("error al abrir txt \n");
    else {
        while (fscanf(arch,"%c", &carAux)==1) {
            nuevo = (NODOLD*)malloc(sizeof(NODOLD));
            nuevo->dato = carAux;
            if (lista->pri == NULL) { // PRINCIPIO
                nuevo->sig = lista->pri; nuevo->ant = NULL;
                lista->ult = nuevo; lista->pri = nuevo;
            }
            else {
                nuevo->sig = NULL; nuevo->ant = lista->ult;
                lista->ult->sig = nuevo; lista->ult = nuevo;
            }
        }
        fclose(arch);
    }
}

void llenaLista (TLISTAD *lista)
{
    NODOLD *nuevo;
    char carAux;
    FILE *arch = fopen("listaInicial.txt", "r");
    if (arch == NULL)
        printf("error al abrir txt \n");
    else {
        while (fscanf(arch,"%c", &carAux)==1) {
            nuevo = (NODOLD*)malloc(sizeof(NODOLD));
            nuevo->dato = carAux;
            nodoNuevo(lista, nuevo);
        }
        fclose(arch);
    }
}

void llenaLista2 (TLISTAD *lista)
{
    NODOLD *nuevo;
    char carAux;
    FILE *arch = fopen("listaInicial2.txt", "r");
    if (arch == NULL)
        printf("error al abrir txt \n");
    else {
        while (fscanf(arch,"%c", &carAux)==1) {
            nuevo = (NODOLD*)malloc(sizeof(NODOLD));
            nuevo->dato = carAux;
            nodoNuevo(lista, nuevo);
        }
        fclose(arch);
    }
}

void muestraLista (TLISTAD lista) // lista es struct
{
    NODOLD *aux = lista.pri;
    printf("LISTA:\t");
    while (aux != NULL) {
        printf("%c ", aux->dato); // printf("%p \n", aux);
        aux = aux->sig;
    }
    printf("\n\n");
}

void recorreInverso (TLISTAD lista)
{
    NODOLD *aux = lista.ult;
    printf("LISTA DESCENDENTE:\t");
    while (aux != NULL) {
        printf("%c ", aux->dato);
        aux = aux->ant;
    }
    printf("\n\n");
}

int estaOrdenada (TLISTAD lista)
{
    char carAux = lista.pri->dato;
    NODOLD *aux = lista.pri;
    while (aux != NULL &&  carAux <= aux->dato) {
        carAux = aux->dato;
        aux = aux->sig;
    }
    if (aux == NULL)
        return 1;
    else
        return 0;
}

int ordenadaDescendente (TLISTAD lista)
{
    // a. Indicar si está ordenada descendentemente
    char carAux = lista.pri->dato;
    NODOLD *aux = lista.pri;
    while (aux != NULL &&  aux->dato <= carAux) {
        carAux = aux->dato;
        aux = aux->sig;
    }
    if (aux == NULL)
        return 1;
    else
        return 0;
}

NODOLD *direccionNodo (TLISTAD lista, int nroNodo)
{
    int cont;
    NODOLD *aux;
    if (nroNodo < 0) { // NODO NO VALIDO (<0)
        aux = NULL;
    }
    else {
        cont = 1; aux = lista.pri;
        while (aux != NULL && cont < nroNodo) {
            cont++;  // printf ("\ndireccion de %c = %p\n", aux->dato, &aux->dato);
            aux = aux->sig;
        };
    }
    return aux;
}

void insertaPorAnterior (TLISTAD *lista)
{
    // b. Insertar conociendo la dirección del anterior (puntero), nulo para insertar al principio
    NODOLD *nuevo, *aux, *direccion;
    int nroNodo; char carAux;
    printf("\n\t2b. Ingrese el nro del NODO ANTERIOR (para obtener su direccion): "); scanf("%d", &nroNodo);
    fflush(stdin);
    printf ("\tIngrese un caracter a insertar: "); scanf("%c", &carAux);
    nuevo = (NODOLD*)malloc(sizeof(NODOLD)); nuevo->dato = carAux;
    if (nroNodo)
        direccion = direccionNodo(*lista,nroNodo);
    else
        direccion = NULL;
    if (lista->pri == NULL || direccion == NULL) {
        nuevo->sig = lista->pri; nuevo->ant = NULL;
        if (lista->pri == NULL) // VACIA
            lista->ult = nuevo;
        else                    // DIRECCION NULL
            lista->pri->ant = nuevo;
        lista->pri = nuevo;
    }
    else {
        if (direccion->sig == NULL) { // AL FINAL
            nuevo->sig = NULL; nuevo->ant = lista->ult;
            lista->ult->sig = nuevo; lista->ult = nuevo;
        }
        else { // BUSQUEDA
            aux = lista->pri;
            while(aux != direccion) {
                aux = aux->sig;
            }
            nuevo->sig = aux->sig; nuevo->ant = aux;
            aux->sig->ant = nuevo; aux->sig = nuevo;
        }
    }
    muestraLista(*lista);
}

void insertaPorSgte (TLISTAD *lista)
{
    // c. Insertar conociendo la dirección del siguiente, nulo para insertar al final
    NODOLD *nuevo, *aux, *direccion;
    int nroNodo; char carAux;
    printf("\n\t2b. Ingrese el nro del NODO SIGUIENTE (para obtener su direccion): "); scanf("%d", &nroNodo);
    fflush(stdin);
    printf ("\tIngrese un caracter a insertar: "); scanf("%c", &carAux);
    nuevo = (NODOLD*)malloc(sizeof(NODOLD)); nuevo->dato = carAux;
    if (lista->pri == NULL) { // VACIA
        nuevo->sig = lista->pri; nuevo->ant = NULL;
        lista->ult = nuevo; lista->pri = nuevo;
    }
    else {
        direccion = direccionNodo(*lista,nroNodo);
        if (!direccion) { // FINAL
            nuevo->sig = NULL; nuevo->ant = lista->ult;
            lista->ult->sig = nuevo; lista->ult = nuevo;
        }
        else {
            if (!direccion->ant) { // INICIO
                nuevo->sig = lista->pri; nuevo->ant = NULL;
                lista->pri->ant = nuevo; lista->pri = nuevo;
            }
            else { // BUSQUEDA
                aux = lista->ult;
                while(aux != direccion) {
                    aux = aux->ant;
                }
                nuevo->sig = aux; nuevo->ant = aux->ant;
                aux->ant->sig = nuevo; aux->ant = nuevo;
                }
        }
    }
    muestraLista(*lista);
}

void insertaPorPosicion (TLISTAD *lista)
{
    // d. Insertar en la posición n-ésima (considerar el caso que no pueda hacerlo)
    int pos = 0, cont = 1;
    NODOLD *nuevo, *aux;
    char auxChar;
    printf("\n");
    while (pos <1) {
        printf("\t2d. Ingrese la posicion (donde insertar nuevo nodo): "); scanf("%d", &pos);
        fflush(stdin);
    }
    printf("\tIngrese el caracter a insertar: "); scanf("%c", &auxChar);
    nuevo = (NODOLD*)malloc(sizeof(NODOLD)); nuevo->dato = auxChar;
    if (pos == 1) {
        nuevo->sig = lista->pri; nuevo->ant = NULL;
        if(lista == NULL)      // VACIA
            lista->ult = nuevo;
        else                    // AL PRINCIPIO (POSICION == 1)
            lista->pri->ant = nuevo;
        lista->pri = nuevo;
    }
    else {
        aux = lista->pri;
        while (aux != NULL && cont < pos) { // BUSQUEDA
            cont++; aux = aux->sig;
        }
        if (aux != NULL) {
            nuevo->ant = aux->ant; nuevo->sig = aux;
            aux->ant->sig = nuevo; aux->ant = nuevo;
        }
        else {
            if (cont == pos) { // FINAL
                nuevo->sig = NULL; nuevo->ant = lista->ult;
                lista->ult->sig = nuevo; lista->ult = nuevo;
            }
            else {
                printf("\tPosicion (%d) mayor a cantidad de lugares donde insertar nodo (%d)\n", pos, cont);
                free(nuevo);
            }
        }
    }
    muestraLista(*lista);
}

void eliminaPorValor (TLISTAD *lista)
{
    // e. Eliminar los nodos que almacenen el valor X retomando la cantidad de eliminaciones (puede no encontrarlo)
    char auxValor;
    int contElim = 0;
    NODOLD *aux, *prox;
    if (lista->pri == NULL) {   // VACIA
        printf("\t2e. Imposible eliminar. Lista ya se encuentra vacia\n");
    }
    else {
        aux = lista->pri;
        printf("\n\t2e. Valor X a eliminar de los nodos de la lista: "); scanf("%c", &auxValor);
        while (aux != NULL) {
            if (aux->dato == auxValor) { // ELIMINA Y AVANZA
                contElim++;
                if (lista->pri == lista->ult) { // único
                        free(aux); lista->pri = NULL; lista->ult = NULL;
                }
                else {
                    if (aux->ant == NULL) {     // primero
                        aux = aux->sig; aux->ant = NULL;
                        free(lista->pri);
                        lista->pri = aux;
                    }
                    else {
                        if (aux->sig == NULL) { // último
                            lista->ult = aux->ant; lista->ult->sig = NULL;
                            free(aux);
                        }
                        else {
                            prox = aux->sig;
                            aux->ant->sig = aux->sig;
                            aux->sig->ant= aux->ant;
                            free(aux); aux = prox;
                        }
                    }
                }
            }
            else // AVANCE NORMAL
                aux = aux->sig;
        }
    }
    printf("\t%d nodos eliminados\n", contElim);
    muestraLista(*lista);
}

void generaLista (TLISTAD lista, TLISTAD lista2, TLISTAD *listinha)
{
    // f. Obtener una lista doble ordenada a partir de dos listas dobles ordenadas
    NODOLD *nuevo;
    if (estaOrdenada(lista) && estaOrdenada(lista2)) {
        while (lista.pri != NULL && lista2.pri != NULL) {
            nuevo = (NODOLD*)malloc(sizeof(NODOLD));
            if (lista.pri->dato < lista2.pri->dato) {
                nuevo->dato = lista.pri->dato;
                nodoNuevo(listinha, nuevo);
                lista.pri = lista.pri->sig;
            }
            else {
                if (lista.pri->dato > lista2.pri->dato) {
                    nuevo->dato = lista2.pri->dato;
                    nodoNuevo(listinha, nuevo);
                    lista2.pri = lista2.pri->sig;
                }
                else {
                    if (lista.pri->dato == lista2.pri->dato) {
                        nuevo->dato = lista.pri->dato;
                        nodoNuevo(listinha, nuevo);
                        lista.pri = lista.pri->sig;
                        lista2.pri = lista2.pri->sig;
                    }
                }
            }
        }
        while (lista.pri != NULL) {
            nuevo = (NODOLD*)malloc(sizeof(NODOLD)); nuevo->dato = lista.pri->dato;
            nodoNuevo(listinha, nuevo);
            lista.pri = lista.pri->sig;
        }
        while (lista2.pri != NULL) {
            nuevo = (NODOLD*)malloc(sizeof(NODOLD)); nuevo->dato = lista2.pri->dato;
            nodoNuevo(listinha, nuevo);
            lista2.pri = lista2.pri->sig;
        }
        printf("\n\t2f. LISTA NUEVA GENERADA\n\t");
        muestraLista(*listinha);
    }
    else {
        printf("\n\t2f. Error. Alguna de las listas de entrada no esta ordenada (ascendentemente)\n");
    }

}

int esPalindroma (TLISTAD lista)
{
    // g. Verificar si la palabra que se forma con los valores de sus nodos es palíndroma
    NODOLD *start = lista.pri, *end = lista.ult;
    while(start->dato == end->dato && start != end) {
        start = start->sig;
        end = end->ant;
    }
    if (start == end) // PALINDROMA
        return 1;
    else
        return 0;
}


