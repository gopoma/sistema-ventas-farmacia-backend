#ifndef SISTEMA_VENTAS_FARMACIA_CLIENTES_H
#define SISTEMA_VENTAS_FARMACIA_CLIENTES_H

#include "../Definitions.h"

ostream& operator<<(ostream& os, const Cliente& cli);
void inicializarClientes();
void agregarCliente();
void mostrarClientes();
void guardarClientes();

#endif
