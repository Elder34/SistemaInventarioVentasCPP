#include "Cliente.h"

Cliente::Cliente() {
    id = 0;
    nombre = "";
    telefono = "";
    correo = "";
    nit = "";
}

Cliente::Cliente(int id, string nombre, string telefono, string correo, string nit) {
    this->id = id;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
    this->nit = nit;
}

int Cliente::getId() { return id; }
string Cliente::getNombre() { return nombre; }
string Cliente::getTelefono() { return telefono; }
string Cliente::getCorreo() { return correo; }
string Cliente::getNit() { return nit; }

void Cliente::setId(int id) { this->id = id; }
void Cliente::setNombre(string nombre) { this->nombre = nombre; }
void Cliente::setTelefono(string telefono) { this->telefono = telefono; }
void Cliente::setCorreo(string correo) { this->correo = correo; }
void Cliente::setNit(string nit) { this->nit = nit; }