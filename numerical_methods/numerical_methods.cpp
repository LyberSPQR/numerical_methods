#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

void extendedMatrixOutput(vector<vector<double>> extendedMatrix, const int N);

int main() {
    setlocale(LC_ALL, "ru");

    int arrSize, vecSize;
    cout << "Введите размер матрицы и вектора" << endl;
    cin >> arrSize;
    vecSize = arrSize;

    vector<vector<double>> extendedMatrix(arrSize, vector<double>(arrSize));

    extendedMatrix = { {+2.5, -3.0, 4.6, -1.05},
                      {-3.5, 2.6, 1.5, -14.46},
                      {-6.5, -3.5, 7.3, -17.73} };

    vector<double> vec(vecSize);
    vector<double> vec1(vecSize);

    // Сохранение оригинальной матрицы A и вектора b
    vector<vector<double>> originalMatrix = extendedMatrix;
    vector<double> originalB(vecSize);
    for (int i = 0; i < arrSize; i++) {
        originalB[i] = extendedMatrix[i][arrSize];
    }

    cout << "Матрица:" << endl;
    extendedMatrixOutput(extendedMatrix, arrSize);

    for (int g = 0; g < arrSize; g++) {
        double maxElement = extendedMatrix[g][g];
        int maxRow = g;
        for (int j = g; j < arrSize; j++) {
            if (abs(extendedMatrix[j][g]) > abs(maxElement)) {
                maxElement = extendedMatrix[j][g];
                maxRow = j;
            }
        }

        // SWAP
        if (maxRow != g) {
            swap(extendedMatrix[g], extendedMatrix[maxRow]);
        }

        cout << "Матрица после смены:" << endl;
        extendedMatrixOutput(extendedMatrix, arrSize);

        if (extendedMatrix[g][g] == 0) {
            cout << "IER = 1";
            return 0;
        }

        for (int i = 0 + g; i < arrSize; i++) {
            double temp = extendedMatrix[i][g];
            if (temp != 0) {
                for (int j = 0 + g; j < arrSize + 1; j++) {
                    extendedMatrix[i][j] = extendedMatrix[i][j] / temp;
                }
            }
        }

        for (int i = 1 + g; i < arrSize; i++) {
            for (int j = 0 + g; j < arrSize + 1; j++) {
                extendedMatrix[i][j] = extendedMatrix[i][j] - extendedMatrix[g][j];
            }
        }

        extendedMatrixOutput(extendedMatrix, arrSize);

        for (int i = 0; i < arrSize; i++) {
            if (i != g) {
                double factor = extendedMatrix[i][g];
                for (int j = g; j < arrSize + 1; j++) {
                    extendedMatrix[i][j] -= factor * extendedMatrix[g][j];
                }
            }
        }

        extendedMatrixOutput(extendedMatrix, arrSize);
        cout << endl << "end of cycle " << g + 1 << endl << endl;
    }

    for (int i = 0; i < arrSize; i++) {
        vec1[i] = extendedMatrix[i][arrSize];
    }

    cout << "Решение (x): ";
    for (int i = 0; i < vecSize; i++) {
        cout << vec1[i] << " ";
    }
    cout << endl;

    // Вычисление вектора невязки F = A * x - b
    vector<double> residual(vecSize, 0.0);
    for (int i = 0; i < arrSize; i++) {
        double sum = 0.0;
        for (int j = 0; j < arrSize; j++) {
            sum += originalMatrix[i][j] * vec1[j];
        }
        residual[i] = sum - originalB[i];
    }

    // Вывод вектора невязки
    cout << "\nВектор невязки F: ";
    for (double r : residual) {
        cout << r << " ";
    }
    cout << endl;

    // Вычисление нормы вектора невязки
    double norm = 0.0;
    for (double r : residual) {
        norm += r * r;
    }
    norm = sqrt(norm);
    cout << "Норма вектора невязки ||F||: " << norm << endl;

    // Вычисление относительной погрешности δ
    double maxDelta = 0.0, maxVec1 = 0.0;
    for (int i = 0; i < vecSize; i++) {
        maxDelta = max(maxDelta, abs(originalB[i] - vec1[i]));
        maxVec1 = max(maxVec1, abs(vec1[i]));
    }

    double relativeError = maxDelta / maxVec1;
    cout << "Относительная погрешность (Delta): " << relativeError << endl;

    return 0;
}

void extendedMatrixOutput(vector<vector<double>> extendedMatrix, const int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            cout << extendedMatrix[i][j] << left << setw(12);
        }
        cout << endl;
    }
    cout << endl << endl;
}
