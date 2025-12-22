/*
Programa: Enfonsar la Flota
Autor: Joel Mesas
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MIDA 10
#define AIGUA 0
#define VAIXELL 1
#define AIGUA_DISPARADA 2

// Caselles dels tipus de vaixells
#define PORTAAVIONS 5
#define CUIRASSAT 4
#define DESTRUCTOR 3
#define FRAGATA 2
#define SUBMARI 1

//Estructura per a poder guardar la informació de cada vaixell
typedef struct 
{
    int mida;
    int tocats;
    char nom[20];

} Vaixell;
void presentar_joc();
int escollir_flota();
void inicialitzar_tauler(int tauler[MIDA][MIDA]);
int main() {
    int tauler[MIDA][MIDA];
    int tauler_visible [MIDA][MIDA];
    Vaixell vaixells[10];
    int num_vaixells = 0;
    int tipus_flota;
    char coordenades[10];
    int fila, columna, valid;
    int resultat;
    int tirades = 0;
    char opcio;
    int nova_partida = 1;

    srand(time(NULL));
    while(nova_partida) {
        presentar_joc();
        tipus_flota = escollir_flota();

        printf("\n Preparant tauler de la flota %d ... \n", tipus_flota);
        int tauler_valid = 0;
        while (!tauler_valid)
        {
            inicialitzar_tauler(tauler);
            inicialitzar_tauler(tauler_visible);
        }
        
        nova_partida = 0;
    }
}
void presentar_joc() {
    printf("\n**************************\n");
    printf("*** ENFONSAR LA FLOTA! ***\n");
    printf("**************************\n");

    printf("Escull una flota: \n");
    printf("1: L'Armada Vencible\n");
    printf("2: Els Brivalls\n");
    printf("3: La Flotilla\n");
}
int escollir_flota() {
    int opcio;
    do {
        printf("Introdueix el número de la flota(1-3): ");
        if(scanf(" %d", &opcio) != 1) {
            while (getchar() != '\n');
            opcio = 0;
        }
    } while (opcio < 1 || opcio > 3 );
return opcio;
}
void inicialitzar_tauler(int tauler[MIDA][MIDA]) {
    for (int i = 0; i < MIDA; i++){
        for (int j = 0; j < MIDA; j++)
        {
            tauler[i][j] = AIGUA;
        }
        
    }
    
}