#include <iostream>
#include <chrono>

// Define the number of columns for the second matrix
using namespace std;
int main() {
    int rows1 = 100, cols1 = 430, rows2 = 430, cols2 = 300;     

    // Paso 1: Pide memoria dinámica para un arreglo de punteros a filas
    // esto usa una representacion 2D
    int** matrix = new int*[rows1];
    int** matrix2 = new int*[rows2];
    int** producto = new int*[rows1];
    // Paso 2: Pide memoria para cada arreglo de fila
     
    for (int i = 0; i < rows1; i++) {
        matrix[i] = new int[cols1];
    }
    for (int i = 0; i < rows2; i++) {
        matrix2[i] = new int[cols2];
    }                               
    for (int i = 0; i < rows1; i++) {
        producto[i] = new int[cols2];
    }



    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix[i][j] = (i + 1) * (j + 1); // segun lo que necesite 
        }
    }

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = (i + 1) * (j + 1); // segun lo que necesite 
        }
    }

    auto start_mult = chrono::steady_clock::now();

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            producto[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                producto[i][j] += matrix[i][k] * matrix2[k][j];
            }
        }
    }

    auto end_mult = chrono::steady_clock::now();
    auto diff_mult = end_mult - start_mult;
    cout << "Tiempo de multiplicacion: " << chrono::duration<double, milli>(diff_mult).count() << " ms" << endl;
    
    /*
    //Imprimir matrices
    cout << "Matrix 1:" << endl;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix 2:" << endl;
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Producto:" << endl;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            cout << producto[i][j] << " ";
        }
        cout << endl;
    }*/

    // Paso 3: Libera la memoria
    for (int i = 0; i < rows1; i++) {
        delete[] matrix[i];
        delete[] matrix2[i];
        if (i < rows1) delete[] producto[i];
    }
    delete[] matrix;
    delete[] matrix2;
    delete[] producto;

    return 0;
}