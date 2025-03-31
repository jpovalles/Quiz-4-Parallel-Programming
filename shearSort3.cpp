#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <omp.h>
using namespace std;

void initialize(vector<vector<int>> &matrix){
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

void sortRow(vector<vector<int>> &matrix, int row, bool asc = true){
    for (int i = 0; i < matrix[0].size(); i++) {
        for (int j = i + 1; j < matrix[0].size(); j++) {
            if ((matrix[row][i] > matrix[row][j] && asc) ||(matrix[row][i] < matrix[row][j] && !asc)) {
                swap(matrix[row][i], matrix[row][j]);
            }
        }
    }
}

void sortColumn(vector<vector<int>> &matrix, int column){
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix.size(); j++) {
            if (matrix[i][column] > matrix[j][column]) {
                swap(matrix[i][column], matrix[j][column]);
            }
        }
    }
}

void transpose(vector<vector<int>> &matrix){
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix.size(); j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void searShort(int n, vector<vector<int>> &matrix){
    int its = ceil(log2(n))+1;

    for(int k = 0; k < its; k++){
        
        for (int i = 0; i < n; i++) {
        sortRow(matrix, i, i % 2 == 0);
        }
        
        for (int i = 0; i < n; i++) {
            sortColumn(matrix, i);
        }
    }
}

void printMatrix(vector<vector<int>> &matrix){
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void altsearShort(int n, vector<vector<int>> &matrix){
    int its = ceil(log2(n))+1;

    for(int k = 0; k < its; k++){               // O(log(n)) 
        for (int i = 0; i < n; i++) {           // O(n^3)
            sortRow(matrix, i, i % 2 == 0);
        }

        transpose(matrix);                      // O(n^2)

        for (int i = 0; i < n; i++) {           // O(n^3)
            sortRow(matrix, i, true);
        }   

        transpose(matrix);                      // O(n^2)
    }
}

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    int n = atoi(argv[1]);

    vector<vector<int>> matrix(n, vector<int>(n));
    initialize(matrix);

    cout << "Original matrix: " << endl;
    printMatrix(matrix);

    altsearShort(n, matrix);

    cout << "Sorted matrix: " << endl;
    printMatrix(matrix);
    
    return 0;
}