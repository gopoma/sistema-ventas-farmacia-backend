#ifndef SISTEMA_VENTAS_FARMACIA_MEDICAMENTOS_H
#define SISTEMA_VENTAS_FARMACIA_MEDICAMENTOS_H

#include "../Definitions.h"

void inicializarMedicamentos();
void agregarMedicamento(Medicamento& nuevoMedicamento);
vector<Medicamento> obtenerMedicamentos();
Medicamento obtenerMedicamentoPorId(unsigned long long id);
void guardarMedicamentos();

#endif
