#include "AppUI.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include <cstring>
#include <vector>

using namespace std;

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

    idModificarProducto = 0;
    idBuscarProducto = 0;
    strcpy_s(buscarNombreProducto, "");
    strcpy_s(mensajeProducto, "");
    modoEdicionProducto = false;

    mostrarCortes = false;

}

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


void AppUI::mostrarMenuPrincipal() {

    ImGuiIO& io = ImGui::GetIO();

    float ancho = 1150.0f;
    float alto = 620.0f;

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

    // BOTONES EN UNA SOLA FILA
    if (ImGui::Button("Productos", ImVec2(210, 55))) {
        mostrarProductos = true;
        mostrarClientes = false;
        mostrarCortes = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Clientes", ImVec2(210, 55))) {
        mostrarClientes = true;
        mostrarProductos = false;
        mostrarCortes = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cortes", ImVec2(210, 55))) {
        mostrarCortes = true;
        mostrarProductos = false;
        mostrarClientes = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Inventario", ImVec2(210, 55))) {
        // mostrarInventario = true;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cerrar Sesion", ImVec2(230, 55))) {

        loginCorrecto = false;

        mostrarProductos = false;
        mostrarClientes = false;
        mostrarCortes = false;

        strcpy_s(usuario, "");
        strcpy_s(password, "");
    }

    ImGui::Separator();

    // MODULOS DENTRO DEL MENU (SIN VENTANAS EXTRA)
    if (mostrarProductos)
        mostrarModuloProductos();

    if (mostrarClientes)
        mostrarModuloClientes();

    if (mostrarCortes)
        mostrarModuloCortes();

    ImGui::End();
}
void AppUI::mostrarModuloProductos() {
    ImGui::SetNextWindowSize(ImVec2(1080, 750), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(130, 70), ImGuiCond_Once);

    ImGui::Begin("Modulo Productos", &mostrarProductos);

    ImGui::Text("Gestion de Productos");
    ImGui::Separator();

    ImGui::InputText("Nombre", nombreProducto, IM_ARRAYSIZE(nombreProducto));
    ImGui::InputFloat("Precio", &precioProducto);
    ImGui::InputInt("Stock", &stockProducto);
    ImGui::InputText("Categoria", categoriaProducto, IM_ARRAYSIZE(categoriaProducto));

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

    ImGui::InputInt("Buscar por ID", &idBuscarProducto);

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

    ImGui::SameLine();

    ImGui::InputText("Buscar por nombre", buscarNombreProducto, IM_ARRAYSIZE(buscarNombreProducto));

    ImGui::Separator();

    vector<Producto> productos;

    if (strlen(buscarNombreProducto) > 0) {
        productos = productoDAO.buscarProductosPorNombre(buscarNombreProducto);
    }
    else {
        productos = productoDAO.obtenerProductos();
    }

    if (ImGui::BeginTable("tabla_productos", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
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

            string btnEditar = "Editar##" + to_string(productos[i].getId());

            if (ImGui::Button(btnEditar.c_str(), ImVec2(80, 30))) {

                idModificarProducto = productos[i].getId();

                strcpy_s(nombreProducto, productos[i].getNombre().c_str());

                precioProducto = productos[i].getPrecio();

                stockProducto = productos[i].getStock();

                strcpy_s(categoriaProducto,
                    productos[i].getCategoria().c_str());

                modoEdicionProducto = true;

                strcpy_s(mensajeProducto,
                    "Editando producto seleccionado");
            }

            ImGui::SameLine();

            string btnEliminar = "Eliminar##" +
                to_string(productos[i].getId());

            if (ImGui::Button(btnEliminar.c_str(),
                ImVec2(90, 30))) {

                if (productoDAO.eliminarProducto(
                    productos[i].getId())) {

                    strcpy_s(mensajeProducto,
                        "Producto eliminado correctamente");
                }
                else {

                    strcpy_s(mensajeProducto,
                        "No se pudo eliminar el producto");
                }
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void AppUI::mostrarModuloClientes() {

    ImGui::SetNextWindowSize(ImVec2(1100, 650), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(260, 130), ImGuiCond_Once);

    ImGui::Begin("Modulo Clientes", &mostrarClientes);

    ImGui::Text("CRUD de Clientes");
    ImGui::Separator();

    // FORMULARIO
    ImGui::InputText("Nombre##clienteNombre", nombreCliente, IM_ARRAYSIZE(nombreCliente));
    ImGui::InputText("Telefono##clienteTelefono", telefonoCliente, IM_ARRAYSIZE(telefonoCliente));
    ImGui::InputText("Correo##clienteCorreo", correoCliente, IM_ARRAYSIZE(correoCliente));

    if (!modoEdicionCliente) {
        if (ImGui::Button("Agregar Cliente##btnAgregarCliente", ImVec2(180, 35))) {

            if (strlen(nombreCliente) > 0) {

                clienteDAO.agregarCliente(
                    nombreCliente,
                    telefonoCliente,
                    correoCliente
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

                clienteDAO.actualizarCliente(
                    idModificarCliente,
                    nombreCliente,
                    telefonoCliente,
                    correoCliente
                );

                idModificarCliente = 0;
                modoEdicionCliente = false;

                strcpy_s(nombreCliente, "");
                strcpy_s(telefonoCliente, "");
                strcpy_s(correoCliente, "");

                strcpy_s(mensajeCliente, "Cliente actualizado correctamente");
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

    // BUSQUEDA
    ImGui::Text("Busqueda de clientes");

    ImGui::InputInt("Buscar por ID##buscarClienteID", &idBuscarCliente);

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

    ImGui::InputText("Buscar por nombre##buscarClienteNombre", buscarNombreCliente, IM_ARRAYSIZE(buscarNombreCliente));

    ImGui::Separator();

    // LISTADO
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
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg)) {

        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Nombre");
        ImGui::TableSetupColumn("Telefono");
        ImGui::TableSetupColumn("Correo");
        ImGui::TableSetupColumn(
            "Accion",
            ImGuiTableColumnFlags_WidthFixed,
            230.0f
        );

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

            string btnEditar =
                "Editar##clienteEditar" +
                to_string(clientes[i].getId());

            if (ImGui::Button(btnEditar.c_str(), ImVec2(85, 30))) {

                idModificarCliente = clientes[i].getId();

                strcpy_s(nombreCliente, sizeof(nombreCliente), clientes[i].getNombre().c_str());
                strcpy_s(telefonoCliente, sizeof(telefonoCliente), clientes[i].getTelefono().c_str());
                strcpy_s(correoCliente, sizeof(correoCliente), clientes[i].getCorreo().c_str());

                modoEdicionCliente = true;

                strcpy_s(mensajeCliente, "Editando cliente seleccionado");
            }

            ImGui::SameLine();

            string btnEliminar =
                "Eliminar##clienteEliminar" +
                to_string(clientes[i].getId());

            if (ImGui::Button(btnEliminar.c_str(), ImVec2(100, 30))) {

                clienteDAO.eliminarCliente(clientes[i].getId());

                strcpy_s(mensajeCliente, "Cliente eliminado correctamente");
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}
void AppUI::mostrarModuloCortes() {

    ImGui::Spacing();
    ImGui::Text("Historial de Cortes");
    ImGui::Separator();

    if (ImGui::Button("Cerrar Cortes", ImVec2(180, 35))) {
        mostrarCortes = false;
    }

    ImGui::Spacing();

    vector<Corte> cortes = corteDAO.obtenerCortes();

    if (ImGui::BeginTable(
        "tablaCortes",
        6,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Fecha");
        ImGui::TableSetupColumn("Descripcion");
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
            ImGui::Text("%s", cortes[i].vendedor.c_str());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text("Q %.2f", cortes[i].total);

            ImGui::TableSetColumnIndex(5);

            string btnVer = "Ver##corte" + to_string(cortes[i].id);
            ImGui::Button(btnVer.c_str(), ImVec2(80, 30));
        }

        ImGui::EndTable();
    }
}