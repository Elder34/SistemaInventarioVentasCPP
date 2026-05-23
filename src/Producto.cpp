#include "Producto.h"

Producto::Producto() {
    id = 0;
    nombre = "";
    precio = 0;
    stock = 0;
    categoria = "";
}

Producto::Producto(int id, string nombre, float precio, int stock, string categoria) {
    this->id = id;
    this->nombre = nombre;
    this->precio = precio;
    this->stock = stock;
    this->categoria = categoria;
}

int Producto::getId() { return id; }
string Producto::getNombre() { return nombre; }
float Producto::getPrecio() { return precio; }
int Producto::getStock() { return stock; }
string Producto::getCategoria() { return categoria; }

void Producto::setNombre(string nombre) {
    this->nombre = nombre;
}

void Producto::setPrecio(float precio) {
    this->precio = precio;
}

void Producto::setStock(int stock) {
    this->stock = stock;
}

void Producto::setCategoria(string categoria) {
    this->categoria = categoria;
}