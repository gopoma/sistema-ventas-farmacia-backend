#include <bits/stdc++.h>
using namespace std;
#define ll long long

// medicamento
struct medicamento {
  string nombre;
  int precio;
  int cantidad;
};

// cliente
struct cliente {
  string nombre;
  string dni;
  int telefono;
};

// venta detalle
struct ventaDetalle {
  int id;
  medicamento medicamentoVenta;
  int cantidad;
  int precio;
};

// venta cabecera
struct ventaCabecera {
  int id;
  vector<ventaDetalle> detalle;
  cliente clienteVenta;
  int total;
};

// medicamentos
map<string, medicamento> medicamentos;
// clientes
map<string, cliente> clientes;
// lista de medicamentos
vector<string> listaMedicamentos;
// lista de ventas
map<int,ventaCabecera> ventas;
int totalVentas = 0;
int dineroTotalporVentas = 0;

void cargarMedicamentos() {
  ifstream archivoMedicamentos("medicamentos.bin", ios::binary);
  if (archivoMedicamentos) {
    medicamentos.clear(); // Limpiamos el mapa antes de cargar los datos

    int numMedicamentos;
    archivoMedicamentos.read((char*)&numMedicamentos, sizeof(numMedicamentos));

    for (int i = 0; i < numMedicamentos; i++) {
      int nombreSize;
      archivoMedicamentos.read((char*)&nombreSize, sizeof(nombreSize));

      char nombre[100];
      archivoMedicamentos.read(nombre, nombreSize);
      nombre[nombreSize] = '\0';

      int precio, cantidad;
      archivoMedicamentos.read((char*)&precio, sizeof(precio));
      archivoMedicamentos.read((char*)&cantidad, sizeof(cantidad));


      medicamento m;
      m.nombre = nombre;
      m.precio = precio;
      m.cantidad = cantidad;
      medicamentos[m.nombre] = m;
    }

    archivoMedicamentos.close();
  }
}


void guardarMedicamentos() {
  ofstream archivoMedicamentos("medicamentos.bin", ios::binary);
  if (archivoMedicamentos) {
    int numMedicamentos = medicamentos.size();
    archivoMedicamentos.write((char*)&numMedicamentos, sizeof(numMedicamentos));

    for (const auto& entry : medicamentos) {
      string nombre = entry.second.nombre;
      int precio = entry.second.precio;
      int cantidad = entry.second.cantidad;
      int nombreSize = nombre.size();

      archivoMedicamentos.write((char*)&nombreSize, sizeof(nombreSize));
      archivoMedicamentos.write(nombre.c_str(), nombreSize);

      archivoMedicamentos.write((char*)&precio, sizeof(precio));
      archivoMedicamentos.write((char*)&cantidad, sizeof(cantidad));
    }
    archivoMedicamentos.close();
  }
}

void guardarVentas() {
  ofstream archivoVentas("ventas.bin", ios::binary);
  if (archivoVentas) {
    int numVentas = ventas.size();
    archivoVentas.write((char*)&numVentas, sizeof(numVentas));

    for (const auto& entry : ventas) {
      ventaCabecera cabecera = entry.second;
      int numDetalles = cabecera.detalle.size();

      archivoVentas.write((char*)&cabecera.id, sizeof(cabecera.id));

      // Guardar datos del cliente
      string idCliente = cabecera.clienteVenta.dni; // Convertir el ID del cliente a string
      int idClienteSize = idCliente.size();
      archivoVentas.write((char*)&idClienteSize, sizeof(idClienteSize));
      archivoVentas.write(idCliente.c_str(), idClienteSize);

      archivoVentas.write((char*)&cabecera.total, sizeof(cabecera.total));
      archivoVentas.write((char*)&numDetalles, sizeof(numDetalles));

      for (const auto& detalle : cabecera.detalle) {
        // Guardar datos del medicamentoVenta (guardamos el nombre como cadena)
        string nombreMedicamento = detalle.medicamentoVenta.nombre;
        int nombreSize = nombreMedicamento.size();
        archivoVentas.write((char*)&nombreSize, sizeof(nombreSize));
        archivoVentas.write(nombreMedicamento.c_str(), nombreSize);

        // Almacenar cantidad y precio como enteros sin signo (unsigned int)
        unsigned int cantidad = detalle.cantidad;
        archivoVentas.write((char*)&cantidad, sizeof(cantidad));
        unsigned int precio = detalle.precio;
        archivoVentas.write((char*)&precio, sizeof(precio));
      }
    }
    archivoVentas.close();
  }
}

