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
}
/*funcion agregar torneo
 *permite agregar datos de un torneo y guardarlo en un txt*/
void agregartorneo(void) {
    Torneo torneo;
    FILE *archivo
    archivo = fopen("datos.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
        printf("ingrese el nombre del torneo: ");
        scanf("%s", torneo.nombre);
        printf("ingrese el deporte: ");
        scanf("%s", torneo.deporte);
        printf("ingrese el año");
        scanf("%d", &torneo.año);
        printf("ingrese el cantidadequipos: ");
        scanf("%d", &torneo.cantidadequipos);
        printf("el torneo esta activo?(1=si 0=no): ");
        scanf("%d", &torneo.activo);
        fprintf(archivo, "%s;%s;%d;%d\n", torneo.nombre, torneo.deporte, torneo.año, torneo.cantidadequipos, torneo.activo);
        fclose(archivo);
        printf("torneo guardado correctamente.\n");
}