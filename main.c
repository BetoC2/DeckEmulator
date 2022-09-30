#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crear_baraja(char*);
void pull(char*, char*, char*);
void bottom(char*, int);
void discard(char*, int);
void guardar(char*, char*, char*);
void cargar(char*, char*, char*);

void imprimir(char *deck, char *mano, int n){
    printf("[");
    for(int i = 0; i <= n; i++){
        if (deck[i] != 'x') {
            if (i != n)
                printf("%c, ", deck[i]);
            else
                printf("%c", deck[i]);
        }
    }
    printf("]");
    printf(" <%c>\n", *mano);
}

void crear_baraja(char *target) {
    char deck[] = "DJQKA";
    int random;
    int i = 0;

    while (i < 5) {
        random = rand() % 5;
        if (deck[random] != 'x'){
            *(target + i) = deck[random];
            *(deck + random) = 'x';
            i++;
        }
    }
}

void pull(char *ptr, char *n, char *mano){


    printf("[t] - Poner en la parte superior\n");
    printf("[b] - Poner en la parte inferior\n");
    printf("[d] - Descartar\n[s] - Guardar partida\n[l] Cargar partida\n");


    char input[255];
    char opcion = 'x';

    imprimir(ptr, mano,*n);

    while(opcion == 'x'){
        fgets(input,255,stdin);
        char opcion = input[0];

        switch(opcion){
            case 't':
                printf("La carta se coloco en la parte superior\n");
                opcion = 'a';
                ptr[*n] = *mano;
                *mano = ' ';
                return;
            case 'b':
                bottom(ptr, *n);
                printf("La carta se coloco en la parte inferior\n");
                opcion = 'a';
                *mano = ' ';
                return;
            case 'd':
                discard(ptr, *n);
                *n = *n-1;
                opcion = 'a';
                *mano = ' ';
                return;
            case 's':
                guardar(ptr, mano, n);
                return;
            case 'l':
                cargar(ptr, mano, n);
                return;
            default:
                printf("No le sabe\n");
                opcion = 'x';
                break;
        }
    }
}

void bottom(char *ptr, int n){
    char a;
    for(int i = n; i > 0; i--){
        a = ptr[i];
        ptr[i] = ptr[i-1];
        ptr[i-1] = a;
    }
}

void discard(char *ptr, int n){
    ptr[n] = 'x';
}

void guardar(char *ptr, char *mano, char *n){

    FILE *file = fopen("./deck", "w");

    rewind(file);
    for (int i = 0; i < 5; i++){
        fwrite(ptr + i, sizeof(char), 1, file);
    }
    fwrite(mano, sizeof(char), 1, file);
    fwrite(n, sizeof(char), 1, file);

    fclose(file);
}

void cargar(char *ptr, char *mano, char *n){
    FILE *file = fopen("./deck", "r");

    for (int i = 0; i < 5; i++){
        fread(ptr + i, sizeof(char), 1, file);
    }
    fread(mano, sizeof(char), 1, file);
    fread(n, sizeof(char), 1, file);

    fclose(file);
}

int main(void) {
    srand(time(NULL));
    char baraja[5];
    char en_mano = ' ';
    char input[255];
    char cartas = 4;

    crear_baraja(baraja);

    printf("[p] - Tomar carta de la parte superior del deck\n");
    printf("[s] - Guardar la partida\n");
    printf("[l] - Cargar la partida\n");
    printf("[e] - Salir del programa\n");

    while (baraja[0] != 'x'){
        printf("Baraja: ");
        imprimir(baraja, &en_mano, cartas);
        printf("Elige tu opcion: ");

        fgets(input, 255, stdin);
        char opcion = input[0];

        switch(opcion){
            case 'p':
                if (en_mano == ' ') {
                    en_mano = baraja[cartas];
                    baraja[cartas] = 'x';
                }
                pull(baraja, &cartas, &en_mano);
                break;

            case 's':
                guardar(baraja, &en_mano, &cartas);
                break;

            case 'l':
                cargar(baraja, &en_mano, &cartas);
                break;

            case 'e':
                printf("Finalizando programa\n");
                return 0;

            default:
                printf("Elije una opcion valida\n");
                break;
        }
    }
    printf("Ya no hay cartas en la baraja, finalizando programa");
    return 0;
}