void cargarVentas() {
  ifstream archivoVentas("ventas.bin", ios::binary);
  if (archivoVentas) {
    ventas.clear(); // Limpiamos el mapa antes de cargar los datos

    int numVentas;
    archivoVentas.read((char*)&numVentas, sizeof(numVentas));

    for (int i = 0; i < numVentas; i++) {
      ventaCabecera cabecera;
      archivoVentas.read((char*)&cabecera.id, sizeof(cabecera.id));

      int dniSize;
      archivoVentas.read((char*)&dniSize, sizeof(dniSize));
      string dniCliente(dniSize, ' ');
      archivoVentas.read(&dniCliente[0], dniSize);
      cabecera.clienteVenta = clientes[dniCliente];

      archivoVentas.read((char*)&cabecera.total, sizeof(cabecera.total));

      int numDetalles;
      archivoVentas.read((char*)&numDetalles, sizeof(numDetalles));
      cabecera.detalle.resize(numDetalles);

      for (int j = 0; j < numDetalles; j++) {
        int nombreSize;
        archivoVentas.read((char*)&nombreSize, sizeof(nombreSize));
        string nombreMedicamento(nombreSize, ' ');
        archivoVentas.read(&nombreMedicamento[0], nombreSize);
        cabecera.detalle[j].medicamentoVenta = medicamentos[nombreMedicamento];

        archivoVentas.read((char*)&cabecera.detalle[j].cantidad, sizeof(cabecera.detalle[j].cantidad));
        archivoVentas.read((char*)&cabecera.detalle[j].precio, sizeof(cabecera.detalle[j].precio));
      }

      ventas[cabecera.id] = cabecera; // Usamos el ID de la venta como clave para el mapa
      totalVentas++; // Incrementamos el contador de ventas
      dineroTotalporVentas += cabecera.total; // Agregamos el total de la venta al dinero total por ventas
    }

    archivoVentas.close();
  }
}

// agregar medicamentos
void agregarMedicamentos() {
  medicamento m;
  cout << "Ingrese el nombre del medicamento: ";
  cin >> m.nombre;
  if(medicamentos[m.nombre].nombre != m.nombre){
    cout << "Ingrese el precio del medicamento: ";
    cin >> m.precio;
    cout << "Ingrese la cantidad del medicamento: ";
    cin >> m.cantidad;
    listaMedicamentos.push_back(m.nombre);
    medicamentos[m.nombre] = m;
  }else{
    cout << "Ingrese la cantidad del medicamento: ";
    cin >> m.cantidad;
    medicamentos[m.nombre].cantidad += m.cantidad;
  }
}

void generarListaMedicamentos() {
  listaMedicamentos.clear(); // Limpiar la lista antes de volver a generarla
  for (const auto& entry : medicamentos) {
    listaMedicamentos.push_back(entry.second.nombre);
  }
}


void VerDetalleDeMedicamento(){
  for(int i = 1; i <= listaMedicamentos.size(); i++){
    cout << i << ". " << listaMedicamentos[i-1] << endl;
  }
  int opcion; cin >> opcion;
  if(opcion > listaMedicamentos.size() || opcion < 1){
    cout << "Opcion invalida" << endl;
    return;
  }
  cout << "Nombre: "<< medicamentos[listaMedicamentos[opcion-1]].nombre << endl;
  cout << "Precio: "<< medicamentos[listaMedicamentos[opcion-1]].precio << endl;
  cout << "Stock: "<< medicamentos[listaMedicamentos[opcion-1]].cantidad << endl;
}

