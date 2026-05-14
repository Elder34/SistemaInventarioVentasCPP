#pragma once
#include "ProductoDAO.h"
#include "ClienteDAO.h"
#include "Login.h"

class AppUI {
private:
    ProductoDAO productoDAO;
    ClienteDAO clienteDAO;
    Login login;

    bool loginCorrecto;
    bool mostrarProductos;
    bool mostrarClientes;

    char usuario[50];
    char password[50];
    char mensajeLogin[100];

    char nombreProducto[100];
    char categoriaProducto[100];
    float precioProducto;
    int stockProducto;
    char nombreCliente[100];
    char telefonoCliente[100];
    char correoCliente[100];
    int idEliminarCliente;
    int idEliminar;

    void mostrarLogin();
    void mostrarMenuPrincipal();
    void mostrarModuloProductos();
    void mostrarModuloClientes();

public:
    AppUI();
    void ejecutar();
};