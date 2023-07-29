#ifndef SISTEMA_VENTAS_FARMACIA_DEFINITIONS_H
#define SISTEMA_VENTAS_FARMACIA_DEFINITIONS_H



#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)



typedef struct Cliente {
    unsigned long long id;
    char nombre[255];
    char dni[9]; // 71136033\0
    char telefono[10]; // 999508648\0
} Cliente;


typedef struct Medicamento {
    unsigned long long id;
    char nombre[255];
    unsigned int precio; // en céntimos
    unsigned int cantidad;
} Medicamento;


typedef struct VentaDetalle {
    unsigned long long venta;
    unsigned long long medicamento;
    unsigned int cantidad;
    unsigned int precio; // en céntimos
} VentaDetalle;


typedef struct VentaCabecera {
  unsigned long long id;
  unsigned long long cliente;
  vector<VentaDetalle> medicamentos;
  unsigned int total;
} VentaCabecera;



unsigned long long idClienteDisponible;
vector<Cliente> clientes;
unsigned long long idMedicamentoDisponible;
vector<Medicamento> medicamentos;

const string RCliente = "Cliente";
const string RMedicamento = "Medicamento";
unordered_map<string, string> STORAGE_PATH = {
    {RCliente, "./database/clientes.dat"},
    {RMedicamento, "./database/medicamentos.dat"}
};



void verificarOInicializarArchivo(const string& where) {
    ifstream archivoEntrada(STORAGE_PATH[where], ios::binary | ios::in);

    if(archivoEntrada.fail()) {
        ofstream archivoSalida(STORAGE_PATH[where], ios::binary | ios::out);

        unsigned long long inicializador = 1LL;
        archivoSalida.write(reinterpret_cast<char*>(&inicializador), sizeof(unsigned long long));

        archivoSalida.close();
    }

    archivoEntrada.close();
}

#endif
