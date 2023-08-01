#include "Medicamentos.h"

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

void agregarMedicamento(Medicamento& nuevoMedicamento) {
    nuevoMedicamento.id = idMedicamentoDisponible++;

    medicamentos.push_back(nuevoMedicamento);
}

vector<Medicamento> obtenerMedicamentos() {
    return medicamentos;
}

void guardarMedicamentos() {
    ofstream medicamentosSalida(STORAGE_PATH[RMedicamento], ios::binary | ios::out);

    medicamentosSalida.write(reinterpret_cast<char*>(&idMedicamentoDisponible), sizeof(unsigned long long));
    for(Medicamento m: medicamentos) {
        medicamentosSalida.write(reinterpret_cast<char*>(&m), sizeof(Medicamento));
    }

    medicamentosSalida.close();
}
