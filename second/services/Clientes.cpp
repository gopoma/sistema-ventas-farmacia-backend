#include "Clientes.h"

ostream& operator<<(ostream& os, const Cliente& cli) {
    os << "Codigo:\t\t" << cli.id       << "\n";
    os << "Nombre:\t\t" << cli.nombre   << "\n";
    os << "DNI:\t\t"    << cli.dni      << "\n";
    os << "Telefono:\t" << cli.telefono << "\n";

    return os;
}

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

void agregarCliente() {
    Cliente nuevoCliente;



    string nombre; printf("Nombre: ");
    cin.ignore(); getline(cin, nombre); strcpy(nuevoCliente.nombre, nombre.c_str());

    // TODO: Agregar Validaciones [DNI] - unique - maxLength[8]
    printf("DNI: "); cin >> nuevoCliente.dni;
    // TODO: Agregar Validaciones [Telefono] - maxLength[9]
    printf("Telefono: "); cin >> nuevoCliente.telefono;



    nuevoCliente.id = idClienteDisponible++;
    clientes.push_back(nuevoCliente);
}

void mostrarClientes() {
    printf("Clientes:\n");
    for(size_t i = 0; i < clientes.size(); i++) {
        cout << "Cliente #" << (i+1) << ":\n";
        cout << clientes[i] << "\n";
    }
}

void guardarClientes() {
    ofstream clientesSalida(STORAGE_PATH[RCliente], ios::binary | ios::out);

    clientesSalida.write(reinterpret_cast<char*>(&idClienteDisponible), sizeof(unsigned long long));
    for(Cliente c: clientes) {
        clientesSalida.write(reinterpret_cast<char*>(&c), sizeof(Cliente));
    }

    clientesSalida.close();
}
