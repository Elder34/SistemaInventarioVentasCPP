#pragma once

#include <string>
using namespace std;

class Cliente {
private:
    int id;
    string nombre;
    string telefono;
    string correo;
    string nit;

public:
    Cliente();
    Cliente(int id, string nombre, string telefono, string correo, string nit);

    int getId();
    string getNombre();
    string getTelefono();
    string getCorreo();
    string getNit();

    void setId(int id);
    void setNombre(string nombre);
    void setTelefono(string telefono);
    void setCorreo(string correo);
    void setNit(string nit);
};