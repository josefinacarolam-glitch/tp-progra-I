#include <stdio.h>

typedef struct {
    char nombre[50];
    char deporte[30];
    int año;
    int cantidadequipos;
    int activo;
}torneo;
//prototipo funciones
void mostrarmenu(void);
void agregartorneo(void);
void listartorneos(void);
void listartorneosactivos(void);
void separartorneos(void);

int main() {
    int opcion;
    //menu + switch con lo elegido
    do {
        mostrarmenu();
        printf("seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                agregartorneo();
                break;
            case 2:
                listartorneos();
                break;
            case 3:
                listartorneosactivos();
                break;
            case 4:
                separartorneos();
                break;
            case 5:
                printf("saliendo del sistema.\n");
                break;
            default:
                printf("opcion incorrecta intente denuevo.\n");
        }
    }while (opcion != 5);
    return 0;
}//avances menu sin funciones por el momento