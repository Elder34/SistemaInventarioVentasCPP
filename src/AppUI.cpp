#include "AppUI.h"
#include <regex>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>

#include <ctime>
#include <sstream>

using namespace std;

//constructor 
AppUI::AppUI() {

    loginCorrecto = false;
    mostrarProductos = false;
    mostrarClientes = false;

    strcpy_s(usuario, "");
    strcpy_s(password, "");
    strcpy_s(mensajeLogin, "");

    strcpy_s(nombreProducto, "");
    strcpy_s(categoriaProducto, "");

    precioProducto = 0.0f;
    stockProducto = 0;
    idEliminar = 0;

    strcpy_s(nombreCliente, "");
    strcpy_s(telefonoCliente, "");
    strcpy_s(correoCliente, "");
    idBuscarCliente = 0;
    strcpy_s(buscarNombreCliente, "");
    idEliminarCliente = 0;
    idModificarCliente = 0;
    modoEdicionCliente = false;
    strcpy_s(mensajeCliente, "");
    strcpy_s(buscarNitClienteVenta, "");
    strcpy_s(clienteSeleccionadoVenta, "");
    idClienteVenta = 0;

    idModificarProducto = 0;
    idBuscarProducto = 0;
    strcpy_s(buscarNombreProducto, "");
    strcpy_s(mensajeProducto, "");
    modoEdicionProducto = false;

    mostrarCortes = false;
    mostrarDetalleCorte = false;
    mostrarInventario = false;

    idProductoInventario = 0;
    cantidadInventario = 0;

    strcpy_s(buscarInventario, "");
    strcpy_s(mensajeInventario, "");

    strcpy_s(buscarProductoVenta, "");
    cantidadVenta = 1;
    strcpy_s(mensajeVenta, "");
    carritoVenta.clear();

    mostrarUsuarios = false;
    mostrarUsuarios = false;

    strcpy_s(nombreUsuarioNuevo, "");
    strcpy_s(usuarioNuevo, "");
    strcpy_s(passwordNuevo, "");
    strcpy_s(rolUsuarioNuevo, "");
    strcpy_s(mensajeUsuario, "");

    idUsuarioEditar = 0;
    modoEdicionUsuario = false;

    pagoClienteVenta = 0.0f;
    cambioVenta = 0.0f;
    metodoPagoVenta = 0;

}
//Funcion de ejecutar
void AppUI::ejecutar() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1600, 900, "Sistema Inventario y Ventas", NULL, NULL);
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.4f;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (!loginCorrecto) {
            mostrarLogin();
        }
        else {
            mostrarMenuPrincipal();
        }

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

//Funcion Login pide contraseña al usuario
void AppUI::mostrarLogin() {
    ImGuiIO& io = ImGui::GetIO();

    float ancho = 720.0f;
    float alto = 500.0f;

    ImGui::SetNextWindowSize(ImVec2(ancho, alto), ImGuiCond_Always);
    ImGui::SetNextWindowPos(
        ImVec2((io.DisplaySize.x - ancho) / 2,
            (io.DisplaySize.y - alto) / 2),
        ImGuiCond_Always
    );

    ImGui::Begin("Login - Sistema de Inventario", NULL,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove
    );

    ImGui::Dummy(ImVec2(0, 20));

    ImGui::SetCursorPosX(170);
    ImGui::Text("SISTEMA DE INVENTARIO Y VENTAS");

    ImGui::Dummy(ImVec2(0, 20));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 25));

    ImGui::SetCursorPosX(120);
    ImGui::Text("Usuario");

    ImGui::SetCursorPosX(120);
    ImGui::SetNextItemWidth(450);
    ImGui::InputText("##usuarioLogin", usuario, IM_ARRAYSIZE(usuario));

    ImGui::Dummy(ImVec2(0, 15));

    ImGui::SetCursorPosX(120);
    ImGui::Text("Contraseña");

    ImGui::SetCursorPosX(120);
    ImGui::SetNextItemWidth(450);
    ImGui::InputText("##passwordLogin", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

    ImGui::Dummy(ImVec2(0, 25));

    ImGui::SetCursorPosX(270);
    if (ImGui::Button("Ingresar##btnLogin", ImVec2(180, 45))) {
        if (login.validarUsuario(usuario, password)) {
            loginCorrecto = true;
            strcpy_s(mensajeLogin, "");
        }
        else {
            strcpy_s(mensajeLogin, "Usuario o contraseña incorrectos");
        }
    }

    if (strlen(mensajeLogin) > 0) {
        ImGui::Dummy(ImVec2(0, 15));
        ImGui::SetCursorPosX(190);
        ImGui::TextColored(ImVec4(1, 0, 0, 1), mensajeLogin);
    }

    ImGui::End();
}

