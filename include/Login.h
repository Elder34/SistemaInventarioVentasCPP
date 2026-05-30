//Administra el login 

#pragma once
#include <string>
using namespace std;

//Verificar credenciales y controlar el acceso de usuarios.
class Login {
public:

    //Método validarUsuario
    bool validarUsuario(string usuario, string password);
};