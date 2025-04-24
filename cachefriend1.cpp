#include <iostream>

int main() {
    int rows1 = 100, cols1 = 430, rows2 = 430, cols2 = 300;

    // Paso 1: Pide una sola porción de memoria de tamaño rows*cols 
    // y usa un puntero, matrix apunta al primer elemento de la mem
    int* matrix = new int[rows1 * cols1];
    int* matrix2 = new int[rows2 * cols2];
    int* producto = new int[rows1 * cols2]; 

    // Paso 2: usa los indices i y j para decir que elemento quiere identificar 
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix[i * cols1 + j] = (i + 1) * (j + 1); 
        }
    }

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i * cols2 + j] = (i + 1) * (j + 1); 
        }
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            producto[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; k++) {
                producto[i * cols2 + j] += matrix[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
/*
    // imprime el resultado
    std::cout << "Producto de matrices:" << std::endl;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            std::cout << producto[i * cols2 + j] << " ";
        }
        std::cout << std::endl;
    } 
*/

    // Paso 4: libera la memoria solicitada 
    delete[] matrix,matrix2,producto;

    return 0;
}

