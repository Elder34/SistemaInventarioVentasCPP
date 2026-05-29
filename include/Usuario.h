#pragma once

#include <string>

using namespace std;

class Usuario {

public:

    int id;
    string nombre;
    string usuario;
    string password;
    string rol;

    Usuario() {
        id = 0;
        nombre = "";
        usuario = "";
        password = "";
        rol = "";
    }

    Usuario(
        int id,
        string nombre,
        string usuario,
        string password,
        string rol
    ) {
        this->id = id;
        this->nombre = nombre;
        this->usuario = usuario;
        this->password = password;
        this->rol = rol;
    }
};