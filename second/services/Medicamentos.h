#ifndef SISTEMA_VENTAS_FARMACIA_MEDICAMENTOS_H
#define SISTEMA_VENTAS_FARMACIA_MEDICAMENTOS_H

#include "../Definitions.h"

ostream& operator<<(ostream& os, const Medicamento& m);
void inicializarMedicamentos();
void agregarMedicamento();
void mostrarMedicamentos();
void guardarMedicamentos();

#endif
