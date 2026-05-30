//Define cómo se crean, consultan y modifican los datos de los clientes dentro del sistema.
#include "Cliente.h"

//Inicializa el objeto cliente con valores vacíos o por defecto.
Cliente::Cliente() {
    id = 0;
    nombre = "";
    telefono = "";
    correo = "";
    nit = "";
}

//Permite crear un cliente con toda su información desde el inicio.
Cliente::Cliente(int id, string nombre, string telefono, string correo, string nit) {
    this->id = id;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
    this->nit = nit;
}

//Devuelven la información almacenada del cliente.
int Cliente::getId() { return id; }
string Cliente::getNombre() { return nombre; }
string Cliente::getTelefono() { return telefono; }
string Cliente::getCorreo() { return correo; }
string Cliente::getNit() { return nit; }

//Permiten modificar la información del cliente.
void Cliente::setId(int id) { this->id = id; }
void Cliente::setNombre(string nombre) { this->nombre = nombre; }
void Cliente::setTelefono(string telefono) { this->telefono = telefono; }
void Cliente::setCorreo(string correo) { this->correo = correo; }
void Cliente::setNit(string nit) { this->nit = nit; }