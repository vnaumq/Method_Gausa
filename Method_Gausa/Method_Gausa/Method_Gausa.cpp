#include <iostream>
#include <iomanip>
using namespace std;
const int SIZE = 3;

void swap_rows(double(&matrix)[SIZE][SIZE + 1], int row1, int row2) {
    for (int i = 0; i <= SIZE; ++i) {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

void gau(double(&matrix)[SIZE][SIZE + 1], double(&result)[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        int max_row = i;
        for (int j = i + 1; j < SIZE; ++j) {
            if (matrix[j][i] > matrix[max_row][i]) {
                max_row = j;
            }
        }
        swap_rows(matrix, i, max_row);

        for (int j = i + 1; j < SIZE; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= SIZE; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    for (int i = SIZE - 1; i >= 0; --i) {
        result[i] = matrix[i][SIZE];
        for (int j = i + 1; j < SIZE; ++j) {
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }
}


int main() {
    setlocale(LC_ALL, "ru");
    double matrix[SIZE][SIZE + 1] = {
      {6, 13, -17, 2},
      {13, 29, -38, 4},
      {-17, -38, 50, -5}
    };
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE + 1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------" << endl;
    double result[SIZE];
    int o, l;
    int a = matrix[0][0];
    for (int i = 0; i < 3; i++)
    {

        cout << matrix[0][i] << endl;
        if (abs(a) < abs(matrix[0][i]))
        {
            a = matrix[0][i];
            o = i;
        }
    }
    cout << "----------------" << endl;
    cout << a << endl;
    cout << "----------------" << endl;
    swap_rows(matrix, o, 0);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE + 1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------" << endl;
    for (int i = 0; i < 4; i++)
    {

        matrix[0][i] = matrix[0][i] / a;

    }
    cout << "----------------" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE + 1; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    gau(matrix, result);

    cout << "Результат:" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "x" << i + 1 << " = " << result[i] << endl;
    }
    int c = 0;
    for (int i = 0; i < SIZE; i++) {
        c += matrix[0][i];

    }
    cout << "Невязка:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        double residual = 0;
        for (int j = 0; j < SIZE; ++j) {
            residual += matrix[i][j] * result[j];
        }
        residual -= matrix[i][SIZE];
        cout << "Невязка " << i + 1 << ": " << setprecision(25) << residual << endl;
    }
    return 0;
}