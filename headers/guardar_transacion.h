#ifndef GUARDAR_TRANSACION_H
#define GUARDAR_TRANSACION_H

#include "transacion_compra.h"
#include "imprimir_transacion.h"

void guardar_archivo(int h,  char* pan, float precio, char* cvv,  char* fecha_expiracion, short estado);


#endif