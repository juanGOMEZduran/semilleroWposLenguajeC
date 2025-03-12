#ifndef ANULACION_TRANFERENCIA_H
#define ANULACION_TRANFERENCIA_H

void anulacion(char id[]);  // Cambié char id[3] por char id[]
int validad_id_buscando(const char *id);
int validar_utimos_digitos_pan(const char *utimos_digitos_pan);
int validar_digitos_cvv(const char *digitos_cvv, const char *franquicia);
int cantidad_de_linea_anulacion(const char *archivo_path);

#endif