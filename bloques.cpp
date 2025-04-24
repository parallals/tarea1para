#include <iostream>
#include <vector>

using namespace std;


void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int** createMatrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) { //Matriz 2dimensional !!!
        matrix[i] = new int[n];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** add(int** matrix, int** matrix2, int n) {
    int** C = createMatrix(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = matrix[i][j] + matrix2[i][j];
    return C;
}


int** block(int** matrix, int** matrix2, int n) {
    
    if (n == 1) {
        int** result = createMatrix(1); // Crear una matriz de 1x1
        result[0][0] = matrix[0][0] * matrix2[0][0];
        return result;
    }

    int mitad = n / 2; //Divide el tamanyo máximo de la matriz en la mitad, y como es cuadrada,"La parte en 4"
     
    int** A11 = createMatrix(mitad); //Todas las matrices son de n/2 x n/2
    int** A12 = createMatrix(mitad);
    int** A21 = createMatrix(mitad);
    int** A22 = createMatrix(mitad);
    int** B11 = createMatrix(mitad);
    int** B12 = createMatrix(mitad);
    int** B21 = createMatrix(mitad);
    int** B22 = createMatrix(mitad);

    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            A11[i][j] = matrix[i][j];
            A12[i][j] = matrix[i][j  + mitad];
            A21[i][j] = matrix[i+ mitad][j];
            A22[i][j] = matrix[i + mitad][j + mitad];
            B11[i][j] = matrix2[i][j];
            B12[i][j] = matrix2[i ][j + mitad];
            B21[i][j] = matrix2[i+ mitad][j ];
            B22[i][j] = matrix2[i + mitad][j + mitad];
        }
    }


    int** M1 = strassen(add(A11, A22, mitad), add(B11, B22, mitad), mitad);
    int** M2 = strassen(add(A21, A22, mitad), B11, mitad);
    int** M3 = strassen(A11, subtract(B12,B22,mitad), mitad);
    int** M4 = strassen(A22, subtract(B21,B11,mitad), mitad);
    int** M5 = strassen(add(A11, A12,mitad), B22, mitad);
    int** M6 = strassen(subtract(A21, A11, mitad), add(B11, B12, mitad), mitad);
    int** M7 = strassen(subtract(A12, A22, mitad), add(B21, B22, mitad), mitad);
    //Operaciones extra
    int** M8 = subtract((add(M1,M4,mitad)),M5,mitad); // M1 + M4 - M5
    int** M9 = add((subtract(M1,M2,mitad)),M3,mitad); // M1 - M2 + M3

    int** C11 =  add(M8, M7, mitad);
    int** C12 = add(M3,M5,mitad);
    int** C21 = add(M2,M4,mitad);
    int** C22 = add(M9,M6,mitad);

    int** C = createMatrix(n); //Rellenamos C de cuarto en cuarto
    for (int i = 0; i < mitad; ++i){
        for(int j = 0; j < mitad; ++j){
            C[i][j] = C11[i][j];
            C[i ][j+ mitad] = C12[i][j];
            C[i+ mitad][j ] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }
    }

    deleteMatrix(A11, mitad);
    deleteMatrix(A12, mitad);
    deleteMatrix(A21, mitad);
    deleteMatrix(A22, mitad);
    deleteMatrix(B11, mitad);
    deleteMatrix(B12, mitad);
    deleteMatrix(B21, mitad);
    deleteMatrix(B22, mitad);
    deleteMatrix(M1, mitad);
    deleteMatrix(M2, mitad);
    deleteMatrix(M3, mitad);
    deleteMatrix(M4, mitad);
    deleteMatrix(M5, mitad);
    deleteMatrix(M6, mitad);
    deleteMatrix(M7, mitad);
    deleteMatrix(M8, mitad);
    deleteMatrix(M9, mitad);
    deleteMatrix(C11, mitad);
    deleteMatrix(C12, mitad);
    deleteMatrix(C21, mitad);
    deleteMatrix(C22, mitad);

    return C;
}


int main() {
    cout<< "Ingrese el tamanyo de las matrices: "<<endl;
    int n;
    cin >> n ;
    int tpot = n & (n-1);

    if(tpot != 0){
        cout << "El tamanyo de la matriz no es potencia de 2" << endl;
        return 0;
    }

    int** A = createMatrix(n);
    int** B = createMatrix(n);
    //Modo manual
    /*
    cout<< "Ingrese la matriz A: "<<endl;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> A[i][j];
        }
    }
    cout<< "Ingrese la matriz B: "<<endl;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
        cin >> B[i][j];
        }
    }*/

    //automatico
    int x = 1;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){

            A[i][j] = x;
            ++x;
        }
    }

    x = 1;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){

            B[i][j] = x;
            ++x;
        }
    }
    int** C = strassen(A, B, n);
    printMatrix(C, n);
    return 0;
}