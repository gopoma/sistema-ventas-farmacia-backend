#ifndef SISTEMA_VENTAS_FARMACIA_VENTAS_H
#define SISTEMA_VENTAS_FARMACIA_VENTAS_H

#include "../Definitions.h"

void inicializarVentas();
vector<VentaCabecera> obtenerVentas();
void agregarMedicamentoAlCarrito(VentaDetalle d);
void agregarVenta(Venta nuevaVenta);
void guardarVentas();

#endif