cliente datosCliente(){
  cliente c;
  cout << "Ingrese el DNI del cliente: ";
  cin >> c.dni;
  if(clientes[c.dni].dni != c.dni){
    cout << "Ingrese el nombre del cliente: ";
    cin >> c.nombre;
    cout << "Ingrese el telefono del cliente: ";
    cin >> c.telefono;
    clientes[c.dni] = c;
  }else{
    c = clientes[c.dni];
  }
  return c;
}

bool venderUnMedicamento(int &cantidad, int &indice) {
  cout << "Medicamentos" << endl;
  for (int i = 1; i <= listaMedicamentos.size(); i++) {
    cout << i << ". " << listaMedicamentos[i - 1] << endl;
  }
  cout << "Ingrese el número del medicamento a vender: ";
  int opcion;
  cin >> opcion;
  while (opcion > listaMedicamentos.size() || opcion < 1) {
    cout << "Opción inválida, por favor ingrese una opción válida: " << endl;
    cin >> opcion;
  }
  indice = opcion - 1;
  cout << "Nombre: " << medicamentos[listaMedicamentos[indice]].nombre << endl;
  cout << "Precio: " << medicamentos[listaMedicamentos[indice]].precio << endl;
  cout << "Stock: " << medicamentos[listaMedicamentos[indice]].cantidad << endl;
  cout << "Ingrese la cantidad a vender: ";
  cin >> cantidad;
  if (cantidad <= 0) {
    cout << "La cantidad debe ser un número positivo." << endl;
    return false;
  } else if (cantidad > medicamentos[listaMedicamentos[indice]].cantidad) {
    cout << "No hay suficiente stock disponible." << endl;
    return false;
  }
  medicamentos[listaMedicamentos[indice]].cantidad -= cantidad;
  return true;
}

void venderMedicamento() {
  if (listaMedicamentos.size() == 0) {
    cout << "No hay medicamentos registrados" << endl;
    return;
  }
  cout << "¿Desea usar un cliente registrado? (s/n): ";
  char op;
  cin >> op;
  cliente c;
  if (op == 's') {
    c = datosCliente();
  } else {
    // registrar cliente en blanco
    c.dni = "";
    c.nombre = "";
    c.telefono = 0;
  }

  int cantidad, indice;
  char seguir = 's';
  while (seguir == 's') {
    ventas[totalVentas].id = totalVentas;
    ventas[totalVentas].clienteVenta = c;
    ventas[totalVentas].total = 0;

    if (venderUnMedicamento(cantidad, indice)) {
      ventas[totalVentas].detalle.push_back({totalVentas, medicamentos[listaMedicamentos[indice]], cantidad, medicamentos[listaMedicamentos[indice]].precio});
      ventas[totalVentas].total += cantidad * medicamentos[listaMedicamentos[indice]].precio;
    }
    cout << "¿Desea seguir comprando? (s/n): ";
    cin >> seguir;

  }
  totalVentas++;
  cout << "Venta realizada" << endl;
}


void imprimirLinea(int nombreAncho, int precioAncho, int stockAncho) {
  cout << "+";
  cout << setfill('-') << setw(nombreAncho + 1) << "+";
  cout << setfill('-') << setw(precioAncho + 1) << "+";
  cout << setfill('-') << setw(stockAncho + 1) << "+";
  cout << setfill(' ') << endl; // Restaurar relleno de espacios en blanco
}

