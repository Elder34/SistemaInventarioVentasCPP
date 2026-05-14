#include "Cliente.h"

Cliente::Cliente() {
    id = 0;
    nombre = "";
    telefono = "";
    correo = "";
}

Cliente::Cliente(int id, string nombre, string telefono, string correo) {
    this->id = id;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
}

int Cliente::getId() const { return id; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getCorreo() const { return correo; }

void Cliente::setNombre(string nombre) { this->nombre = nombre; }
void Cliente::setTelefono(string telefono) { this->telefono = telefono; }
void Cliente::setCorreo(string correo) { this->correo = correo; }