#ifndef SISTEMA_VENTAS_FARMACIA_MEDICAMENTOS_H
#define SISTEMA_VENTAS_FARMACIA_MEDICAMENTOS_H

#include "../Definitions.h"

void inicializarMedicamentos();
void agregarMedicamento(Medicamento& nuevoMedicamento);
vector<Medicamento> obtenerMedicamentos();
void guardarMedicamentos();

#endif
