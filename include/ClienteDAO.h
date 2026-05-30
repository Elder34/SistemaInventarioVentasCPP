//administra la comunicación entre el sistema y la base de datos para realizar operaciones relacionadas con los clientes.
#pragma once

//Librerias
#include <vector>
#include "Cliente.h"

//Clase publica
class ClienteDAO {
public:
    //fUNCION 
    void agregarCliente( string nombre, string telefono, string correo, string nit );
    bool eliminarCliente(int id);

    //Vector dinamico para guardar campos de cliente
    vector<Cliente> obtenerClientes();

    bool actualizarCliente(int id, string nombre, string telefono, string correo, string nit);
    Cliente buscarClientePorId(int id);
    vector<Cliente> buscarClientesPorNombre(string nombre);

    vector<Cliente> buscarClientesPorNit(string nit);
};
