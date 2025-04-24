#include <iostream>
#include <chrono>
#include <omp.h> // Include OpenMP header

using namespace std;

int main() {
    int rows1 = 100, cols1 = 430, rows2 = 430, cols2 = 300;

    int** matrix = new int*[rows1];
    int** matrix2 = new int*[rows2];
    int** producto = new int*[rows1];

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
            matrix[i][j] = (i + 1) * (j + 1);
        }
    }

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = (i + 1) * (j + 1);
        }
    }

    auto start_mult = chrono::steady_clock::now();

    #pragma omp parallel default(none) shared(matrix, matrix2, producto, rows1, cols1, cols2)
    {
        #pragma omp for
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                producto[i][j] = 0;
            }
        }
    }
    #pragma omp parallel default(none) shared(matrix, matrix2, producto, rows1, cols1, cols2)
    {
        #pragma omp for
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                int sum = 0;
                for (int k = 0; k < cols1; k++) {
                    sum += matrix[i][k] * matrix2[k][j];
                }
                producto[i][j] = sum;
            }
        }
    }

    auto end_mult = chrono::steady_clock::now();
    auto diff_mult = end_mult - start_mult;
    cout << "Tiempo de multiplicacion: " << chrono::duration<double, milli>(diff_mult).count() << " ms" << endl;

    // Free memory
    for (int i = 0; i < rows1; i++) {
        delete[] matrix[i];
        delete[] producto[i];
    }
    for (int i = 0; i < rows2; i++) {
        delete[] matrix2[i];
    }
    delete[] matrix;
    delete[] matrix2;
    delete[] producto;

    return 0;
}