void mostrarMedicamentos() {
  cout << setfill(' '); // Establecer el relleno de espacios en blanco

  int nombreAncho = 20;
  int precioAncho = 9;
  int stockAncho = 9;

  imprimirLinea(nombreAncho, precioAncho, stockAncho);
  cout << "|" << setw(nombreAncho) << left << "Nombre";
  cout << "|" << setw(precioAncho) << right << "Precio";
  cout << "|" << setw(stockAncho) << right << "Stock";
  cout << "|" << endl;
  imprimirLinea(nombreAncho, precioAncho, stockAncho);

  for (auto i : listaMedicamentos) {
    cout << "|" << setw(nombreAncho) << left << medicamentos[i].nombre;
    cout << "|" << setw(precioAncho) << right << medicamentos[i].precio;
    cout << "|" << setw(stockAncho) << right << medicamentos[i].cantidad;
    cout << "|" << endl;
  }
  imprimirLinea(nombreAncho, precioAncho, stockAncho);
}

void Menu() {
  int anchoTotal = 40;
  int anchoTextoCentrado = 34;
  int anchoOpciones = 30;

  cout << "+---------------------------------------+" << endl;
  cout << "|" << setw(anchoTotal - 1) << "" << "|" << endl;
  cout << "|" << "        Bienvenido a la farmacia       "  << "|" << endl;
  cout << "|" << setw(anchoTotal - 1) << "" << "|" << endl;
  cout << "+---------------------------------------+" << endl;
  cout << "| 1. Vender" << setw(anchoOpciones) << right << "|" << endl;
  cout << "| 2. Agregar Medicamentos" << setw(anchoOpciones - 14) << right << "|" << endl;
  cout << "| 3. Ver Medicamentos" << setw(anchoOpciones - 10) << right << "|" << endl;
  cout << "| 4. Buscar un medicamento" << setw(anchoOpciones - 15) << right << "|" << endl;
  cout << "| 5. Ver detalles de venta" << setw(anchoOpciones - 15) << right << "|" << endl;
  cout << "| 6. Salir" << setw(anchoOpciones + 1) << right << "|" << endl;
  cout << "+---------------------------------------+" << endl;
  cout << "Ingrese una opción: ";
}

void verDetalleDeVenta() {
  // pedir el id de la venta
  if (totalVentas == 0) {
    cout << "No hay ventas registradas" << endl;
    return;
  }
  cout << "IDs de 1 a " << totalVentas << endl;
  cout << "Ingrese el ID de la venta: ";
  int id;
  cin >> id;
  id--;
  if (ventas.find(id) != ventas.end()) {
    // mostrar los detalles de la venta
    if (ventas[id].clienteVenta.nombre != "") {
      cout << "Cliente: " << ventas[id].clienteVenta.nombre << endl;
      cout << "DNI: " << ventas[id].clienteVenta.dni << endl;
      cout << "Telefono: " << ventas[id].clienteVenta.telefono << endl;
    }
    cout << "Total: " << ventas[id].total << endl;

    // Calcular anchos para las columnas
    int nombreAncho = 10;
    int cantidadAncho = 9;
    int precioAncho = 8;

    for (auto i : ventas[id].detalle) {
      int nombreSize = i.medicamentoVenta.nombre.size();
      int cantidadSize = to_string(i.cantidad).size();
      int precioSize = to_string(i.precio).size();

      if (nombreSize > nombreAncho) {
        nombreAncho = nombreSize;
      }
      if (cantidadSize > cantidadAncho) {
        cantidadAncho = cantidadSize;
      }
      if (precioSize > precioAncho) {
        precioAncho = precioSize;
      }
    }

    cout << "+";
    cout << setfill('-') << setw(nombreAncho + 3) << "+";
    cout << setfill('-') << setw(cantidadAncho + 3) << "+";
    cout << setfill('-') << setw(precioAncho + 3) << "+";
    cout << setfill(' ') << endl; // Restaurar relleno de espacios en blanco

    cout << "| " << setw(nombreAncho) << left << "Nombre";
    cout << " | " << setw(cantidadAncho) << right << "Cantidad";
    cout << " | " << setw(precioAncho) << right << "Precio";
    cout << " |" << endl;

    cout << "+";
    cout << setfill('-') << setw(nombreAncho + 3) << "+";
    cout << setfill('-') << setw(cantidadAncho + 3) << "+";
    cout << setfill('-') << setw(precioAncho + 3) << "+";
    cout << setfill(' ') << endl; // Restaurar relleno de espacios en blanco

    for (auto i : ventas[id].detalle) {
      cout << "| " << setw(nombreAncho) << left << i.medicamentoVenta.nombre;
      cout << " | " << setw(cantidadAncho) << right << i.cantidad;
      cout << " | " << setw(precioAncho) << right << i.precio << " |" << endl;
    }

    cout << "+";
    cout << setfill('-') << setw(nombreAncho + 3) << "+";
    cout << setfill('-') << setw(cantidadAncho + 3) << "+";
    cout << setfill('-') << setw(precioAncho + 3) << "+";
    cout << setfill(' ') << endl; // Restaurar relleno de espacios en blanco

    int totalAncho = nombreAncho + cantidadAncho + precioAncho + 4;
    cout << "| " << setw(totalAncho - 3) << left << "Total: " << setw(precioAncho - 3) << right << ventas[id].total << " |" << endl;

    cout << "+";
    cout << setfill('-') << setw(totalAncho + 5) << "+";
    cout << setfill(' ') << endl;

  } else {
    cout << "ID de venta no válido." << endl;
  }
  cout << endl;
}

