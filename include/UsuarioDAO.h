//administra la comunicación entre el sistema y la base de datos para gestionar los usuarios registrados.

#pragma once

#include <vector>
#include <string>
#include "Usuario.h"

using namespace std;

class UsuarioDAO {
public:

    //Registra un nuevo usuario en la base de datos.
    bool agregarUsuario(string nombre, string usuario, string password, string rol);

    //Obtiene todos los usuarios almacenados en el sistema retorna todos los usuarios
    vector<Usuario> obtenerUsuarios();

    //Modifica la información de un usuario existente.
    bool actualizarUsuario(int id, string nombre, string usuario, string password, string rol);

    //Elimina un usuario utilizando su identificador.
    bool eliminarUsuario(int id);
};