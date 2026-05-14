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

    idEliminarCliente = 0;
}

void AppUI::ejecutar() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sistema Inventario y Ventas", NULL, NULL);
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

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

            if (mostrarProductos) {
                mostrarModuloProductos();
            }
            if (mostrarClientes) {
                mostrarModuloClientes();
            }
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
    ImGui::SetNextWindowSize(ImVec2(420, 260));
    ImGui::SetNextWindowPos(ImVec2(430, 200), ImGuiCond_Once);

    ImGui::Begin("Login - Sistema de Inventario", NULL, ImGuiWindowFlags_NoResize);

    ImGui::Text("Sistema de Inventario y Ventas");
    ImGui::Separator();

    ImGui::InputText("Usuario", usuario, IM_ARRAYSIZE(usuario));
    ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Ingresar", ImVec2(120, 35))) {
        if (login.validarUsuario(usuario, password)) {
            loginCorrecto = true;
            strcpy_s(mensajeLogin, "");
        }
        else {
            strcpy_s(mensajeLogin, "Usuario o password incorrectos");
        }
    }

    if (strlen(mensajeLogin) > 0) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), mensajeLogin);
    }

    ImGui::End();
}

void AppUI::mostrarMenuPrincipal() {
    ImGui::SetNextWindowSize(ImVec2(300, 350));
    ImGui::SetNextWindowPos(ImVec2(30, 80), ImGuiCond_Once);

    ImGui::Begin("Menu Principal");

    ImGui::Text("Bienvenido al sistema");
    ImGui::Separator();

    if (ImGui::Button("Productos", ImVec2(180, 40))) {
        mostrarProductos = true;
    }

    if (ImGui::Button("Clientes", ImVec2(180, 40))) {
        mostrarClientes = true;
    }

    if (ImGui::Button("Ventas", ImVec2(180, 40))) {
    }

    if (ImGui::Button("Inventario", ImVec2(180, 40))) {
    }

    if (ImGui::Button("Cerrar sesion", ImVec2(180, 40))) {
        loginCorrecto = false;
        mostrarProductos = false;
        strcpy_s(usuario, "");
        strcpy_s(password, "");
    }

    ImGui::End();
}

void AppUI::mostrarModuloProductos() {
    ImGui::SetNextWindowSize(ImVec2(820, 560));
    ImGui::SetNextWindowPos(ImVec2(370, 80), ImGuiCond_Once);

    ImGui::Begin("Modulo Productos", &mostrarProductos);

    ImGui::Text("CRUD de Productos");
    ImGui::Separator();

    ImGui::InputText("Nombre", nombreProducto, IM_ARRAYSIZE(nombreProducto));
    ImGui::InputFloat("Precio", &precioProducto);
    ImGui::InputInt("Stock", &stockProducto);
    ImGui::InputText("Categoria", categoriaProducto, IM_ARRAYSIZE(categoriaProducto));

    if (ImGui::Button("Agregar Producto", ImVec2(160, 35))) {
        if (strlen(nombreProducto) > 0 && precioProducto > 0 && stockProducto >= 0) {
            productoDAO.agregarProducto(nombreProducto, precioProducto, stockProducto, categoriaProducto);

            strcpy_s(nombreProducto, "");
            strcpy_s(categoriaProducto, "");
            precioProducto = 0.0f;
            stockProducto = 0;
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Limpiar", ImVec2(100, 35))) {
        strcpy_s(nombreProducto, "");
        strcpy_s(categoriaProducto, "");
        precioProducto = 0.0f;
        stockProducto = 0;
    }

    ImGui::Separator();

    if (ImGui::BeginTable("tabla_productos", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Nombre");
        ImGui::TableSetupColumn("Precio");
        ImGui::TableSetupColumn("Stock");
        ImGui::TableSetupColumn("Categoria");
        ImGui::TableHeadersRow();

        vector<Producto> productos = productoDAO.obtenerProductos();

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
        }

        ImGui::EndTable();
    }

    ImGui::Separator();

    ImGui::InputInt("ID a eliminar", &idEliminar);

    if (ImGui::Button("Eliminar Producto", ImVec2(160, 35))) {
        productoDAO.eliminarProducto(idEliminar);
        idEliminar = 0;
    }

    ImGui::End();
}
void AppUI::mostrarModuloClientes() {

    ImGui::SetNextWindowSize(ImVec2(820, 560));
    ImGui::SetNextWindowPos(ImVec2(370, 80), ImGuiCond_Once);

    ImGui::Begin("Modulo Clientes", &mostrarClientes);

    ImGui::Text("CRUD de Clientes");
    ImGui::Separator();

    ImGui::InputText("Nombre", nombreCliente, IM_ARRAYSIZE(nombreCliente));
    ImGui::InputText("Telefono", telefonoCliente, IM_ARRAYSIZE(telefonoCliente));
    ImGui::InputText("Correo", correoCliente, IM_ARRAYSIZE(correoCliente));

    if (ImGui::Button("Agregar Cliente", ImVec2(160, 35))) {

        if (strlen(nombreCliente) > 0) {

            clienteDAO.agregarCliente(
                nombreCliente,
                telefonoCliente,
                correoCliente
            );

            strcpy_s(nombreCliente, "");
            strcpy_s(telefonoCliente, "");
            strcpy_s(correoCliente, "");
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Limpiar", ImVec2(100, 35))) {

        strcpy_s(nombreCliente, "");
        strcpy_s(telefonoCliente, "");
        strcpy_s(correoCliente, "");
    }

    ImGui::Separator();

    vector<Cliente> clientes = clienteDAO.obtenerClientes();

    if (ImGui::BeginTable("tabla_clientes", 4,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg)) {

        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Nombre");
        ImGui::TableSetupColumn("Telefono");
        ImGui::TableSetupColumn("Correo");

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
        }

        ImGui::EndTable();
    }

    ImGui::Separator();

    ImGui::InputInt("ID Cliente", &idEliminarCliente);

    if (ImGui::Button("Eliminar Cliente", ImVec2(160, 35))) {

        clienteDAO.eliminarCliente(idEliminarCliente);

        idEliminarCliente = 0;
    }

    ImGui::End();
}