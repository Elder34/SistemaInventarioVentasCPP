#pragma once

#include <vector>
#include "Cliente.h"

class ClienteDAO {
public:
    void agregarCliente(string nombre, string telefono, string correo);
    bool eliminarCliente(int id);
    vector<Cliente> obtenerClientes();

    bool actualizarCliente(int id, string nombre, string telefono, string correo);
    Cliente buscarClientePorId(int id);
    vector<Cliente> buscarClientesPorNombre(string nombre);
};