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
        if (deck[i] != 'x' && deck[i] != 'D') {
            if (i != n)
                printf("%c, ", deck[i]);
            else
                printf("%c", deck[i]);
        }
        else if(deck[i] == 'D'){
            if(i != n)
                printf("10, ");
            else
                printf("10");
        }
    }
    printf("]");
    if (*mano != 'D')
        printf(" <%c>\n", *mano);
    else
        printf("<10>\n");
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


    printf("\n[t] - Poner en la parte superior\n");
    printf("[b] - Poner en la parte inferior\n");
    printf("[d] - Descartar\n[s] - Guardar partida\n[l] Cargar partida\n\n");


    char input[255];
    char opcion = 'x';

    imprimir(ptr, mano,*n);

    while(opcion == 'x'){
        printf("Opcion para carta: ");
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
                if (*mano != ' ')
                    ptr[*n] = *mano;
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

    unsigned short vacio = 0;
    char vacio_2 = 0;
    int indice = 10000;
    int letra;
    char a = *ptr;

    for (int i = 0; i < 5; i++){
        a = ptr[i];
        letra = (a == 'D')? 1: (a == 'J')? 2: (a == 'Q')? 3: (a == 'K')? 4: (a == 'A')? 5: 0;
        vacio = vacio + (indice * letra);
        indice = indice/10;
    }

    fwrite(&vacio, sizeof(unsigned short), 1, file);

    a = *mano;
    letra = (a == 'D')? 1: (a == 'J')? 2: (a == 'Q')? 3: (a == 'K')? 4: (a == 'A')? 5: 0;
    vacio_2 = vacio_2 + (letra * 10);
    vacio_2 += *n;

    fwrite(&vacio_2, sizeof(char), 1, file);
    fclose(file);
}

void cargar(char *ptr, char *mano, char *n){
    FILE *file = fopen("./deck", "r");

    unsigned short vacio = 0;
    char vacio_2 = 0;
    char letra;
    int indice = 10000;
    int a;

    fread(&vacio, sizeof(unsigned short), 1, file);
    fread(&vacio_2, sizeof(char), 1, file);


    for (int i = 0; i < 5; i++){
        a = vacio/indice;
        vacio = vacio - (a * indice);
        indice = indice/10;
        letra = (a == 1)? 'D': (a == 2)? 'J': (a == 3)? 'Q': (a == 4)? 'K': (a == 5)? 'A': 'x';
        ptr[i] = letra;
    }

    a = vacio_2/10;
    letra = (a == 1)? 'D': (a == 2)? 'J': (a == 3)? 'Q': (a == 4)? 'K': (a == 5)? 'A': ' ';
    *mano = letra;

    vacio_2 = vacio_2 - (a * 10);
    *n = vacio_2;

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
        printf("\nBaraja: ");
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
