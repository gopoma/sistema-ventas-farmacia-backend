#include "Medicamentos.h"

void inicializarMedicamentos() {
    verificarOInicializarArchivo(RMedicamento);

    ifstream medicamentosEntrada(STORAGE_PATH[RMedicamento], ios::binary | ios::in);

    medicamentosEntrada.read(reinterpret_cast<char*>(&idMedicamentoDisponible), sizeof(unsigned long long));

    Medicamento m;
    while(medicamentosEntrada.read(reinterpret_cast<char*>(&m), sizeof(Medicamento))) {
        medicamentos.push_back(m);
    }

    for(Medicamento& m: medicamentos) {
        medicamentosIndexadosPorId[m.id] = m;
    }

    medicamentosEntrada.close();
}

void agregarMedicamento(Medicamento& nuevoMedicamento) {
    nuevoMedicamento.id = idMedicamentoDisponible++;

    medicamentos.push_back(nuevoMedicamento);

    medicamentosIndexadosPorId[nuevoMedicamento.id] = nuevoMedicamento;
}

vector<Medicamento> obtenerMedicamentos() {
    return medicamentos;
}

Medicamento obtenerMedicamentoPorId(unsigned long long id) {
    return medicamentosIndexadosPorId[id];
}

void guardarMedicamentos() {
    ofstream medicamentosSalida(STORAGE_PATH[RMedicamento], ios::binary | ios::out);

    medicamentosSalida.write(reinterpret_cast<char*>(&idMedicamentoDisponible), sizeof(unsigned long long));
    for(Medicamento m: medicamentos) {
        medicamentosSalida.write(reinterpret_cast<char*>(&m), sizeof(Medicamento));
    }

    medicamentosSalida.close();
}
