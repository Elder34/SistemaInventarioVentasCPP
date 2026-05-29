#pragma once
#include "ProductoDAO.h"
#include "ClienteDAO.h"
#include "Login.h"
#include "CorteDAO.h"
#include "VentaDAO.h"
#include "Venta.h"
#include <vector>
#include <string>

using namespace std;

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
    char nitCliente[30];
    char buscarNitClienteVenta[30];
    char clienteSeleccionadoVenta[100];
    int idClienteVenta;

    int idModificarProducto;
    int idBuscarProducto;
    char buscarNombreProducto[100];
    char mensajeProducto[150];
    bool modoEdicionProducto;

    void mostrarModuloCortes();
    bool mostrarCortes = false;
    CorteDAO corteDAO;
    bool mostrarDetalleCorte;
    Corte corteSeleccionado;

    bool mostrarInventario;
    int idProductoInventario;
    int cantidadInventario;
    char buscarInventario[100];
    char mensajeInventario[150];

    VentaDAO ventaDAO;
    char clienteVenta[100];
    char descripcionVenta[200];
    char vendedorVenta[100];
    float totalVenta;
    char mensajeVenta[150];


    void mostrarLogin();
    void mostrarMenuPrincipal();
    void mostrarModuloProductos();
    void mostrarModuloClientes();
    void mostrarModuloInventario();

    char buscarProductoVenta[100];
    int cantidadVenta;
    

    void mostrarVentaRapida();
    struct ItemVenta {
        int idProducto;
        string nombre;
        int cantidad;
        float precio;
        float subtotal;
    };

    vector<ItemVenta> carritoVenta;

    float pagoClienteVenta;
    float cambioVenta;
    int metodoPagoVenta;

public:
    AppUI();
    void ejecutar();
};
