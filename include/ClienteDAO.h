#pragma once

#include <vector>
#include "Cliente.h"

class ClienteDAO {
public:
    void agregarCliente( string nombre, string telefono, string correo, string nit );
    bool eliminarCliente(int id);
    vector<Cliente> obtenerClientes();

    bool actualizarCliente(int id, string nombre, string telefono, string correo, string nit);
    Cliente buscarClientePorId(int id);
    vector<Cliente> buscarClientesPorNombre(string nombre);

    vector<Cliente> buscarClientesPorNit(string nit);
};
