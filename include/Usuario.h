//Permite almacenar la información necesaria para el acceso y control de permisos.

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
    
    //Inicializa el objeto usuario con valores vacíos o por defecto.
    Usuario() {
        id = 0;
        nombre = "";
        usuario = "";
        password = "";
        rol = "";
    }
};