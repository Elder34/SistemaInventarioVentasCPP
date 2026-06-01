#pragma once

#include "ProductoDAO.h"
#include "ClienteDAO.h"
#include "Login.h"
#include "CorteDAO.h"
#include "VentaDAO.h"
#include "Venta.h"
#include "UsuarioDAO.h"

#include <vector>
#include <string>

using namespace std;

class AppUI {
private:

    ProductoDAO productoDAO;
    ClienteDAO clienteDAO;
    Login login;
    UsuarioDAO usuarioDAO;
    VentaDAO ventaDAO;
    CorteDAO corteDAO;

    bool loginCorrecto;
    bool mostrarProductos;
    bool mostrarClientes;
    bool mostrarCortes;
    bool mostrarInventario;
    bool mostrarUsuarios;
    bool mostrarDetalleCorte;

    char usuario[50];
    char password[50];
    char mensajeLogin[100];

    // PRODUCTOS
    char codigoProducto[50];
    char nombreProducto[100];
    char categoriaProducto[100];
    float precioProducto;
    int stockProducto;
    int idModificarProducto;
    int idBuscarProducto;
    int idEliminar;
    bool modoEdicionProducto;
    char buscarNombreProducto[100];
    char mensajeProducto[150];

    // CLIENTES
    int idModificarCliente;
    int idEliminarCliente;
    int idBuscarCliente;
    bool modoEdicionCliente;
    char nombreCliente[100];
    char telefonoCliente[100];
    char correoCliente[100];
    char nitCliente[30];
    char buscarNombreCliente[100];
    char mensajeCliente[150];

    // VENTA RAPIDA
    char buscarNitClienteVenta[30];
    char clienteSeleccionadoVenta[100];
    int idClienteVenta;
    char buscarProductoVenta[100];
    int cantidadVenta;
    char clienteVenta[100];
    char descripcionVenta[200];
    char vendedorVenta[100];
    float totalVenta;
    float pagoClienteVenta;
    float cambioVenta;
    int metodoPagoVenta;
    char mensajeVenta[150];
    char referenciaPagoVenta[100];

    struct ItemVenta {
        int idProducto;
        string nombre;
        int cantidad;
        float precio;
        float subtotal;
    };

    vector<ItemVenta> carritoVenta;

    // CORTES
    Corte corteSeleccionado;

    // INVENTARIO
    int idProductoInventario;
    int cantidadInventario;
    char buscarInventario[100];
    char mensajeInventario[150];

    // USUARIOS
    char nombreUsuarioNuevo[100];
    char usuarioNuevo[50];
    char passwordNuevo[50];
    char rolUsuarioActual[30];
    char rolUsuarioNuevo[30];
    char mensajeUsuario[100];
    int idUsuarioEditar;
    int idUsuarioEliminar;
    bool modoEdicionUsuario;

    // FUNCIONES
    void mostrarLogin();
    void mostrarMenuPrincipal();

    void mostrarModuloProductos();
    void mostrarModuloClientes();
    void mostrarModuloInventario();
    void mostrarModuloCortes();
    void mostrarModuloUsuarios();

    void mostrarVentaRapida();

    bool popupConfirmacion(
        const char* idPopup,
        const char* mensaje
    );

    void generarTicketPDF(
        string cliente,
        string metodoPago,
        float total,
        float pago,
        float cambio
    );

public:
    AppUI();
    void ejecutar();
};