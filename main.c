#include <stdio.h>

typedef struct {
    char nombre[50];
    char deporte[30];
    int anio;
    int cantidadEquipos;
    int activo;
}Torneo;
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
    FILE *archivo;
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
        scanf("%d", &torneo.anio);
        printf("ingrese el cantidadequipos: ");
        scanf("%d", &torneo.cantidadEquipos);
        printf("el torneo esta activo?(1=si 0=no): ");
        scanf("%d", &torneo.activo);
        fprintf(archivo, "%s;%s;%d;%d\n", torneo.nombre, torneo.deporte, torneo.anio, torneo.cantidadEquipos, torneo.activo);
        fclose(archivo);
        printf("torneo guardado correctamente.\n");
}
// funcion listar
void listartorneos(void) {
    Torneo torneo;
    FILE *archivo;
    int cantidad=0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("\n no hay torneos para mostrar.\n");
        return;
    }
    printf("\n---lista torneos---\n");
    while (fscanf(archivo,"%s;%s;%d;%d;%d;%d",
        torneo.nombre,
        torneo.deporte,
        &torneo.anio,
        &torneo.cantidadEquipos,
        &torneo.activo)==5) {
        printf("\nNombre: %s\n",torneo.nombre);
        printf("\nDeporte: %s\n",torneo.deporte);
        printf("año:%d\n"torneo.anio);
        printf("cantidad de equipos: %d\n",torneo.cantidadEquipos);

        if (torneo.activo == 1) {
            printf("estado:activo\n\n");
        }else {
            printf("estado:inactivo\n");
        }
        cantidad++;
        }
    if (cantidad==0) {
        printf("no hay torneos cargados.\n");
    }
    fclose(archivo);
}//