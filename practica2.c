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
void mostrar_tauler(int tauler [MIDA][MIDA], int mostrar_tot);
void crear_flota(Vaixell vaixells[], int *num_vaixells, int tipus_flota);
int pot_colocar(int tauler[MIDA][MIDA], int fila, int col, int mida, int horitzontal);
void colocar_vaixell(int tauler[MIDA][MIDA], int fila, int col, int mida, int horitzontal);
int colocar_vaixells(int tauler[MIDA][MIDA], Vaixell vaixells[], int num_vaixells);
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
            crear_flota(vaixells, &num_vaixells, tipus_flota);
            tauler_valid = colocar_vaixells(tauler, vaixells, num_vaixells);
            if(tauler_valid) {
                printf("Tauler generat. Vols fer trampes i veure el tauler generat? (S/N): ");
                mostrar_tauler(tauler, 1);
            }
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
void mostrar_tauler(int tauler [MIDA][MIDA], int mostrar_tot) {
    printf("\n   | A B C D E F G H I J\n");
    printf("---+--------------------\n");
    for (int i = 0; i < MIDA; i++) {
        printf("%2d | ", i + 1);
        for (int j = 0; j < MIDA; j++){
            if(mostrar_tot) {
                printf("%d ", tauler[i][j]);
            } else {
                printf("%d ", tauler[i][j]);
            }
        }
        printf("\n");
    }
    
}
void crear_flota(Vaixell vaixells[], int *num_vaixells, int tipus_flota) {
    *num_vaixells = 0;
    if(tipus_flota == 1) {
        //Flota 1: K'Armada Vencible
        vaixells[(*num_vaixells)++] = (Vaixell){PORTAAVIONS, 0, "Portaavions"};
        vaixells[(*num_vaixells)++] = (Vaixell){CUIRASSAT, 0, "Cuirassat"};
        vaixells[(*num_vaixells)++] = (Vaixell){DESTRUCTOR, 0, "Destructor"};
        vaixells[(*num_vaixells)++] = (Vaixell){DESTRUCTOR, 0, "Destructor"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
    } else if (tipus_flota == 2)
    {
        //Flota 2: Els Brivalls
        vaixells[(*num_vaixells)++] = (Vaixell){CUIRASSAT, 0, "Cuirassat"};
        vaixells[(*num_vaixells)++] = (Vaixell){DESTRUCTOR, 0, "Destructor"};
        vaixells[(*num_vaixells)++] = (Vaixell){DESTRUCTOR, 0, "Destructor"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
    } else if (tipus_flota == 3)
    {
        //Flota 3: La Flotilla
        vaixells[(*num_vaixells)++] = (Vaixell){DESTRUCTOR, 0, "Destructor"};
        vaixells[(*num_vaixells)++] = (Vaixell){DESTRUCTOR, 0, "Destructor"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){FRAGATA, 0, "Fragata"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};
        vaixells[(*num_vaixells)++] = (Vaixell){SUBMARI, 0, "Submarí"};       
    }   
}
int pot_colocar(int tauler[MIDA][MIDA], int fila, int col, int mida, int horitzontal) {
//Hem de saber els limits del tauler, per això ho hem de comprovar
    if (horitzontal){
        if (col + mida > MIDA) return 0;      
    } else {
        if(fila + mida > MIDA) return 0;
    }

//Comprovem també que les caselles i el voltant estiguin buides
    for (int i = 0; i < mida; i++)    {
        int f = horitzontal ? fila : fila + i;
        int c = horitzontal ? col + i : col;
        
        for (int df = 0; df <= 1; df++){
            for (int dc = 0; dc <= 1; dc++){
                int nf = f + df;
                int nc = c + dc;
                if (nf >= 0 && nf < MIDA && nc >= 0 && nc < MIDA)
                {
                    if(tauler[nf][nc] == VAIXELL){
                        return 0;
                    }
                }
                
            }
            
        }
        
    }
    
return 1;
}
void colocar_vaixell(int tauler[MIDA][MIDA], int fila, int col, int mida, int horitzontal) {
    for (int i = 0; i < mida; i++) {
        if(horitzontal) {
            tauler[fila][col + i] = VAIXELL;
        } else {
            tauler[fila + i][col] = VAIXELL;
        }
    }
    
}
int colocar_vaixells(int tauler[MIDA][MIDA], Vaixell vaixells[], int num_vaixells){
    int intents_maxims = 10000;
    int intents = 0;

    for (int v = 0; v < num_vaixells; v++){
        int colocat = 0;
        int intents_vaixell = 0;

        while(!colocat && intents < intents_maxims) {
            int fila = rand() % MIDA;
            int col = rand() % MIDA;
            int horitzontal = rand() % 2;

            if(pot_colocar(tauler, fila, col, vaixells[v].mida, horitzontal)) {
                colocar_vaixell(tauler, fila, col, vaixells[v].mida, horitzontal);
                colocat = 1;
            }
            intents++;
            intents_vaixell++;
            if(intents_vaixell > 1000) {
                return 0;
            }
        }
        if(!colocat) {
            return 0;
        }
    }   
return 1;
}