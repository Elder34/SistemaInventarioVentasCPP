#pragma once

#include <vector>
#include <string>
#include "Usuario.h"

using namespace std;

class UsuarioDAO {
public:

    bool agregarUsuario(
        string nombre,
        string usuario,
        string password,
        string rol
    );

    vector<Usuario> obtenerUsuarios();

    bool eliminarUsuario(int id);
};