void cargarClientes() {
  ifstream archivoClientes("clientes.bin", ios::binary);
  if (archivoClientes) {
    int numClientes;
    archivoClientes.read((char*)&numClientes, sizeof(numClientes));

    for (int i = 0; i < numClientes; i++) {
      int dniSize;
      archivoClientes.read((char*)&dniSize, sizeof(dniSize));
      string dniCliente(dniSize, ' ');
      archivoClientes.read(&dniCliente[0], dniSize);

      cliente c;
      c.dni = dniCliente;
      archivoClientes.read((char*)&c.telefono, sizeof(c.telefono));

      int nombreSize;
      archivoClientes.read((char*)&nombreSize, sizeof(nombreSize));
      c.nombre.resize(nombreSize, ' ');
      archivoClientes.read(&c.nombre[0], nombreSize);

      int correoSize;

      clientes[c.dni] = c;
    }

    archivoClientes.close();
  }
}

void guardarClientes() {
  ofstream archivoClientes("clientes.bin", ios::binary);
  if (archivoClientes) {
    int numClientes = clientes.size();
    archivoClientes.write((char*)&numClientes, sizeof(numClientes));

    for (const auto& entry : clientes) {
      const cliente& c = entry.second;

      int dniSize = c.dni.size();
      archivoClientes.write((char*)&dniSize, sizeof(dniSize));
      archivoClientes.write(c.dni.c_str(), dniSize);

      archivoClientes.write((char*)&c.telefono, sizeof(c.telefono));

      int nombreSize = c.nombre.size();
      archivoClientes.write((char*)&nombreSize, sizeof(nombreSize));
      archivoClientes.write(c.nombre.c_str(), nombreSize);

    }

    archivoClientes.close();
  }
}

int main() {
  cargarMedicamentos();
  cargarVentas();
  cargarClientes();
  generarListaMedicamentos();

  bool seguir = true;
  while (seguir) {
    Menu();
    int opcion;
    cin >> opcion;
    cout << endl;

    switch (opcion) {
      case 1:
        venderMedicamento();
        break;
      case 2:
        agregarMedicamentos();
        break;
      case 3:
        mostrarMedicamentos();
        break;
      case 4:
        VerDetalleDeMedicamento();
        break;
      case 5:
        verDetalleDeVenta();
        break;
      case 6:
        seguir = false;
        break;
      default:
        cout << "Opción inválida" << endl;
        break;
    }
  }

  guardarMedicamentos();
  guardarVentas();
  guardarClientes();
  cout << "Gracias por utilizar el sistema de farmacia." << endl;
  return 0;
}

