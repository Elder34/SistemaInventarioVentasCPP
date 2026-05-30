#include "Login.h"

// Método encargado de validar el acceso al sistema
bool Login::validarUsuario(string usuario, string password) {

    // Verifica si el usuario y contraseña coinciden
    // con las credenciales definidas en el sistema
    return usuario == "admin" && password == "1234";
}