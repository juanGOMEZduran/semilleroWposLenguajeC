#ifndef TRANSACION_COMPRA_H
#define TRANSACION_COMPRA_H

int validar_pan(const char *pan);
char *mirar_franquisia(const char *pan);
int validar_fecha_exp(const char *fecha_expiracion);
int validar_cvv(const char *cvv, const char *franquisia);
void hacer_compra(float precio);
int cantidad_de_lineas_archivo();

#endif