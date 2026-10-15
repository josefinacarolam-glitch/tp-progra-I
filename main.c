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
int leertorneo(FILE *archivo,Torneo *torneo);
void escribirtorneo(FILE *archivo, Torneo torneo);
void limpiarbuffer(void);

int main() {
    int opcion;
    //menu + switch con lo elegido
    do {
        mostrarmenu();
        printf("seleccione una opcion: ");
        if (scanf("%d", &opcion)==1) {
            limpiarbuffer();

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
        }else {
            printf("opcion incorrecto.\n");
            limpiarbuffer();
            opcion = 0;
        }
    }while (opcion!=5);

    return 0;
}
//muestra las opciones del menu disponibles
void mostrarmenu(void) {
    printf("\n-- SISTEMA DE TORNEOS DEPORTIVOS --\n");
    printf("1. Agregar un torneo\n");
    printf("2. Listar todos los torneos\n");
    printf("3. Listar torneos activos\n");
    printf("4. Separar torneos en dos archivos\n");
    printf("5. Salir\n");
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
        scanf("%49s", torneo.nombre);
        printf("ingrese el deporte: ");
        scanf("%29s", torneo.deporte);
        printf("ingrese el año");
        scanf("%d", &torneo.anio);
        printf("ingrese el cantidadequipos: ");
        scanf("%d", &torneo.cantidadEquipos);
        printf("el torneo esta activo?(1=si 0=no): ");
        scanf("%d", &torneo.activo);
        if (torneo.activo != 0 && torneo.activo != 1) {
            printf("Error: debe ingresar 0 o 1.\n");
            fclose(archivo);
        return;
        }


        fprintf(archivo, "%s;%s;%d;%d;%d\n",
            torneo.nombre, torneo.deporte, torneo.anio,
            torneo.cantidadEquipos, torneo.activo);
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

    while (leertorneo(archivo, &torneo) == 1) {
        printf("\nNombre: %s\n", torneo.nombre);
        printf("Deporte: %s\n", torneo.deporte);
        printf("Anio: %d\n", torneo.anio);
        printf("Cantidad de equipos: %d\n",
               torneo.cantidadEquipos);
        if (torneo.activo == 1) {
            printf("Estado: Activo\n");
        } else {
            printf("Estado: Inactivo\n");
        }
        cantidad++;
    }
    if (cantidad == 0) {
        printf("No hay torneos cargados.\n");
    }
    fclose(archivo);
}
/* Muestra solamente los torneos activos. */
void listartorneosactivos(void) {
    Torneo torneo;
    FILE *archivo;
    int cantidad = 0;
    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("\nNo hay torneos cargados.\n");
    } else {
        printf("\n--- TORNEOS ACTIVOS ---\n");
        while (leertorneo(archivo, &torneo) == 1) {
            if (torneo.activo == 1) {
                printf("\nNombre: %s\n", torneo.nombre);
                printf("Deporte: %s\n", torneo.deporte);
                printf("Anio: %d\n", torneo.anio);
                printf("Cantidad de equipos: %d\n",
                       torneo.cantidadEquipos);
                cantidad++;
            }
        }
        if (cantidad == 0) {
            printf("No hay torneos activos.\n");
        }
        fclose(archivo);
    }
}
/* Separa los torneos en dos archivos segun su estado. */
void separartorneos(void) {
    Torneo torneo;
    FILE *origen;
    FILE *activos;
    FILE *inactivos;
    int cantidadActivos = 0;
    int cantidadInactivos = 0;

    origen = fopen("datos.txt", "r");

    if (origen == NULL) {
        printf("No se encuentra el archivo datos.txt.\n");
    } else {
        activos = fopen("torneos_activos.txt", "w");

        if (activos == NULL) {
            printf("Error al crear el archivo de activos.\n");
            fclose(origen);
        } else {
            inactivos = fopen("torneos_inactivos.txt", "w");

            if (inactivos == NULL) {
                printf("Error al crear el archivo de inactivos.\n");
                fclose(origen);
                fclose(activos);
            } else {
                while (leertorneo(origen, &torneo) == 1) {
                    if (torneo.activo == 1) {
                        escribirtorneo(activos, torneo);
                        cantidadActivos++;
                    } else if (torneo.activo == 0) {
                        escribirtorneo(inactivos, torneo);
                        cantidadInactivos++;
                    }
                }

                fclose(origen);
                fclose(activos);
                fclose(inactivos);

                printf("\nSeparacion realizada correctamente.\n");
                printf("Torneos activos: %d\n", cantidadActivos);
                printf("Torneos inactivos: %d\n", cantidadInactivos);
            }
        }
    }
}
/* Lee un registro y comprueba si se leyeron los cinco campos. */
int leertorneo(FILE *archivo, Torneo *torneo) {
    return fscanf(archivo, " %49[^;];%29[^;];%d;%d;%d",
                  torneo->nombre,
                  torneo->deporte,
                  &torneo->anio,
                  &torneo->cantidadEquipos,
                  &torneo->activo) == 5;
}
/* Escribe un torneo en el archivo de texto. */
void escribirtorneo(FILE *archivo, Torneo torneo) {
    fprintf(archivo, "%s;%s;%d;%d;%d\n",
            torneo.nombre,
            torneo.deporte,
            torneo.anio,
            torneo.cantidadEquipos,
            torneo.activo);
}

/* Limpia los caracteres pendientes de la entrada. */
void limpiarbuffer(void) {
    int caracter;

    while ((caracter = getchar()) != '\n' && caracter != EOF) {
    }
}