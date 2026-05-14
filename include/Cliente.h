#pragma once
#include <string>

using namespace std;

class Cliente {
private:
    int id;
    string nombre;
    string telefono;
    string correo;

public:
    Cliente();
    Cliente(int id, string nombre, string telefono, string correo);

    int getId() const;
    string getNombre() const;
    string getTelefono() const;
    string getCorreo() const;

    void setNombre(string nombre);
    void setTelefono(string telefono);
    void setCorreo(string correo);
};