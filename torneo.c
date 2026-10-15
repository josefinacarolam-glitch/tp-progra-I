#include <stdio.h>
#include "torneo.h"
#include "utils.h"

int leertorneo(const char *linea, Torneo *t) {
    return sscanf(linea, "%49[^;];%29[^;];%d;%d;%d",
                  t->nombre, t->deporte, &t->anio,
                  &t->cantidadequipos, &t->activo) == 5;
}

void mostrartorneo(const Torneo *t) {
    printf("Nombre: %s | Deporte: %s | Anio: %d | Equipos: %d | Activo: %s\n",
           t->nombre, t->deporte, t->anio, t->cantidadequipos,
           t->activo ? "si" : "no");
}

void agregartorneo(void) {
    Torneo torneo;
    FILE *archivo;

    archivo = fopen(ARCHIVO, "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("ingrese el nombre del torneo: ");
    leertexto(torneo.nombre, sizeof(torneo.nombre));
    printf("ingrese el deporte: ");
    leertexto(torneo.deporte, sizeof(torneo.deporte));
    printf("ingrese el anio: ");
    torneo.anio = leerentero();
    printf("ingrese la cantidad de equipos: ");
    torneo.cantidadequipos = leerentero();
    printf("el torneo esta activo?(1=si 0=no): ");
    torneo.activo = leerentero();

    fprintf(archivo, "%s;%s;%d;%d;%d\n", torneo.nombre, torneo.deporte,
            torneo.anio, torneo.cantidadequipos, torneo.activo);
    fclose(archivo);
    printf("torneo guardado correctamente.\n");
}

void listartorneos(void) {
    Torneo torneo;
    char linea[200];
    int cantidad = 0;
    FILE *archivo = fopen(ARCHIVO, "r");

    if (archivo == NULL) {
        printf("todavia no hay torneos cargados.\n");
        return;
    }
    printf("\n--- listado de torneos ---\n");
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (leertorneo(linea, &torneo)) {
            mostrartorneo(&torneo);
            cantidad++;
        }
    }
    fclose(archivo);
    if (cantidad == 0) {
        printf("no hay torneos para mostrar.\n");
    }
}

void listartorneosactivos(void) {
    Torneo torneo;
    char linea[200];
    int cantidad = 0;
    FILE *archivo = fopen(ARCHIVO, "r");

    if (archivo == NULL) {
        printf("todavia no hay torneos cargados.\n");
        return;
    }
    printf("\n--- torneos activos ---\n");
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (leertorneo(linea, &torneo) && torneo.activo == 1) {
            mostrartorneo(&torneo);
            cantidad++;
        }
    }
    fclose(archivo);
    if (cantidad == 0) {
        printf("no hay torneos activos.\n");
    }
}

void separartorneos(void) {
    Torneo torneo;
    char linea[200];
    int activos = 0, inactivos = 0;
    FILE *origen = fopen(ARCHIVO, "r");
    FILE *fact, *finact;

    if (origen == NULL) {
        printf("todavia no hay torneos cargados.\n");
        return;
    }
    fact = fopen(ARCHIVO_ACTIVOS, "w");
    finact = fopen(ARCHIVO_INACTIVOS, "w");
    if (fact == NULL || finact == NULL) {
        printf("Error al crear los archivos de salida.\n");
        if (fact != NULL) fclose(fact);
        if (finact != NULL) fclose(finact);
        fclose(origen);
        return;
    }

    while (fgets(linea, sizeof(linea), origen) != NULL) {
        if (!leertorneo(linea, &torneo)) {
            continue;
        }
        if (torneo.activo == 1) {
            fprintf(fact, "%s;%s;%d;%d;%d\n", torneo.nombre, torneo.deporte,
                    torneo.anio, torneo.cantidadequipos, torneo.activo);
            activos++;
        } else {
            fprintf(finact, "%s;%s;%d;%d;%d\n", torneo.nombre, torneo.deporte,
                    torneo.anio, torneo.cantidadequipos, torneo.activo);
            inactivos++;
        }
    }
    fclose(origen);
    fclose(fact);
    fclose(finact);
    printf("listo: %d activos (%s) y %d inactivos (%s).\n",
           activos, ARCHIVO_ACTIVOS, inactivos, ARCHIVO_INACTIVOS);
}
