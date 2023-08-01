#include "Clientes.h"

void inicializarClientes() {
    verificarOInicializarArchivo(RCliente);

    ifstream clientesEntrada(STORAGE_PATH[RCliente], ios::binary | ios::in);

    clientesEntrada.read(reinterpret_cast<char*>(&idClienteDisponible), sizeof(unsigned long long));

    Cliente c;
    while(clientesEntrada.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
        clientes.push_back(c);
    }

    clientesEntrada.close();
}

void agregarCliente(Cliente& nuevoCliente) {
    nuevoCliente.id = idClienteDisponible++;

    clientes.push_back(nuevoCliente);
}

vector<Cliente> obtenerClientes() {
    return clientes;
}

void guardarClientes() {
    ofstream clientesSalida(STORAGE_PATH[RCliente], ios::binary | ios::out);

    clientesSalida.write(reinterpret_cast<char*>(&idClienteDisponible), sizeof(unsigned long long));
    for(Cliente c: clientes) {
        clientesSalida.write(reinterpret_cast<char*>(&c), sizeof(Cliente));
    }

    clientesSalida.close();
}
