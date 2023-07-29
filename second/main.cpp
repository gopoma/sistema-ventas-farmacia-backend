#include "./services/Clientes.h"
#include "./services/Clientes.cpp"
#include "./services/Medicamentos.h"
#include "./services/Medicamentos.cpp"

void inicializar();
void mostrarMenu();
void guardar();

int main() {
    inicializar();

    bool seguir = true;
    do {
        mostrarMenu();

        unsigned int opcion;
        cin >> opcion;
        cout << "\n";

        switch (opcion) {
            case 1: {
                agregarCliente();
                break;
            }
            case 2: {
                mostrarClientes();
                break;
            }
            case 3: {
                agregarMedicamento();
                break;
            }
            case 4: {
                mostrarMedicamentos();
                break;
            }
            case 5: {
                cout << "VerDetalleDeMedicamento()\n";
                break;
            }
            case 6: {
                cout << "verDetalleDeVenta()\n";
                break;
            }
            case 7: {
                seguir = false;
                break;
            }
            default: {
                printf("Opcion Invalida!\n");
                break;
            }
        }
    } while(seguir);

    guardar();
    printf("Gracias por utilizar el sistema de farmacia.\n");

    return 0;
}

void inicializar() {
    inicializarClientes();
    inicializarMedicamentos();
}

void mostrarMenu() {
    int anchoTotal = 40;
    int anchoTextoCentrado = 34;
    int anchoOpciones = 30;

    cout << "+---------------------------------------+" << endl;
    cout << "|" << setw(anchoTotal - 1) << "" << "|" << endl;
    cout << "|" << "        Bienvenido a la Farmacia       "  << "|" << endl;
    cout << "|" << setw(anchoTotal - 1) << "" << "|" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "| 1. Agregar Cliente     " << setw(anchoOpciones - 14) << right << "|" << endl;
    cout << "| 2. Mostrar Clientes    " << setw(anchoOpciones - 14) << right << "|" << endl;
    cout << "| 3. Agregar Medicamento " << setw(anchoOpciones - 14) << right << "|" << endl;
    cout << "| 4. Ver Medicamentos" << setw(anchoOpciones - 10) << right << "|" << endl;
    cout << "| 5. Buscar un medicamento" << setw(anchoOpciones - 15) << right << "|" << endl;
    cout << "| 6. Ver detalles de venta" << setw(anchoOpciones - 15) << right << "|" << endl;
    cout << "| 7. Salir" << setw(anchoOpciones + 1) << right << "|" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "Ingrese una opcion: ";
}

void guardar() {
    guardarClientes();
    guardarMedicamentos();
}
