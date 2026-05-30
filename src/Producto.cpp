#include "Producto.h"

// Constructor vacío de la clase Producto
// Inicializa los atributos con valores por defecto
Producto::Producto() {
    id = 0;
    nombre = "";
    precio = 0;
    stock = 0;
    categoria = "";
}

// Constructor con parámetros
// Permite crear un producto con datos específicos
Producto::Producto(int id, string nombre, float precio, int stock, string categoria) {

    // this-> se usa para diferenciar los atributos del objeto
    // de las variables recibidas como parámetros
    this->id = id;
    this->nombre = nombre;
    this->precio = precio;
    this->stock = stock;
    this->categoria = categoria;
}

// ===== MÉTODOS GET =====
// Sirven para obtener o consultar los datos del producto

// Retorna el ID del producto
int Producto::getId() {
    return id;
}

// Retorna el nombre del producto
string Producto::getNombre() {
    return nombre;
}

// Retorna el precio del producto
float Producto::getPrecio() {
    return precio;
}

// Retorna el stock disponible
int Producto::getStock() {
    return stock;
}

// Retorna la categoría del producto
string Producto::getCategoria() {
    return categoria;
}

// ===== MÉTODOS SET =====
// Sirven para modificar los datos del producto

// Modifica el nombre del producto
void Producto::setNombre(string nombre) {
    this->nombre = nombre;
}

// Modifica el precio del producto
void Producto::setPrecio(float precio) {
    this->precio = precio;
}

// Modifica la cantidad en stock
void Producto::setStock(int stock) {
    this->stock = stock;
}

// Modifica la categoría del producto
void Producto::setCategoria(string categoria) {
    this->categoria = categoria;
}