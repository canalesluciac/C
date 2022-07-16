#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxNombre 26
#define maxCod 3
#define maxTabla 8

/* Mediciones climáticas del servicio meteorológico en != ciudades
2 archivos: Mediciones (med. diarias de un det. año) + Provincias (info de c/provincia) */

typedef struct lugar {
    char nombre [maxNombre];
    char codigoPcia [maxCod];
} lugarStruct;

typedef struct {
    lugarStruct lugar;
    signed short int mes, dia;
    float minima, maxima;
} medicionStruct;

typedef struct {
    lugarStruct lugar;
    signed int superficie;
} provinciaStruct;

void llenaMediciones (); void llenaPcias ();
void muestraMediciones (); void muestraPcias ();
void creaTablaPcias (provinciaStruct tablaPcias[], int *n);
int buscaCodPcia (provinciaStruct tablaPcias[], char codPcia[], int n);
void resumenProvincia (provinciaStruct p[], int n, int vecMediciones[], int vecMayores20[]);
void procesa ();

int main()
{
    llenaPcias(); llenaMediciones ();
    muestraPcias (); muestraMediciones ();
    procesa();
    return 0;
}

void llenaMediciones ()
{
    medicionStruct m;
    FILE *medicionesTxt = fopen("MedicionesIM.txt", "r");
    FILE *medicionesBin = fopen("mediciones.dat", "wb");
    if (medicionesTxt == NULL)
        printf("\n error al abrir mediciones txt\n");
    else {
        while (fscanf(medicionesTxt,"%s %hu %hu %s %f %f", m.lugar.nombre, &m.mes, &m.dia, m.lugar.codigoPcia, &m.minima, &m.maxima)==6) {
            fwrite(&m, sizeof(medicionStruct), 1, medicionesBin);
        }
        fclose(medicionesBin); fclose(medicionesTxt);
    }
}

void llenaPcias ()
{
    provinciaStruct p;
    FILE *pciaTxt = fopen("ProvinciasIM.txt", "r");
    FILE *pciaBin = fopen("provincias.dat", "wb");
    if (pciaTxt == NULL)
        printf("\n error al abrir provincias txt\n");
    else {
        while (fscanf(pciaTxt,"%s %s %d", p.lugar.codigoPcia, p.lugar.nombre, &p.superficie)==3) {
            fwrite(&p, sizeof(provinciaStruct), 1, pciaBin);
        }
        fclose(pciaBin); fclose(pciaTxt);
    }
}

void muestraMediciones ()
{
    medicionStruct m;
    FILE *medBin = fopen("mediciones.dat", "rb");
    if (medBin == NULL)
        printf("\nError al grabar y/o mostrar mediciones binario\n");
    else {
        printf("MEDICIONES \nLUGAR\t\tMES\tDIA\tCOD\tMIN\tMAX\n");
        fread(&m, sizeof(medicionStruct),1,medBin);
        while (!feof(medBin)) {
            printf("%s\t%hu\t%hu\t%s\t%.1f\t%.1f\n", m.lugar.nombre, m.mes, m.dia, m.lugar.codigoPcia, m.minima, m.maxima);
            fread(&m, sizeof(medicionStruct),1,medBin);
        }
        printf("\n");
        fclose(medBin);
    }
}

void muestraPcias ()
{
    provinciaStruct p;
    FILE *pciaBin = fopen("provincias.dat", "rb");
    if (pciaBin == NULL)
        printf("error al abrir binario pcias \n");
    else {
        printf("PROVINCIAS\nCOD\tPROVINCIA\tSUPERFICIE\n");
        fread(&p, sizeof(provinciaStruct),1, pciaBin);
        while(!feof(pciaBin)) {
            printf("%s\t%s\t%d\n", p.lugar.codigoPcia, p.lugar.nombre, p.superficie);
            fread(&p, sizeof(provinciaStruct),1, pciaBin);
        }
        printf("\n");
        fclose(pciaBin);
    }
}

void creaTablaPcias (provinciaStruct tablaPcias[], int *n)
{
    FILE *pciaBin = fopen("provincias.dat", "rb");
    int cont = 0;
    if (pciaBin == NULL)
        printf("error al abrir pciaBin\n");
    else {
        fread(&tablaPcias[0], sizeof(provinciaStruct), 1, pciaBin);
        while (!feof(pciaBin) && cont < maxTabla) {
            cont++;
            fread(&tablaPcias[cont], sizeof(provinciaStruct), 1, pciaBin);
        }
        fclose(pciaBin);
    }
    *n = cont;
}

