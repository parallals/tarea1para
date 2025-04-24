#include <iostream>
#include <chrono>
using namespace std;

int main() {
    int rows1 = 2, cols1 = 2, rows2 = 2, cols2 = 2;

    for(int i = 0; i < 10 ; i++){ //10 iteraciones
        // Paso 1: Pide una sola porción de memoria de tamaño rows*cols 
        // y usa un puntero, matrix apunta al primer elemento de la mem
        int* matrix = new int[rows1 * cols1];
        int* matrix2 = new int[rows2 * cols2];
        int* producto = new int[rows1 * cols2]; 
        // Llenar matrix y matrix2 para medir el tiempo

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols1; j++) {
            matrix[i * cols1 + j] = 3;
            }
        }

        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < cols2; j++) {
            matrix2[i * cols2 + j] = 3;
            }
        }

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
        
        // Multiplicar matrices, tiempo de ejecución
        double duration = 0;
        for(int i = 0; i<10; i++){ //Repeticion de 10 la suma, luego calcular promedio, para eliminar ruido 
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < cols2; j++) {
                    producto[i * cols2 + j] = 0;
                    for (int k = 0; k < cols1; k++) {
                        producto[i * cols2 + j] += matrix[i * cols1 + k] * matrix2[k * cols2 + j];
                    }
                }
            }
            auto finish = chrono::high_resolution_clock::now();
            auto d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
            duration += d;
        }
    // Imprimir csv, variables 'Numero elementos'- 'Tiempo promedio'
    cout << rows1 << "," << int(duration / 100) << std::endl;
    duration = 0;
    // Paso 4: libera la memoria solicitada 
        delete[] matrix,matrix2,producto;
        rows1 *= 2;
        cols1 *= 2;
        rows2 *= 2;
        cols2 *= 2;
    }

    return 0;
}

