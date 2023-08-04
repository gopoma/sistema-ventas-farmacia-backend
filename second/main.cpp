#include "./services/Clientes.h"
#include "./services/Clientes.cpp"
#include "./services/Medicamentos.h"
#include "./services/Medicamentos.cpp"

ostream &operator<<(ostream &os, const Cliente &cli);
ostream &operator<<(ostream &os, const Medicamento &m);
void inicializar();
void mostrarMenu();
void guardar();

int main()
{
    inicializar();

    bool seguir = true;
    do
    {
        mostrarMenu();

        unsigned int opcion;
        cin >> opcion;
        cout << "\n";

        // 1. Mostrar Clientes
        // 2. Agregar Cliente
        // 3. Buscar Cliente por id
        // 4. Buscar Cliente por dni
        // 5. Ver Medicamentos
        // 6. Agregar Medicamento
        // 7. Buscar Medicamento por id
        // 8. Ver detalles de venta
        // 9. Salir

        switch (opcion)
        {
        case 1:
        {
            vector<Cliente> clientes = obtenerClientes();

            printf("Clientes:\n");
            for (size_t i = 0; i < clientes.size(); i++)
            {
                cout << "Cliente #" << (i + 1) << ":\n";
                cout << clientes[i] << "\n";
            }
            break;
        }
        case 2:
        {
            Cliente nuevoCliente;

            string nombre;
            printf("Nombre: ");
            cin.ignore();
            getline(cin, nombre);
            strcpy(nuevoCliente.nombre, nombre.c_str());

            // TODO: Agregar Validaciones [DNI] - unique - maxLength[8]
            printf("DNI: ");
            cin >> nuevoCliente.dni;
            // TODO: Agregar Validaciones [Telefono] - maxLength[9]
            printf("Telefono: ");
            cin >> nuevoCliente.telefono;

            agregarCliente(nuevoCliente);
            break;
        }
        case 3:
        {
            unsigned long long id;
            printf("id: ");
            cin >> id;

            Cliente cliente = obtenerClientePorId(id);
            if (cliente.id != 0)
                cout << cliente << "\n";
            else
                cout << "Not Found!\n";

            break;
        }
        case 4:
        {
            string dni;
            printf("dni: ");
            cin >> dni;

            Cliente cliente = obtenerClientePorDNI(dni);
            if (cliente.id != 0)
                cout << cliente << "\n";
            else
                cout << "Not Found!\n";
            break;
        }
        case 5:
        {
            vector<Medicamento> medicamentos = obtenerMedicamentos();

            printf("Medicamentos:\n");
            for (size_t i = 0; i < medicamentos.size(); i++)
            {
                cout << "Medicamento #" << (i + 1) << ":\n";
                cout << medicamentos[i] << "\n";
            }
            break;
        }
        case 6:
        {
            Medicamento nuevoMedicamento;

            string nombre;
            printf("Nombre: ");
            cin.ignore();
            getline(cin, nombre);
            strcpy(nuevoMedicamento.nombre, nombre.c_str());

            printf("Precio (En Centimos de S/.): ");
            cin >> nuevoMedicamento.precio;
            printf("Cantidad: ");
            cin >> nuevoMedicamento.cantidad;

            agregarMedicamento(nuevoMedicamento);
            break;
        }
        case 7:
        {
            unsigned long long id;
            printf("id: ");
            cin >> id;

            Medicamento medicamento = obtenerMedicamentoPorId(id);
            if (medicamento.id != 0)
                cout << medicamento << "\n";
            else
                cout << "Not Found!\n";
            break;
        }
        case 9:
        {
            seguir = false;
            break;
        }
        default:
        {
            printf("Opcion Invalida!\n");
            break;
        }
        }
    } while (seguir);

    guardar();
    printf("Gracias por utilizar el sistema de farmacia.\n");

    return 0;
}

ostream &operator<<(ostream &os, const Cliente &cli)
{
    os << "Codigo:\t\t" << cli.id << "\n";
    os << "Nombre:\t\t" << cli.nombre << "\n";
    os << "DNI:\t\t" << cli.dni << "\n";
    os << "Telefono:\t" << cli.telefono << "\n";

    return os;
}

ostream &operator<<(ostream &os, const Medicamento &m)
{
    os << "Codigo:\t\t" << m.id << "\n";
    os << "Nombre:\t\t" << m.nombre << "\n";
    os << "Precio:\t\t" << m.precio << "\n";
    os << "Cantidad:\t" << m.cantidad << "\n";

    return os;
}

void inicializar()
{
    inicializarClientes();
    inicializarMedicamentos();
}

void mostrarMenu()
{
    int anchoTotal = 40;
    int anchoTextoCentrado = 34;
    int anchoOpciones = 30;

    cout << "+---------------------------------------+" << endl;
    cout << "|" << setw(anchoTotal - 1) << ""
         << "|" << endl;
    cout << "|"
         << "        Bienvenido a la Farmacia       "
         << "|" << endl;
    cout << "|" << setw(anchoTotal - 1) << ""
         << "|" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "| 1. Mostrar Clientes    " << setw(anchoOpciones - 14) << right << "|" << endl;
    cout << "| 2. Agregar Cliente     " << setw(anchoOpciones - 14) << right << "|" << endl;
    cout << "| 3. Buscar Cliente por id" << setw(anchoOpciones - 15) << right << "|" << endl;
    cout << "| 4. Buscar Cliente por dni" << setw(anchoOpciones - 16) << right << "|" << endl;
    cout << "| 5. Ver Medicamentos" << setw(anchoOpciones - 10) << right << "|" << endl;
    cout << "| 6. Agregar Medicamento " << setw(anchoOpciones - 14) << right << "|" << endl;
    cout << "| 7. Buscar Medicamento por id" << setw(anchoOpciones - 19) << right << "|" << endl;
    cout << "| 8. Ver detalles de venta" << setw(anchoOpciones - 15) << right << "|" << endl;
    cout << "| 9. Salir" << setw(anchoOpciones + 1) << right << "|" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "Ingrese una opcion: ";
}

void guardar()
{
    guardarClientes();
    guardarMedicamentos();
}
