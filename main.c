#include <stdio.h>
#include "torneo.h"
#include "utils.h"
void mostrarmenu(void);
int main() {
    int opcion;
    do {
        mostrarmenu();
        printf("seleccione una opcion: ");
        opcion = leerentero();
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
                printf("saliendo.\n");
                break;
            default:
                printf("opcion incorrecta, intente de nuevo.\n");
        }
    } while (opcion != 5);
    return 0;
}
void mostrarmenu(void) {
    printf("\n===== TORNEOS DEPORTIVOS =====\n");
    printf("1. agregar torneo\n");
    printf("2. listar torneos\n");
    printf("3. listar torneos activos\n");
    printf("4. separar torneos (activos / inactivos)\n");
    printf("5. salir\n");
}
