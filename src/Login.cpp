#include "Login.h"

bool Login::validarUsuario(string usuario, string password) {
    return usuario == "admin" && password == "1234";
}