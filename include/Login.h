#pragma once
#include <string>
using namespace std;

class Login {
public:
    bool validarUsuario(string usuario, string password);
    string obtenerRolUsuario(string usuario);
};