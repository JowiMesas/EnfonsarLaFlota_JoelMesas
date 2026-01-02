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
#define TOCAT 1
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
void processar_coordenades(char coord[10], int *fila, int *col, int *valid);
int disparar(int tauler[MIDA][MIDA], int tauler_visible[MIDA][MIDA], Vaixell vaixells[],int num_vaixells, int fila, int col);
void revelar_aigua_voltant(int tauler[MIDA][MIDA], int tauler_visible[MIDA][MIDA], int fila,int col, int mida, int horitzontal);
char llegir_opcio();
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
        while (!tauler_valid)  {
            inicialitzar_tauler(tauler);
            inicialitzar_tauler(tauler_visible);
            crear_flota(vaixells, &num_vaixells, tipus_flota);
            tauler_valid = colocar_vaixells(tauler, vaixells, num_vaixells);
            if(tauler_valid) {
                printf("Tauler generat. Vols fer trampes i veure el tauler generat? (S/N): ");
                opcio = llegir_opcio();
                if (opcio == 'S'){
                    mostrar_tauler(tauler, 1);
                    printf("\n Vols generar un nou tauler? (S/N): ");
                    opcio = llegir_opcio();
                    if (opcio == 'S'){
                       tauler_valid = 0;
                    }
                    
                }
                
            }
        }
        printf("\n Comença la partida...\n");
        tirades = 0;
        while (1){
            printf("\n Introdueix coordenades (ex: A5): ");
            scanf("%s", coordenades);
            processar_coordenades(coordenades, &fila, &columna, &valid);
            if (!valid){
                printf("Coordenades invàlides! Utilitza format lletra (A-J) + número(1-10) \n");
                continue;
            }
            if (tauler_visible[fila][columna] != AIGUA) {
                printf("Ja has disparat a aquesta posició!\n");
                continue;
            }
            tirades++;
            resultat = disparar(tauler, tauler_visible, vaixells, num_vaixells, fila, columna);
            if(resultat == 0) {
                printf("Aigua!\n");
            } else if(resultat == 1) {
                printf("Tocat! \n");
            } else if(resultat == 2) {
                printf("Tocat i enfonsat! \n");
            }
            mostrar_tauler(tauler_visible, 0);
            
        }
        printf("\n Vols jugar una nova partida? (S/N): ");
        opcio = llegir_opcio();
        nova_partida = (opcio == 'S');
    }
    printf(" \n Gràcies per jugar!\n");
    return 0;
}
char llegir_opcio() {
    char opcio;
    scanf(" %c", &opcio);
    return toupper(opcio);
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
void processar_coordenades(char coord[10], int *fila, int *col, int *valid){
    *valid = 0;
    if (coord[0] == '\0' || coord[1] == '\0'){
       return;
    }
    char lletra = toupper(coord[0]);
    if (lletra < 'A' || lletra > 'J') {
        return;
    }
    *col = lletra - 'A';
    int num = atoi(&coord[1]);
    if (num < 1 || num > 10) {
      return;
    }
    *fila = num - 1;
    *valid = 1;
}
int disparar(int tauler[MIDA][MIDA], int tauler_visible[MIDA][MIDA], Vaixell vaixells[], 
int num_vaixells, int fila, int col){
if (tauler[fila][col] == VAIXELL){
    tauler_visible[fila][col] = TOCAT;    
    //Ara hem de saber el vaixell que hem tocat
    int mida_vaixell = 0;
    int horitzontal = 0;
    int fila_inici = fila;
    int col_inici = col;
    //També cap a on esta orientat i la seva mida
    if (col > 0 && tauler[fila][col - 1] == VAIXELL) {
       horitzontal = 1; 
    } else if (col < MIDA - 1 && tauler[fila][col + 1] == VAIXELL) {
        horitzontal = 1;
    } else if (fila > 0 && tauler[fila - 1][col] == VAIXELL){
        horitzontal = 0;
    } else if (fila < MIDA - 1 && tauler[fila + 1][col] == VAIXELL) {
        horitzontal = 0;
    }
    //Trobar el començament del vaixell
    if(horitzontal) {
        while (col_inici > 0 && tauler[fila][col_inici - 1] == VAIXELL){
           col_inici--;
        }
        while (col_inici + mida_vaixell < MIDA && tauler[fila][col_inici + mida_vaixell] == VAIXELL){
            mida_vaixell++;
        } 
    } else {
        while (fila_inici > 0 && tauler[fila_inici - 1][col]== VAIXELL){
            fila_inici--;
        }
        while (fila_inici + mida_vaixell < MIDA && tauler[fila_inici + mida_vaixell][col] == VAIXELL){
            mida_vaixell++;
        }      
    }
    //Hem de saber també si el vaixell esta enfonsat
    int enfonsat = 1;
    for (int i = 0; i < mida_vaixell; i++) {
        int f = horitzontal ? fila_inici : fila_inici + i;
        int c = horitzontal ? col_inici + i : col_inici;
        if(tauler_visible[f][c] != TOCAT) {
            enfonsat = 0;
            break;
        }
    }
    if(enfonsat) {
        revelar_aigua_voltant(tauler, tauler_visible, fila_inici, col_inici, mida_vaixell, horitzontal);
        return 2; //QUe aixo significa tocat i enfonsat
    }
    return 1; //Només tocat

} else {
    tauler_visible[fila][col] == AIGUA_DISPARADA;
    return 0; // Aigua 
}
}
void revelar_aigua_voltant(int tauler[MIDA][MIDA], int tauler_visible[MIDA][MIDA], int fila,
int col, int mida, int horitzontal) {
    for (int i = 0; i < mida; i++){
        int f = horitzontal ? fila : fila + i;
        int c = horitzontal ? col + i : col;
        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++){
                int nf = f + df;
                int nc = c + dc;
                if (nf >= 0 && nf < MIDA && nc >= 0 && nc < MIDA){
                 if (tauler_visible[nf][nc]== AIGUA){
                    tauler_visible[nf][nc]== AIGUA_DISPARADA;
                 }
                }               
            }           
        }      
    }  
}