//Funcion de menu principar del programa
void AppUI::mostrarMenuPrincipal() {

    ImGuiIO& io = ImGui::GetIO();

    float ancho = 1350.0f;
    float alto = 820.0f;

    ImGui::SetNextWindowSize(ImVec2(ancho, alto), ImGuiCond_Always);
    ImGui::SetNextWindowPos(
        ImVec2((io.DisplaySize.x - ancho) / 2,
            (io.DisplaySize.y - alto) / 2),
        ImGuiCond_Always
    );

    ImGui::Begin("MENU PRINCIPAL", NULL,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove
    );

    ImGui::Dummy(ImVec2(0, 10));

    //Botones de menu
    if (ImGui::Button("Productos", ImVec2(210, 55))) {
        mostrarProductos = true;
        mostrarClientes = false;
        mostrarCortes = false;
        mostrarInventario = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Clientes", ImVec2(210, 55))) {
        mostrarClientes = true;
        mostrarProductos = false;
        mostrarCortes = false;
        mostrarInventario = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cortes", ImVec2(210, 55))) {
        mostrarCortes = true;
        mostrarProductos = false;
        mostrarClientes = false;
        mostrarInventario = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Inventario", ImVec2(210, 55))) {
        mostrarInventario = true;
        mostrarProductos = false;
        mostrarClientes = false;
        mostrarCortes = false;
    }
    ImGui::SameLine();

    if (ImGui::Button("Usuarios", ImVec2(180, 55))) {
        mostrarUsuarios = true;

        mostrarProductos = false;
        mostrarClientes = false;
        mostrarCortes = false;
        mostrarInventario = false;
    }

    
    ImGui::SameLine();

    if (ImGui::Button("Cerrar Sesion", ImVec2(230, 55))) {
        loginCorrecto = false;

        mostrarProductos = false;
        mostrarClientes = false;
        mostrarCortes = false;
        mostrarInventario = false;

        strcpy_s(usuario, "");
        strcpy_s(password, "");
    }

    ImGui::Separator();

    mostrarVentaRapida();

    ImGui::Separator();

    if (mostrarProductos)
        mostrarModuloProductos();

    if (mostrarClientes)
        mostrarModuloClientes();

    if (mostrarCortes)
        mostrarModuloCortes();

    if (mostrarUsuarios)
        mostrarModuloUsuarios();

    if (mostrarInventario)
        mostrarModuloInventario();

    ImGui::End();
}

//Funcion me modulo de productos 
void AppUI::mostrarModuloProductos() {
    ImGui::SetNextWindowSize(ImVec2(1080, 750), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(130, 70), ImGuiCond_Once);

    ImGui::Begin("Modulo Productos", &mostrarProductos);

    ImGui::Text("Gestion de Productos");
    ImGui::Separator();

    ImGui::Text("Nombre");
    ImGui::InputText("##nombreProducto", nombreProducto, IM_ARRAYSIZE(nombreProducto));

    ImGui::Text("Precio");
    ImGui::InputFloat("##precioProducto", &precioProducto);

    ImGui::Text("Stock");
    ImGui::InputInt("##stockProducto", &stockProducto);

    ImGui::Text("Categoria");
    ImGui::InputText("##categoriaProducto", categoriaProducto, IM_ARRAYSIZE(categoriaProducto));

    if (!modoEdicionProducto) {
        if (ImGui::Button("Agregar Producto", ImVec2(180, 35))) {
            if (strlen(nombreProducto) > 0 && precioProducto > 0 && stockProducto >= 0) {
                productoDAO.agregarProducto(nombreProducto, precioProducto, stockProducto, categoriaProducto);

                strcpy_s(nombreProducto, "");
                strcpy_s(categoriaProducto, "");
                precioProducto = 0.0f;
                stockProducto = 0;

                strcpy_s(mensajeProducto, "Producto agregado correctamente");
            }
            else {
                strcpy_s(mensajeProducto, "Complete los datos del producto");
            }
        }
    }
    else {
        if (ImGui::Button("Guardar Cambios", ImVec2(180, 35))) {
            if (idModificarProducto > 0 && strlen(nombreProducto) > 0 && precioProducto > 0 && stockProducto >= 0) {
                productoDAO.actualizarProducto(
                    idModificarProducto,
                    nombreProducto,
                    precioProducto,
                    stockProducto,
                    categoriaProducto
                );

                idModificarProducto = 0;
                modoEdicionProducto = false;

                strcpy_s(nombreProducto, "");
                strcpy_s(categoriaProducto, "");
                precioProducto = 0.0f;
                stockProducto = 0;

                strcpy_s(mensajeProducto, "Producto actualizado correctamente");
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Limpiar", ImVec2(120, 35))) {
        strcpy_s(nombreProducto, "");
        strcpy_s(categoriaProducto, "");
        strcpy_s(buscarNombreProducto, "");
        strcpy_s(mensajeProducto, "");

        precioProducto = 0.0f;
        stockProducto = 0;
        idEliminar = 0;
        idBuscarProducto = 0;
        idModificarProducto = 0;
        modoEdicionProducto = false;
    }

    if (strlen(mensajeProducto) > 0) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), mensajeProducto);
    }

    ImGui::Separator();

    ImGui::Text("Busqueda de productos");
    ImGui::Separator();

    ImGui::Text("Buscar por ID");
    ImGui::InputInt("##idBuscarProducto", &idBuscarProducto);

    if (ImGui::Button("Buscar ID", ImVec2(120, 35))) {
        Producto producto = productoDAO.buscarProductoPorId(idBuscarProducto);

        if (producto.getId() > 0) {
            idModificarProducto = producto.getId();

            strcpy_s(nombreProducto, producto.getNombre().c_str());
            precioProducto = producto.getPrecio();
            stockProducto = producto.getStock();
            strcpy_s(categoriaProducto, producto.getCategoria().c_str());

            modoEdicionProducto = true;
            strcpy_s(mensajeProducto, "Producto encontrado. Puede modificarlo.");
        }
        else {
            strcpy_s(mensajeProducto, "No se encontro producto con ese ID");
        }
    }

    ImGui::Spacing();

    ImGui::Text("Buscar por nombre");
    ImGui::InputText(
        "##buscarNombreProducto",
        buscarNombreProducto,
        IM_ARRAYSIZE(buscarNombreProducto)
    );

    ImGui::Separator();

    vector<Producto> productos;

    if (strlen(buscarNombreProducto) > 0) {
        productos = productoDAO.buscarProductosPorNombre(buscarNombreProducto);
    }
    else {
        productos = productoDAO.obtenerProductos();
    }

    if (ImGui::BeginTable(
        "tabla_productos",
        6,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg)) {

        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Nombre");
        ImGui::TableSetupColumn("Precio");
        ImGui::TableSetupColumn("Stock");
        ImGui::TableSetupColumn("Categoria");
        ImGui::TableSetupColumn("Accion");
        ImGui::TableHeadersRow();

        for (int i = 0; i < productos.size(); i++) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", productos[i].getId());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", productos[i].getNombre().c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("Q %.2f", productos[i].getPrecio());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%d", productos[i].getStock());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%s", productos[i].getCategoria().c_str());

            ImGui::TableSetColumnIndex(5);

            string btnEditar = "Editar##producto" + to_string(productos[i].getId());

            if (ImGui::Button(btnEditar.c_str(), ImVec2(80, 30))) {
                idModificarProducto = productos[i].getId();

                strcpy_s(nombreProducto, productos[i].getNombre().c_str());
                precioProducto = productos[i].getPrecio();
                stockProducto = productos[i].getStock();
                strcpy_s(categoriaProducto, productos[i].getCategoria().c_str());

                modoEdicionProducto = true;
                strcpy_s(mensajeProducto, "Editando producto seleccionado");
            }

            ImGui::SameLine();

            string btnEliminar = "Eliminar##producto" + to_string(productos[i].getId());

            if (ImGui::Button(btnEliminar.c_str(), ImVec2(90, 30))) {
                if (productoDAO.eliminarProducto(productos[i].getId())) {
                    strcpy_s(mensajeProducto, "Producto eliminado correctamente");
                }
                else {
                    strcpy_s(mensajeProducto, "No se pudo eliminar el producto");
                }
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}
//Funcion regular para validacion de correos
bool correoValido(const std::string& correo) {
    std::regex patron(
        R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"
    );
    return std::regex_match(correo, patron);
}

