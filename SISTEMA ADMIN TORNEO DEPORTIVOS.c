#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void buscartorneo(void);
void leertexto(const char *mensaje, char destino[], int tam);
int leerenterorango(const char *mensaje, int minimo, int maximo);
int leertorneo(FILE *archivo,Torneo *torneo);
void escribirtorneo(FILE *archivo, Torneo torneo);
void limpiarbuffer(void);

int main() {
    int opcion;
    int leido;
    //menu + switch con lo elegido
    do {
        mostrarmenu();
        printf("seleccione una opcion: ");
        leido = scanf("%d", &opcion);
        if (leido == EOF) {
            printf("\n Saliendo del sistema.\n");
            opcion = 6;
        } else if (leido == 1) {
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
                    buscartorneo();
                    break;
                case 6:
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
    }while (opcion!=6);

    return 0;
}
//muestra las opciones del menu disponibles
void mostrarmenu(void) {
    printf("\n-- SISTEMA DE TORNEOS DEPORTIVOS --\n");
    printf("1. Agregar un torneo\n");
    printf("2. Listar todos los torneos\n");
    printf("3. Listar torneos activos\n");
    printf("4. Separar torneos en dos archivos\n");
    printf("5. Buscar un torneo por nombre\n");
    printf("6. Salir\n");
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

    leertexto("Ingrese el nombre del torneo: ", torneo.nombre, 50);
    leertexto("Ingrese el deporte: ", torneo.deporte, 30);
    torneo.anio = leerenterorango("Ingrese el anio (1900-2100): ", 1900, 2100);
    torneo.cantidadEquipos = leerenterorango("Ingrese la cantidad de equipos (2-1000): ", 2, 1000);
    torneo.activo = leerenterorango("El torneo esta activo? (1=si 0=no): ", 0, 1);

    escribirtorneo(archivo, torneo);
    fclose(archivo);
    printf("Torneo guardado correctamente.\n");
}
/* Pide un texto (puede tener espacios). Repite hasta que no este vacio
 * y no contenga ';' (es el separador del archivo). tam es el tamanio del arreglo. */
void leertexto(const char *mensaje, char destino[], int tam) {
    int valido = 0;
    int largo;

    while (!valido) {
        printf("%s", mensaje);
        if (fgets(destino, tam, stdin) == NULL) {
            printf("\nSe cerro la entrada. Saliendo del sistema.\n");
            exit(0);
        }
        largo = (int)strlen(destino);
        if (largo > 0 && destino[largo - 1] == '\n') {
            destino[largo - 1] = '\0';
        } else {
            limpiarbuffer(); /* se escribio mas de lo que entra */
        }
        if (destino[0] == '\0') {
            printf("Error: no puede estar vacio.\n");
        } else if (strchr(destino, ';') != NULL) {
            printf("Error: no puede contener ';'.\n");
        } else {
            valido = 1;
        }
    }
}
/* Pide un entero entre minimo y maximo (inclusive). Repite hasta que sea valido. */
int leerenterorango(const char *mensaje, int minimo, int maximo) {
    int valor = 0;
    int valido = 0;
    int resultado;

    while (!valido) {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);
        if (resultado == EOF) {
            printf("\nSe cerro la entrada. Saliendo del sistema.\n");
            exit(0);
        } else if (resultado != 1) {
            printf("Error: ingrese un numero.\n");
            limpiarbuffer();
        } else {
            limpiarbuffer();
            if (valor < minimo || valor > maximo) {
                printf("Error: el valor debe estar entre %d y %d.\n", minimo, maximo);
            } else {
                valido = 1;
            }
        }
    }
    return valor;
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
/* Busca en datos.txt los torneos cuyo nombre coincide con el ingresado
 * y los muestra. Informa si no encontro ninguno. */
void buscartorneo(void) {
    Torneo torneo;
    FILE *archivo;
    char buscado[50];
    int cantidad = 0;

    archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("\nNo hay torneos cargados.\n");
        return;
    }

    leertexto("Ingrese el nombre del torneo a buscar: ", buscado, 50);

    while (leertorneo(archivo, &torneo) == 1) {
        if (strcmp(torneo.nombre, buscado) == 0) {
            printf("\nNombre: %s\n", torneo.nombre);
            printf("Deporte: %s\n", torneo.deporte);
            printf("Anio: %d\n", torneo.anio);
            printf("Cantidad de equipos: %d\n", torneo.cantidadEquipos);
            if (torneo.activo == 1) {
                printf("Estado: Activo\n");
            } else {
                printf("Estado: Inactivo\n");
            }
            cantidad++;
        }
    }
    if (cantidad == 0) {
        printf("No se encontro ningun torneo llamado %s.\n", buscado);
    } else {
        printf("\nTorneos encontrados: %d\n", cantidad);
    }
    fclose(archivo);
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
}//
