#include <stdio.h>

void guardar_archivo(int h, char* pan,char* franquisia,  float precio, char* cvv, char* fecha_expiracion, short estado) {
    FILE *archivo = fopen("archivos/transferenciad.dat", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    const char* tipo_transaccion = (estado == 1) ? "COMPRA" : (estado == 2) ? "COMPRA_NULA" : "";

    fprintf(archivo, "| %d | %s | %s | %.2f | %s | %s | %s |\n", h, pan, franquisia, precio, cvv, fecha_expiracion, tipo_transaccion);
    fclose(archivo);

    printf("Transacción guardada en transferenciad.dat\n");
}