//Funcion de modulo cliente 
//Funcion princiapr es agregar clientes 
void AppUI::mostrarModuloClientes() {

    ImGui::SetNextWindowSize(ImVec2(1100, 650), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(260, 130), ImGuiCond_Once);

    ImGui::Begin("Modulo Clientes", &mostrarClientes);

    ImGui::Text("CRUD de Clientes");
    ImGui::Separator();

    ImGui::Text("Nombre");
    ImGui::InputText("##clienteNombre", nombreCliente, IM_ARRAYSIZE(nombreCliente));

    ImGui::Text("Telefono");
    ImGui::InputText("##clienteTelefono", telefonoCliente, IM_ARRAYSIZE(telefonoCliente));

    ImGui::Text("Correo");
    ImGui::InputText("##clienteCorreo", correoCliente, IM_ARRAYSIZE(correoCliente));

    ImGui::Text("NIT");
    ImGui::InputText("##clienteNit", nitCliente, IM_ARRAYSIZE(nitCliente));
    if (!modoEdicionCliente) {
        if (ImGui::Button("Agregar Cliente##btnAgregarCliente", ImVec2(180, 35))) {

            if (strlen(nombreCliente) == 0) {
                strcpy_s(mensajeCliente, "Ingrese nombre");
            }
            else if (!correoValido(correoCliente)) {
                strcpy_s(mensajeCliente, "Correo invalido");
            }
            else {
                clienteDAO.agregarCliente(
                    nombreCliente,
                    telefonoCliente,
                    correoCliente,
                    nitCliente
                );

                strcpy_s(nombreCliente, "");
                strcpy_s(telefonoCliente, "");
                strcpy_s(correoCliente, "");

                strcpy_s(mensajeCliente, "Cliente agregado correctamente");
            }
        }
    }
    else {
        if (ImGui::Button("Guardar Cambios##btnGuardarCliente", ImVec2(190, 35))) {

            if (idModificarCliente > 0 && strlen(nombreCliente) > 0) {

                if (!correoValido(correoCliente)) {
                    strcpy_s(mensajeCliente, "Correo invalido");
                }
                else {
                    clienteDAO.actualizarCliente(
                        idModificarCliente,
                        nombreCliente,
                        telefonoCliente,
                        correoCliente,
                        nitCliente
                    );

                    idModificarCliente = 0;
                    modoEdicionCliente = false;

                    strcpy_s(nombreCliente, "");
                    strcpy_s(telefonoCliente, "");
                    strcpy_s(correoCliente, "");
                    strcpy_s(nitCliente, "");

                    strcpy_s(mensajeCliente, "Cliente actualizado correctamente");
                }
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Limpiar##btnLimpiarCliente", ImVec2(120, 35))) {
        strcpy_s(nombreCliente, "");
        strcpy_s(telefonoCliente, "");
        strcpy_s(correoCliente, "");
        strcpy_s(buscarNombreCliente, "");

        idBuscarCliente = 0;
        idModificarCliente = 0;
        modoEdicionCliente = false;

        strcpy_s(mensajeCliente, "");
    }

    if (strlen(mensajeCliente) > 0) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), mensajeCliente);
    }

    ImGui::Separator();

    ImGui::Text("Busqueda de clientes");

    ImGui::Text("Buscar por ID");
    ImGui::InputInt("##buscarClienteID", &idBuscarCliente);

    if (ImGui::Button("Buscar ID##btnBuscarClienteID", ImVec2(130, 35))) {

        Cliente cliente = clienteDAO.buscarClientePorId(idBuscarCliente);

        if (cliente.getId() > 0) {
            idModificarCliente = cliente.getId();

            strcpy_s(nombreCliente, sizeof(nombreCliente), cliente.getNombre().c_str());
            strcpy_s(telefonoCliente, sizeof(telefonoCliente), cliente.getTelefono().c_str());
            strcpy_s(correoCliente, sizeof(correoCliente), cliente.getCorreo().c_str());

            modoEdicionCliente = true;

            strcpy_s(mensajeCliente, "Cliente encontrado. Puede modificarlo.");
        }
        else {
            strcpy_s(mensajeCliente, "No se encontro cliente con ese ID");
        }
    }

    ImGui::SameLine();

    ImGui::Text("Buscar por nombre");
    ImGui::InputText("##buscarClienteNombre", buscarNombreCliente, IM_ARRAYSIZE(buscarNombreCliente));

    ImGui::Separator();

    vector<Cliente> clientes;

    if (strlen(buscarNombreCliente) > 0) {
        clientes = clienteDAO.buscarClientesPorNombre(buscarNombreCliente);
    }
    else {
        clientes = clienteDAO.obtenerClientes();
    }

    if (ImGui::BeginTable(
        "tabla_clientes",
        5,
        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {

        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Nombre");
        ImGui::TableSetupColumn("Telefono");
        ImGui::TableSetupColumn("Correo");
        ImGui::TableSetupColumn("Accion", ImGuiTableColumnFlags_WidthFixed, 230.0f);

        ImGui::TableHeadersRow();

        for (int i = 0; i < clientes.size(); i++) {

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", clientes[i].getId());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", clientes[i].getNombre().c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", clientes[i].getTelefono().c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%s", clientes[i].getCorreo().c_str());

            ImGui::TableSetColumnIndex(4);

            string btnEditar = "Editar##clienteEditar" + to_string(clientes[i].getId());

            if (ImGui::Button(btnEditar.c_str(), ImVec2(85, 30))) {
                idModificarCliente = clientes[i].getId();

                strcpy_s(nombreCliente, sizeof(nombreCliente), clientes[i].getNombre().c_str());
                strcpy_s(telefonoCliente, sizeof(telefonoCliente), clientes[i].getTelefono().c_str());
                strcpy_s(correoCliente, sizeof(correoCliente), clientes[i].getCorreo().c_str());

                modoEdicionCliente = true;

                strcpy_s(mensajeCliente, "Editando cliente seleccionado");
            }

            ImGui::SameLine();

            string btnEliminar = "Eliminar##clienteEliminar" + to_string(clientes[i].getId());

            if (ImGui::Button(btnEliminar.c_str(), ImVec2(100, 30))) {
                clienteDAO.eliminarCliente(clientes[i].getId());
                strcpy_s(mensajeCliente, "Cliente eliminado correctamente");
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

//Funcion de Modulo de cortes muestrar las ventas realizaddas
void AppUI::mostrarModuloCortes() {

    ImGui::SetNextWindowSize(ImVec2(1100, 650), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(170, 80), ImGuiCond_Once);

    ImGui::Begin("Modulo Cortes", &mostrarCortes);

    ImGui::Text("Historial de Cortes");
    ImGui::Separator();

    if (ImGui::Button("Cerrar Cortes", ImVec2(180, 35))) {
        mostrarCortes = false;
        mostrarDetalleCorte = false;
    }

    ImGui::Spacing();

    vector<Corte> cortes = corteDAO.obtenerCortes();

    if (ImGui::BeginTable(
        "tablaCortes",
        7,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Fecha");
        ImGui::TableSetupColumn("Descripcion");
        ImGui::TableSetupColumn("Metodo Pago");
        ImGui::TableSetupColumn("Vendedor");
        ImGui::TableSetupColumn("Total");
        ImGui::TableSetupColumn("Accion");

        ImGui::TableHeadersRow();

        for (int i = 0; i < cortes.size(); i++) {

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", cortes[i].id);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", cortes[i].fecha.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", cortes[i].descripcion.c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%s", cortes[i].metodoPago.c_str());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%s", cortes[i].vendedor.c_str());

            ImGui::TableSetColumnIndex(5);
            ImGui::Text("Q %.2f", cortes[i].total);

            ImGui::TableSetColumnIndex(6);

            string btnVer = "Ver##corte" + to_string(cortes[i].id);

            if (ImGui::Button(btnVer.c_str(), ImVec2(80, 30))) {
                corteSeleccionado = cortes[i];
                mostrarDetalleCorte = true;
            }
        }

        ImGui::EndTable();
    }

    if (mostrarDetalleCorte) {
        ImGui::Spacing();
        ImGui::Separator();

        ImGui::Text("Detalle del Corte");
        ImGui::Separator();

        ImGui::Text("ID: %d", corteSeleccionado.id);
        ImGui::Text("Fecha: %s", corteSeleccionado.fecha.c_str());
        ImGui::Text("Descripcion: %s", corteSeleccionado.descripcion.c_str());
        ImGui::Text("Metodo Pago: %s", corteSeleccionado.metodoPago.c_str());
        ImGui::Text("Vendedor: %s", corteSeleccionado.vendedor.c_str());
        ImGui::Text("Total: Q %.2f", corteSeleccionado.total);

        if (ImGui::Button("Cerrar detalle##cerrarDetalleCorte", ImVec2(160, 35))) {
            mostrarDetalleCorte = false;
        }
    }

    ImGui::End();
}

//Funcion de Inventario Muestra el inventario ingresado
void AppUI::mostrarModuloInventario() {

    ImGui::SetNextWindowSize(ImVec2(1080, 650), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(180, 90), ImGuiCond_Once);

    ImGui::Begin("Modulo Inventario", &mostrarInventario);

    ImGui::Text("Modulo Inventario");
    ImGui::Separator();

    ImGui::Text("Buscar producto");
    ImGui::InputText(
        "##buscarInventario",
        buscarInventario,
        IM_ARRAYSIZE(buscarInventario)
    );

    ImGui::Text("ID Producto");
    ImGui::InputInt(
        "##idProductoInventario",
        &idProductoInventario
    );

    ImGui::Text("Cantidad");
    ImGui::InputInt(
        "##cantidadInventario",
        &cantidadInventario
    );

    

    vector<Producto> productos;

    if (strlen(buscarInventario) > 0) {
        productos = productoDAO.buscarProductosPorNombre(buscarInventario);
    }
    else {
        productos = productoDAO.obtenerProductos();
    }

    if (ImGui::Button("Agregar Stock##btnAgregarStock", ImVec2(180, 35))) {

        int idUsar = idProductoInventario;

        if (idUsar == 0 && productos.size() == 1) {
            idUsar = productos[0].getId();
        }

        Producto producto = productoDAO.buscarProductoPorId(idUsar);

        if (producto.getId() > 0 && cantidadInventario > 0) {

            int nuevoStock = producto.getStock() + cantidadInventario;

            productoDAO.actualizarStockProducto(producto.getId(), nuevoStock);

            strcpy_s(mensajeInventario, "Stock agregado correctamente");

            idProductoInventario = producto.getId();
        }
        else {
            strcpy_s(mensajeInventario, "Producto o cantidad invalida");
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Quitar Stock##btnQuitarStock", ImVec2(180, 35))) {

        int idUsar = idProductoInventario;

        if (idUsar == 0 && productos.size() == 1) {
            idUsar = productos[0].getId();
        }

        Producto producto = productoDAO.buscarProductoPorId(idUsar);

        if (producto.getId() > 0 && cantidadInventario > 0) {

            int nuevoStock = producto.getStock() - cantidadInventario;

            if (nuevoStock >= 0) {
                productoDAO.actualizarStockProducto(producto.getId(), nuevoStock);
                strcpy_s(mensajeInventario, "Stock reducido correctamente");
                idProductoInventario = producto.getId();
            }
            else {
                strcpy_s(mensajeInventario, "No puede quedar stock negativo");
            }
        }
        else {
            strcpy_s(mensajeInventario, "Producto o cantidad invalida");
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Limpiar##btnLimpiarInventario", ImVec2(120, 35))) {
        idProductoInventario = 0;
        cantidadInventario = 0;
        strcpy_s(buscarInventario, "");
        strcpy_s(mensajeInventario, "");
    }

    ImGui::SameLine();

    if (ImGui::Button("Salir##btnSalirInventario", ImVec2(120, 35))) {

        mostrarInventario = false;

        idProductoInventario = 0;
        cantidadInventario = 0;

        strcpy_s(buscarInventario, "");
        strcpy_s(mensajeInventario, "");
    }

    if (strlen(mensajeInventario) > 0) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), mensajeInventario);
    }

    ImGui::Separator();

    if (ImGui::BeginTable(
        "tablaInventario",
        6,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Producto");
        ImGui::TableSetupColumn("Categoria");
        ImGui::TableSetupColumn("Precio");
        ImGui::TableSetupColumn("Stock");
        ImGui::TableSetupColumn("Estado");

        ImGui::TableHeadersRow();

        for (int i = 0; i < productos.size(); i++) {

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            string btnSeleccionar =
                "Seleccionar##inventario" +
                to_string(productos[i].getId());

            if (ImGui::Button(btnSeleccionar.c_str(), ImVec2(130, 30))) {
                idProductoInventario = productos[i].getId();
                strcpy_s(mensajeInventario, "Producto seleccionado");
            }

            ImGui::SameLine();
            ImGui::Text("%d", productos[i].getId());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", productos[i].getNombre().c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", productos[i].getCategoria().c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("Q %.2f", productos[i].getPrecio());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%d", productos[i].getStock());

            ImGui::TableSetColumnIndex(5);

            if (productos[i].getStock() == 0) {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Sin stock");
            }
            else if (productos[i].getStock() <= 5) {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "Stock bajo");
            }
            else {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "Disponible");
            }
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

//Funcion de Ventas rapidas se realizan ventas mediante busqueda de producto 
void AppUI::mostrarVentaRapida() {

    ImGui::Text("VENTA RAPIDA");
    ImGui::Separator();

    ImGui::Text("Buscar NIT cliente");
    ImGui::InputText(
        "##buscarNitClienteVenta",
        buscarNitClienteVenta,
        IM_ARRAYSIZE(buscarNitClienteVenta)
    
    );

    if (strlen(buscarNitClienteVenta) > 0) {
        vector<Cliente> clientesVenta =
            clienteDAO.buscarClientesPorNit(buscarNitClienteVenta);

        if (ImGui::BeginTable(
            "tablaClientesVenta",
            4,
            ImGuiTableFlags_Borders |
            ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Cliente");
            ImGui::TableSetupColumn("NIT");
            ImGui::TableSetupColumn("Accion");
            ImGui::TableHeadersRow();

            for (int i = 0; i < clientesVenta.size(); i++) {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%d", clientesVenta[i].getId());

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", clientesVenta[i].getNombre().c_str());

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", clientesVenta[i].getNit().c_str());

                ImGui::TableSetColumnIndex(3);

                string btnCliente =
                    "Seleccionar##clienteVenta" +
                    to_string(clientesVenta[i].getId());

                if (ImGui::Button(btnCliente.c_str(), ImVec2(120, 30))) {
                    idClienteVenta = clientesVenta[i].getId();

                    strcpy_s(
                        clienteSeleccionadoVenta,
                        clientesVenta[i].getNombre().c_str()
                    );

                    strcpy_s(buscarNitClienteVenta, "");
                    strcpy_s(mensajeVenta, "Cliente seleccionado");
                }
            }

            ImGui::EndTable();
        }
    }

    if (idClienteVenta > 0) {
        ImGui::Text("Cliente seleccionado: %s", clienteSeleccionadoVenta);
    }
    else {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Seleccione un cliente para la venta");
    }

    ImGui::Separator();

    ImGui::Text("Buscar producto");
    ImGui::InputText(
        "##buscarProductoVenta",
        buscarProductoVenta,
        IM_ARRAYSIZE(buscarProductoVenta)
    );

    ImGui::Text("Cantidad");
    ImGui::InputInt("##cantidadVenta", &cantidadVenta);

    vector<Producto> productosVenta;

    if (strlen(buscarProductoVenta) > 0) {
        productosVenta = productoDAO.buscarProductosPorNombre(buscarProductoVenta);
    }

    if (strlen(buscarProductoVenta) > 0) {

        if (ImGui::BeginTable("tablaBusquedaVenta", 5,
            ImGuiTableFlags_Borders |
            ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Producto");
            ImGui::TableSetupColumn("Precio");
            ImGui::TableSetupColumn("Stock");
            ImGui::TableSetupColumn("Accion");
            ImGui::TableHeadersRow();

            for (int i = 0; i < productosVenta.size(); i++) {

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%d", productosVenta[i].getId());

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", productosVenta[i].getNombre().c_str());

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("Q %.2f", productosVenta[i].getPrecio());

                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%d", productosVenta[i].getStock());

                ImGui::TableSetColumnIndex(4);

                string btnAgregar = "Agregar##ventaProducto" + to_string(productosVenta[i].getId());

                if (ImGui::Button(btnAgregar.c_str(), ImVec2(90, 30))) {

                    if (cantidadVenta <= 0) {
                        strcpy_s(mensajeVenta, "Cantidad invalida");
                    }
                    else if (cantidadVenta > productosVenta[i].getStock()) {
                        strcpy_s(mensajeVenta, "No hay suficiente stock");
                    }
                    else {
                        ItemVenta item;
                        item.idProducto = productosVenta[i].getId();
                        item.nombre = productosVenta[i].getNombre();
                        item.cantidad = cantidadVenta;
                        item.precio = productosVenta[i].getPrecio();
                        item.subtotal = item.precio * item.cantidad;

                        carritoVenta.push_back(item);

                        strcpy_s(buscarProductoVenta, "");
                        cantidadVenta = 1;
                        strcpy_s(mensajeVenta, "Producto agregado a la venta");
                    }
                }
            }

            ImGui::EndTable();
        }
    }

    ImGui::Separator();
    ImGui::Text("Ticket actual");

    float total = 0.0f;

    if (ImGui::BeginTable("tablaCarritoVenta", 5,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Producto");
        ImGui::TableSetupColumn("Cantidad");
        ImGui::TableSetupColumn("Precio");
        ImGui::TableSetupColumn("Subtotal");
        ImGui::TableSetupColumn("Accion");
        ImGui::TableHeadersRow();

        for (int i = 0; i < carritoVenta.size(); i++) {

            total += carritoVenta[i].subtotal;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", carritoVenta[i].nombre.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", carritoVenta[i].cantidad);

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("Q %.2f", carritoVenta[i].precio);

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("Q %.2f", carritoVenta[i].subtotal);

            ImGui::TableSetColumnIndex(4);

            string btnEliminar = "Quitar##itemVenta" + to_string(i);

            if (ImGui::Button(btnEliminar.c_str(), ImVec2(80, 30))) {
                carritoVenta.erase(carritoVenta.begin() + i);
                break;
            }
        }

        ImGui::EndTable();
    }

    ImGui::Text("Total: Q %.2f", total);

    const char* metodosPago[] = {
    "Efectivo",
    "Tarjeta",
    "Transferencia"
    };

    ImGui::Text("Metodo de pago");
    ImGui::Combo(
        "##metodoPagoVenta",
        &metodoPagoVenta,
        "Efectivo\0Tarjeta\0Transferencia\0"
    );

    ImGui::Text("Pago cliente");
    ImGui::InputFloat(
        "##pagoClienteVenta",
        &pagoClienteVenta
    );

    cambioVenta = pagoClienteVenta - total;

    ImGui::Text("Cambio: Q %.2f", cambioVenta);

    if (ImGui::Button("Cobrar venta##btnCobrarVenta", ImVec2(180, 35))) {

        if (idClienteVenta <= 0) {
            strcpy_s(mensajeVenta, "Seleccione un cliente");
        }
        else if (carritoVenta.empty()) {
            strcpy_s(mensajeVenta, "Agregue productos al ticket");
        }
        else if (metodoPagoVenta == 0 && pagoClienteVenta < total) {
            strcpy_s(mensajeVenta, "Pago insuficiente");
        }
        else {

            string descripcion = "";

            for (int i = 0; i < carritoVenta.size(); i++) {
                descripcion += carritoVenta[i].nombre;
                descripcion += " x";
                descripcion += to_string(carritoVenta[i].cantidad);

                if (i < carritoVenta.size() - 1) {
                    descripcion += ", ";
                }

                Producto producto = productoDAO.buscarProductoPorId(
                    carritoVenta[i].idProducto
                );

                int nuevoStock =
                    producto.getStock() - carritoVenta[i].cantidad;

                productoDAO.actualizarStockProducto(
                    producto.getId(),
                    nuevoStock
                );
            }

            string metodo = metodosPago[metodoPagoVenta];

            
            

            bool ok = ventaDAO.registrarVenta(
                clienteSeleccionadoVenta,
                descripcion,
                vendedorVenta,
                total,
                metodo
            );

            if (ok) {

                generarTicketPDF(
                    clienteSeleccionadoVenta,
                    metodo,
                    total,
                    pagoClienteVenta,
                    cambioVenta
                );

                carritoVenta.clear();

                strcpy_s(buscarProductoVenta, "");
                strcpy_s(buscarNitClienteVenta, "");
                strcpy_s(clienteSeleccionadoVenta, "");
                strcpy_s(mensajeVenta, "Venta cobrada correctamente");

                idClienteVenta = 0;
                cantidadVenta = 1;
                pagoClienteVenta = 0.0f;
                cambioVenta = 0.0f;
                metodoPagoVenta = 0;
            }
            else {
                strcpy_s(mensajeVenta, "Error al cobrar venta");
            }
        }
    }

    if (strlen(mensajeVenta) > 0) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), mensajeVenta);
    }

    if (ImGui::Button("Cancelar venta##cancelarVenta", ImVec2(160, 35))) {
        carritoVenta.clear();
        strcpy_s(buscarProductoVenta, "");
        cantidadVenta = 1;
        strcpy_s(mensajeVenta, "Venta cancelada");
    }
}

//Funcion de usuarios creasion, edicion y eliminacion
void AppUI::mostrarModuloUsuarios() {

    ImGui::SetNextWindowSize(ImVec2(1000, 650), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(220, 100), ImGuiCond_Once);

    ImGui::Begin("Modulo Usuarios", &mostrarUsuarios);

    ImGui::Text("CRUD de Usuarios");
    ImGui::Separator();

    ImGui::Text("Nombre");
    ImGui::InputText("##nombreUsuarioNuevo", nombreUsuarioNuevo, IM_ARRAYSIZE(nombreUsuarioNuevo));

    ImGui::Text("Usuario");
    ImGui::InputText("##usuarioNuevo", usuarioNuevo, IM_ARRAYSIZE(usuarioNuevo));

    ImGui::Text("Password");
    ImGui::InputText("##passwordNuevo", passwordNuevo, IM_ARRAYSIZE(passwordNuevo), ImGuiInputTextFlags_Password);

    ImGui::Text("Rol");
    ImGui::InputText("##rolUsuarioNuevo", rolUsuarioNuevo, IM_ARRAYSIZE(rolUsuarioNuevo));

    if (!modoEdicionUsuario) {
        if (ImGui::Button("Crear Usuario", ImVec2(180, 35))) {
            bool ok = usuarioDAO.agregarUsuario(nombreUsuarioNuevo, usuarioNuevo, passwordNuevo, rolUsuarioNuevo);

            if (ok) {
                strcpy_s(mensajeUsuario, "Usuario creado correctamente");
                strcpy_s(nombreUsuarioNuevo, "");
                strcpy_s(usuarioNuevo, "");
                strcpy_s(passwordNuevo, "");
                strcpy_s(rolUsuarioNuevo, "");
            }
            else {
                strcpy_s(mensajeUsuario, "Error al crear usuario");
            }
        }
    }
    else {
        if (ImGui::Button("Guardar Cambios", ImVec2(180, 35))) {
            bool ok = usuarioDAO.actualizarUsuario(
                idUsuarioEditar,
                nombreUsuarioNuevo,
                usuarioNuevo,
                passwordNuevo,
                rolUsuarioNuevo
            );

            if (ok) {
                strcpy_s(mensajeUsuario, "Usuario actualizado correctamente");
                idUsuarioEditar = 0;
                modoEdicionUsuario = false;

                strcpy_s(nombreUsuarioNuevo, "");
                strcpy_s(usuarioNuevo, "");
                strcpy_s(passwordNuevo, "");
                strcpy_s(rolUsuarioNuevo, "");
            }
            else {
                strcpy_s(mensajeUsuario, "Error al actualizar usuario");
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Limpiar", ImVec2(120, 35))) {
        strcpy_s(nombreUsuarioNuevo, "");
        strcpy_s(usuarioNuevo, "");
        strcpy_s(passwordNuevo, "");
        strcpy_s(rolUsuarioNuevo, "");
        strcpy_s(mensajeUsuario, "");

        idUsuarioEditar = 0;
        modoEdicionUsuario = false;
    }

    if (strlen(mensajeUsuario) > 0) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", mensajeUsuario);
    }

    ImGui::Separator();

    vector<Usuario> usuarios = usuarioDAO.obtenerUsuarios();

    if (ImGui::BeginTable("tablaUsuarios", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Nombre");
        ImGui::TableSetupColumn("Usuario");
        ImGui::TableSetupColumn("Password");
        ImGui::TableSetupColumn("Rol");
        ImGui::TableSetupColumn("Accion");
        ImGui::TableHeadersRow();

        for (int i = 0; i < usuarios.size(); i++) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", usuarios[i].id);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", usuarios[i].nombre.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", usuarios[i].usuario.c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%s", usuarios[i].password.c_str());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%s", usuarios[i].rol.c_str());

            ImGui::TableSetColumnIndex(5);

            string btnEditar = "Editar##usuario" + to_string(usuarios[i].id);

            if (ImGui::Button(btnEditar.c_str(), ImVec2(80, 30))) {
                idUsuarioEditar = usuarios[i].id;
                modoEdicionUsuario = true;

                strcpy_s(nombreUsuarioNuevo, usuarios[i].nombre.c_str());
                strcpy_s(usuarioNuevo, usuarios[i].usuario.c_str());
                strcpy_s(passwordNuevo, usuarios[i].password.c_str());
                strcpy_s(rolUsuarioNuevo, usuarios[i].rol.c_str());

                strcpy_s(mensajeUsuario, "Editando usuario seleccionado");
            }

            ImGui::SameLine();

            string btnEliminar = "Eliminar##usuario" + to_string(usuarios[i].id);

            if (ImGui::Button(btnEliminar.c_str(), ImVec2(90, 30))) {
                if (usuarioDAO.eliminarUsuario(usuarios[i].id)) {
                    strcpy_s(mensajeUsuario, "Usuario eliminado correctamente");
                }
                else {
                    strcpy_s(mensajeUsuario, "No se pudo eliminar usuario");
                }
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

//Funcion para generar el ticket de la venta realizada
void AppUI::generarTicketPDF(
    string cliente,
    string metodoPago,
    float total,
    float pago,
    float cambio
) {
    system("mkdir tickets > nul 2>&1");

    time_t ahora = time(0);
    tm tiempoLocal;
    localtime_s(&tiempoLocal, &ahora);

    char nombreArchivo[100];
    strftime(
        nombreArchivo,
        sizeof(nombreArchivo),
        "tickets/ticket_%Y%m%d_%H%M%S.pdf",
        &tiempoLocal
    );

    ofstream pdf(nombreArchivo, ios::binary);

    if (!pdf.is_open()) {
        strcpy_s(
            mensajeVenta,
            sizeof(mensajeVenta),
            "No se pudo generar PDF"
        );
        return;
    }

    stringstream contenido;
    int y = 780;

    auto linea = [&](string texto, int size = 12) {
        contenido
            << "BT /F1 "
            << size
            << " Tf 40 "
            << y
            << " Td ("
            << texto
            << ") Tj ET\n";

        y -= 20;
        };

    char fecha[80];
    strftime(
        fecha,
        sizeof(fecha),
        "%d/%m/%Y %H:%M:%S",
        &tiempoLocal
    );

    linea("NOVA MARKET", 18);
    linea("Sistema Inventario y Ventas", 12);
    linea("------------------------------------");

    linea(string("Fecha: ") + fecha);
    linea(string("Cliente: ") + cliente);
    linea(string("Metodo Pago: ") + metodoPago);

    linea("------------------------------------");
    linea("PRODUCTOS", 14);
    linea("------------------------------------");

    for (int i = 0; i < carritoVenta.size(); i++) {

        string producto =
            carritoVenta[i].nombre
            + " x"
            + to_string(carritoVenta[i].cantidad)
            + "  Q "
            + to_string(carritoVenta[i].subtotal);

        linea(producto);
    }

    linea("------------------------------------");

    linea(
        "TOTAL: Q "
        + to_string(total),
        14
    );

    linea(
        "PAGO: Q "
        + to_string(pago)
    );

    linea(
        "CAMBIO: Q "
        + to_string(cambio)
    );

    linea("------------------------------------");
    linea("Gracias por su compra", 12);
    linea("Vuelva pronto", 12);

    string stream = contenido.str();

    pdf << "%PDF-1.4\n";
    pdf << "1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj\n";
    pdf << "2 0 obj << /Type /Pages /Kids [3 0 R] /Count 1 >> endobj\n";
    pdf << "3 0 obj << /Type /Page /Parent 2 0 R "
        << "/MediaBox [0 0 320 850] "
        << "/Contents 4 0 R "
        << "/Resources << /Font << /F1 5 0 R >> >> >> endobj\n";

    pdf << "4 0 obj << /Length "
        << stream.size()
        << " >> stream\n";

    pdf << stream;

    pdf << "endstream endobj\n";

    pdf << "5 0 obj << /Type /Font "
        << "/Subtype /Type1 "
        << "/BaseFont /Helvetica >> endobj\n";

    pdf << "xref\n0 6\n";
    pdf << "0000000000 65535 f \n";
    pdf << "trailer << /Root 1 0 R /Size 6 >>\n";
    pdf << "startxref\n0\n%%EOF";

    pdf.close();

    string comando =
        "start \"\" \"" +
        string(nombreArchivo) +
        "\"";

    system(comando.c_str());
}