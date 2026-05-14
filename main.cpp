#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct Producto
{
    int id;
    string nombre;
    float precio;
    int stock;
    string categoria;
};

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sistema Inventario y Ventas", NULL, NULL);
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool loginCorrecto = false;
    bool mostrarProductos = false;

    char usuario[50] = "";
    char password[50] = "";
    string mensajeLogin = "";

    vector<Producto> productos;

    int idProducto = 1;
    char nombreProducto[100] = "";
    char categoriaProducto[100] = "";
    float precioProducto = 0.0f;
    int stockProducto = 0;

    int idEliminar = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (!loginCorrecto)
        {
            ImGui::SetNextWindowSize(ImVec2(420, 260));
            ImGui::SetNextWindowPos(ImVec2(430, 200), ImGuiCond_Once);

            ImGui::Begin("Login - Sistema de Inventario", NULL, ImGuiWindowFlags_NoResize);

            ImGui::Text("Sistema de Inventario y Ventas");
            ImGui::Separator();

            ImGui::InputText("Usuario", usuario, IM_ARRAYSIZE(usuario));
            ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

            if (ImGui::Button("Ingresar", ImVec2(120, 35)))
            {
                if (strcmp(usuario, "admin") == 0 && strcmp(password, "1234") == 0)
                {
                    loginCorrecto = true;
                    mensajeLogin = "";
                }
                else
                {
                    mensajeLogin = "Usuario o password incorrectos";
                }
            }

            if (!mensajeLogin.empty())
            {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), mensajeLogin.c_str());
            }

            ImGui::End();
        }
        else
        {
            ImGui::SetNextWindowSize(ImVec2(300, 350));
            ImGui::SetNextWindowPos(ImVec2(30, 80), ImGuiCond_Once);

            ImGui::Begin("Menu Principal");

            ImGui::Text("Bienvenido al sistema");
            ImGui::Separator();

            if (ImGui::Button("Productos", ImVec2(180, 40)))
            {
                mostrarProductos = true;
            }

            if (ImGui::Button("Clientes", ImVec2(180, 40)))
            {
            }

            if (ImGui::Button("Ventas", ImVec2(180, 40)))
            {
            }

            if (ImGui::Button("Inventario", ImVec2(180, 40)))
            {
            }

            if (ImGui::Button("Cerrar sesion", ImVec2(180, 40)))
            {
                loginCorrecto = false;
                mostrarProductos = false;
                strcpy_s(usuario, "");
                strcpy_s(password, "");
            }

            if (ImGui::Button("Salir", ImVec2(180, 40)))
            {
                glfwSetWindowShouldClose(window, true);
            }

            ImGui::End();

            if (mostrarProductos)
            {
                ImGui::SetNextWindowSize(ImVec2(820, 560));
                ImGui::SetNextWindowPos(ImVec2(370, 80), ImGuiCond_Once);

                ImGui::Begin("Modulo Productos", &mostrarProductos);

                ImGui::Text("CRUD de Productos");
                ImGui::Separator();

                ImGui::InputText("Nombre", nombreProducto, IM_ARRAYSIZE(nombreProducto));
                ImGui::InputFloat("Precio", &precioProducto);
                ImGui::InputInt("Stock", &stockProducto);
                ImGui::InputText("Categoria", categoriaProducto, IM_ARRAYSIZE(categoriaProducto));

                if (ImGui::Button("Agregar Producto", ImVec2(160, 35)))
                {
                    if (strlen(nombreProducto) > 0 && precioProducto > 0 && stockProducto >= 0)
                    {
                        Producto nuevo;
                        nuevo.id = idProducto++;
                        nuevo.nombre = nombreProducto;
                        nuevo.precio = precioProducto;
                        nuevo.stock = stockProducto;
                        nuevo.categoria = categoriaProducto;

                        productos.push_back(nuevo);

                        strcpy_s(nombreProducto, "");
                        strcpy_s(categoriaProducto, "");
                        precioProducto = 0.0f;
                        stockProducto = 0;
                    }
                }

                ImGui::SameLine();

                if (ImGui::Button("Limpiar", ImVec2(100, 35)))
                {
                    strcpy_s(nombreProducto, "");
                    strcpy_s(categoriaProducto, "");
                    precioProducto = 0.0f;
                    stockProducto = 0;
                }

                ImGui::Separator();

                ImGui::Text("Listado de productos");

                if (ImGui::BeginTable("tabla_productos", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("ID");
                    ImGui::TableSetupColumn("Nombre");
                    ImGui::TableSetupColumn("Precio");
                    ImGui::TableSetupColumn("Stock");
                    ImGui::TableSetupColumn("Categoria");
                    ImGui::TableHeadersRow();

                    for (int i = 0; i < productos.size(); i++)
                    {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%d", productos[i].id);

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("%s", productos[i].nombre.c_str());

                        ImGui::TableSetColumnIndex(2);
                        ImGui::Text("Q %.2f", productos[i].precio);

                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text("%d", productos[i].stock);

                        ImGui::TableSetColumnIndex(4);
                        ImGui::Text("%s", productos[i].categoria.c_str());
                    }

                    ImGui::EndTable();
                }

                ImGui::Separator();

                ImGui::InputInt("ID a eliminar", &idEliminar);

                if (ImGui::Button("Eliminar Producto", ImVec2(160, 35)))
                {
                    for (int i = 0; i < productos.size(); i++)
                    {
                        if (productos[i].id == idEliminar)
                        {
                            productos.erase(productos.begin() + i);
                            idEliminar = 0;
                            break;
                        }
                    }
                }

                ImGui::End();
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

    return 0;
}