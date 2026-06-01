#pragma once

#include <string>
using namespace std;

class Login {
private:
    string rolUsuario;

public:
    bool validarUsuario(string usuario, string password);
    string getRolUsuario();
};