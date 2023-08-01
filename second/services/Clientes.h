#ifndef SISTEMA_VENTAS_FARMACIA_CLIENTES_H
#define SISTEMA_VENTAS_FARMACIA_CLIENTES_H

#include "../Definitions.h"

void inicializarClientes();
void agregarCliente(Cliente& nuevoCliente);
vector<Cliente> obtenerClientes();
void guardarClientes();

#endif