int buscaCodPcia (provinciaStruct tablaPcias[], char codPcia[], int n)
{
    int i = 0;
    while (i < n && strcmp(codPcia,tablaPcias[i].lugar.codigoPcia)) {
        i++;
    }
    return (i<n) ? i : -1;
}

void resumenProvincia (provinciaStruct p[], int n, int vecMediciones[], int vecMayores20[])
{
    int i; float aux;
    for (i = 0; i<n; i++) {
        aux = (vecMediciones[i] > 0)? (float) vecMayores20[i]*100/vecMediciones[i] : 0;
        printf("%s\t\t%d\t\t\t\t%.2f %% \n", p[i].lugar.nombre, vecMediciones[i], aux);
    }
}

void procesa ()
{
    int cantMedicionesMes, n, vecMediciones[maxTabla] = {0}, vecMayores20[maxTabla] = {0}, nroPcia;
    signed short int mesAct, diaMasCalurosoMesNro, mesMinNro, anioDia,anioMes;
    char ciudadAct [maxNombre], anioCiud[maxNombre];
    float anioMin, minSumaMes, maxSumaMes, diaMasCalurosoMesTemp, mesMinTemp;
    medicionStruct m; provinciaStruct p[maxTabla];
    FILE *medBin = fopen("mediciones.dat", "rb");
    FILE *actualBin = fopen("actualizado.dat", "wb");
    if (medBin == NULL)
        printf("\nerror al abrir binario mediciones \n");
    else {
        creaTablaPcias(p,&n);
        fread(&m, sizeof(medicionStruct), 1, medBin); printf("\n");
        anioMin = 999.9;
        while (!feof(medBin)) { // ARCHIVO (ANTES: GLOBALES)
            strcpy (ciudadAct, m.lugar.nombre);
            nroPcia = buscaCodPcia(p,m.lugar.codigoPcia,n);
            mesMinTemp = -999.9;
            printf("# Ciudad: %s\nMes\tMinProm\tMaxProm\tDia mas caluroso\n", ciudadAct);
            while (!feof(medBin) && !strcmp(ciudadAct,m.lugar.nombre)) { // CIUDAD (ANTES: RELATIVOS A C/CIUDAD)
                mesAct = m.mes;
                minSumaMes = 0.0; maxSumaMes = 0.0; cantMedicionesMes = 0; diaMasCalurosoMesNro = 0; diaMasCalurosoMesTemp = -999.9;
                while (!feof(medBin) && !strcmp(ciudadAct,m.lugar.nombre) && mesAct == m.mes) { // CIUDAD + MES
                    cantMedicionesMes++;
                    minSumaMes += m.minima; maxSumaMes += m.maxima;
                    if (m.maxima >= diaMasCalurosoMesTemp) {
                        diaMasCalurosoMesNro = m.dia;
                        diaMasCalurosoMesTemp = m.maxima;
                    }
                    if (m.minima <= anioMin) {
                        anioMin = m.minima;
                        anioDia = m.dia; anioMes = m.mes;
                        strcpy(anioCiud, m.lugar.nombre);
                    }
                    if (m.maxima > 20) {
                        vecMayores20[nroPcia]++;
                    }
                    fread(&m, sizeof(medicionStruct), 1, medBin);
                }
                vecMediciones[nroPcia] += cantMedicionesMes;
                printf("%hu\t%.1f \t%.1f \t%hu (%.1f)\n",mesAct,minSumaMes/cantMedicionesMes,maxSumaMes/cantMedicionesMes,diaMasCalurosoMesNro,diaMasCalurosoMesTemp);
                if (minSumaMes/cantMedicionesMes >= mesMinTemp) {
                    mesMinTemp = minSumaMes/cantMedicionesMes;
                    mesMinNro = mesAct;
                }
            }
            printf("Mes con mayor Temp.Min.Promedio: %hu (%.1f grados)\n\n", mesMinNro, mesMinTemp);
        }
        printf("Dia mas frio del anio en todo el pais: %hu-%hu (%.1f grados) en ciudad %s\n",anioDia,anioMes,anioMin,anioCiud);

        printf("\nResumen por provincia:\nProvincia\tCant. de Mediciones\tPorc. de Mediciones Temp.Max > 20 grados\n");
        resumenProvincia(p,n,vecMediciones, vecMayores20);
        fclose(medBin); fclose(actualBin);
    }
}
