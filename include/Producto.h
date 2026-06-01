// Permite almacenar y manipular la información de los productos registrados.

#pragma once
#include <string>

using namespace std;

class Producto {
private:

    // Atributos del producto
    int id;
    string codigo;
    string nombre;
    float precio;
    int stock;
    string categoria;

public:

    // Constructores
    // Permiten crear objetos producto vacíos o con información completa.
    Producto();

    Producto(
        int id,
        string codigo,
        string nombre,
        float precio,
        int stock,
        string categoria
    );

    // Métodos GET
    // Permiten consultar la información del producto.
    int getId();
    string getCodigo();
    string getNombre();
    float getPrecio();
    int getStock();
    string getCategoria();

    // Métodos SET
    // Permiten modificar los datos del producto.
    void setCodigo(string codigo);
    void setNombre(string nombre);
    void setPrecio(float precio);
    void setStock(int stock);
    void setCategoria(string categoria);
};