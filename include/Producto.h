#pragma once
#include <string>
using namespace std;

class Producto {
private:
    int id;
    string nombre;
    float precio;
    int stock;
    string categoria;

public:
    Producto();
    Producto(int id, string nombre, float precio, int stock, string categoria);

    int getId() const;
    string getNombre() const;
    float getPrecio() const;
    int getStock() const;
    string getCategoria() const;

    void setNombre(string nombre);
    void setPrecio(float precio);
    void setStock(int stock);
    void setCategoria(string categoria);
};