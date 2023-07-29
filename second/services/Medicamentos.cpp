#include "Medicamentos.h"

ostream& operator<<(ostream& os, const Medicamento& m) {
    os << "Codigo:\t\t"     << m.id         << "\n";
    os << "Nombre:\t\t"     << m.nombre     << "\n";
    os << "Precio:\t\t"     << m.precio     << "\n";
    os << "Cantidad:\t"   << m.cantidad   << "\n";

    return os;
}

void inicializarMedicamentos() {
    verificarOInicializarArchivo(RMedicamento);

    ifstream medicamentosEntrada(STORAGE_PATH[RMedicamento], ios::binary | ios::in);

    medicamentosEntrada.read(reinterpret_cast<char*>(&idMedicamentoDisponible), sizeof(unsigned long long));

    Medicamento m;
    while(medicamentosEntrada.read(reinterpret_cast<char*>(&m), sizeof(Medicamento))) {
        medicamentos.push_back(m);
    }

    medicamentosEntrada.close();
}

void agregarMedicamento() {
    Medicamento nuevoMedicamento;



    string nombre; printf("Nombre: ");
    cin.ignore(); getline(cin, nombre); strcpy(nuevoMedicamento.nombre, nombre.c_str());

    printf("Precio (En Centimos de S/.): ");
    cin >> nuevoMedicamento.precio;
    printf("Cantidad: ");
    cin >> nuevoMedicamento.cantidad;



    nuevoMedicamento.id = idMedicamentoDisponible++;
    medicamentos.push_back(nuevoMedicamento);
}

void mostrarMedicamentos() {
    printf("Medicamentos:\n");
    for(size_t i = 0; i < medicamentos.size(); i++) {
        cout << "Medicamento #" << (i+1) << ":\n";
        cout << medicamentos[i] << "\n";
    }
}

void guardarMedicamentos() {
    ofstream medicamentosSalida(STORAGE_PATH[RMedicamento], ios::binary | ios::out);

    medicamentosSalida.write(reinterpret_cast<char*>(&idMedicamentoDisponible), sizeof(unsigned long long));
    for(Medicamento m: medicamentos) {
        medicamentosSalida.write(reinterpret_cast<char*>(&m), sizeof(Medicamento));
    }

    medicamentosSalida.close();
}
