#include "Ventas.h"

void inicializarVentas() {
    verificarOInicializarArchivo(RVenta);

    ifstream ventasEntrada(STORAGE_PATH[RVenta], ios::binary | ios::in);

    ventasEntrada.read(reinterpret_cast<char*>(&idVentaDisponible), sizeof(unsigned long long));

    unsigned long long id;
    while(ventasEntrada.read(reinterpret_cast<char*>(&id), sizeof(unsigned long long))) {
        VentaCabecera v;
        v.id = id;

        unsigned long long idCliente;
        ventasEntrada.read(reinterpret_cast<char*>(&idCliente), sizeof(unsigned long long));
        v.cliente = clientesIndexadosPorId[idCliente];

        int cantidadMedicamentos;
        ventasEntrada.read(reinterpret_cast<char*>(&cantidadMedicamentos), sizeof(int));

        for(int i = 0; i < cantidadMedicamentos; i++) {
            VentaDetalle d;
            unsigned long long idMedicamento;
            ventasEntrada.read(reinterpret_cast<char*>(&idMedicamento), sizeof(unsigned long long));
            d.medicamento = medicamentosIndexadosPorId[idMedicamento];

            unsigned int cantidad;
            ventasEntrada.read(reinterpret_cast<char*>(&cantidad), sizeof(unsigned int));
            d.cantidad = cantidad;

            unsigned int precio;
            ventasEntrada.read(reinterpret_cast<char*>(&precio), sizeof(unsigned int));
            d.precio = precio;

            v.medicamentos.push_back(d);
        }

        unsigned int total;
        ventasEntrada.read(reinterpret_cast<char*>(&total), sizeof(unsigned int));
        v.total = total;

        ventas.push_back(v);
    }

    ventasEntrada.close();
}

vector<VentaCabecera> obtenerVentas() {
    return ventas;
}

void agregarMedicamentoAlCarrito(VentaDetalle d) {
    carrito.push_back(d);
}

void agregarVenta(VentaCabecera nuevaVenta) {
    nuevaVenta.id = idVentaDisponible++;

    unsigned int total = 0;
    for(VentaDetalle& d: carrito) {
        nuevaVenta.medicamentos.push_back(d);
        total += d.precio;
    }

    nuevaVenta.total = total;

    ventas.push_back(nuevaVenta);
}

void guardarVentas() {
    ofstream ventasSalida(STORAGE_PATH[RVenta], ios::binary | ios::out);

    ventasSalida.write(reinterpret_cast<char*>(&idVentaDisponible), sizeof(unsigned long long));
    for(VentaCabecera v: ventas) {
        unsigned long long id = v.id;
        ventasSalida.write(reinterpret_cast<char*>(&id), sizeof(unsigned long long));

        unsigned long long idCliente = v.cliente.id;
        ventasSalida.write(reinterpret_cast<char*>(&idCliente), sizeof(unsigned long long));

        int cantidadMedicamentos = v.medicamentos.size();
        ventasSalida.write(reinterpret_cast<char*>(&cantidadMedicamentos), sizeof(int));

        for(VentaDetalle& d: v.medicamentos) {
            unsigned long long idMedicamento = d.medicamento.id;
            ventasSalida.write(reinterpret_cast<char*>(&idMedicamento), sizeof(unsigned long long));

            unsigned int cantidad = d.cantidad;
            ventasSalida.write(reinterpret_cast<char*>(&cantidad), sizeof(unsigned int));

            unsigned int precio = d.precio;
            ventasSalida.write(reinterpret_cast<char*>(&precio), sizeof(unsigned int));
        }

        unsigned int total = v.total;
        ventasSalida.write(reinterpret_cast<char*>(&total), sizeof(unsigned int));
    }

    ventasSalida.close();
}
