#pragma once
#include "ProductoDAO.h"
#include "ClienteDAO.h"
#include "Login.h"
#include "CorteDAO.h"

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

    int idModificarCliente;
    bool modoEdicionCliente;
    char mensajeCliente[150];
    char nombreCliente[100];
    char telefonoCliente[100];
    char correoCliente[100];
    int idEliminarCliente;
    int idEliminar;
    int idBuscarCliente;
    char buscarNombreCliente[100];

    int idModificarProducto;
    int idBuscarProducto;
    char buscarNombreProducto[100];
    char mensajeProducto[150];
    bool modoEdicionProducto;

    void mostrarModuloCortes();
    bool mostrarCortes = false;
    CorteDAO corteDAO;


    void mostrarLogin();
    void mostrarMenuPrincipal();
    void mostrarModuloProductos();
    void mostrarModuloClientes();

public:
    AppUI();
    void ejecutar();
};