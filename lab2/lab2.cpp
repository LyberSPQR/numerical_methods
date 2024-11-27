#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Параметры
const double eps1 = 1e-9; // Точность по невязке
const double eps2 = 1e-9; // Точность по шагу
const int NIT = 100;      // Максимальное количество итераций

// Прототипы функций
double f1(double x, double x_2);
double f2(double x, double x_2);
double df1_dx(double x, double x_2);
double df1_dx_2(double x, double x_2);
double df2_dx(double x, double x_2);
double df2_dx_2(double x, double x_2);
void solveLinearSystem(double J[2][2], double F[2], double delta[2]);
double delta1(const vector<double>& x0);
double delta2(const vector<double>& x0, const vector<double>& xk1);

int main() {
    setlocale(LC_ALL, "ru");
    // Начальное приближение
    vector<double> x0 = { 1.0, 1.0 }; // x0 = (x1, x2)
    vector<double> xk1(2);           // xk1 для хранения нового приближения
    double delta[2];                 // Поправки Δx1, Δx2
    int iter = 0;

    // Установка формата вывода
    cout << fixed << setprecision(6);
    cout << "Итерация\tDelta1\t\tDelta2\n";

    while (iter < NIT) {
        // Вычисление функций невязки
        double F[2] = { -f1(x0[0], x0[1]), -f2(x0[0], x0[1]) };

        // Вычисление матрицы Якоби
        double J[2][2];
        J[0][0] = df1_dx(x0[0], x0[1]);
        J[0][1] = df1_dx_2(x0[0], x0[1]);
        J[1][0] = df2_dx(x0[0], x0[1]);
        J[1][1] = df2_dx_2(x0[0], x0[1]);

        // Решаем систему для поправок Δx1 и Δx2
        solveLinearSystem(J, F, delta);

        // Уточняем новое приближение
        xk1[0] = x0[0] + delta[0];
        xk1[1] = x0[1] + delta[1];

        // Вычисляем delta1 и delta2
        double d1 = delta1(x0);
        double d2 = delta2(x0, xk1);

        // Вывод результатов текущей итерации
        cout << iter + 1 << "\t\t" << d1 << "\t" << d2 << "\n";

        // Проверка критерия завершения
        if (d1 <= eps1 && d2 <= eps2) {
            cout << "Решение достигнуто.\n";
            break;
        }

        // Обновляем x0 для следующей итерации
        x0 = xk1;
        iter++;
    }

    if (iter == NIT) {
        cout << "Превышено максимальное количество итераций.\n";
    }
    else {
        cout << "Решение: X1 = " << x0[0] << ", X2 = " << x0[1] << "\n";
    }

    return 0;
}

// Первая функция
double f1(double x, double x_2) {
    return 1.5 * pow(x, 3) - pow(x_2, 2) - 1;
}

// Вторая функция
double f2(double x, double x_2) {
    return x * pow(x_2, 3) - x_2 - 4;
}

// Частные производные
double df1_dx(double x, double x_2) {
    return 4.5 * pow(x, 2);
}

double df1_dx_2(double x, double x_2) {
    return -2 * x_2;
}

double df2_dx(double x, double x_2) {
    return pow(x_2, 3);
}

double df2_dx_2(double x, double x_2) {
    return 3 * x * pow(x_2, 2) - 1;
}

// Решение системы линейных уравнений методом Крамера
void solveLinearSystem(double J[2][2], double F[2], double delta[2]) {
    // Вычисление определителя Якобиана
    double detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];
    if (fabs(detJ) < 1e-12) {
        throw runtime_error("Якобиан вырожден.");
    }
    delta[0] = (F[0] * J[1][1] - F[1] * J[0][1]) / detJ;
    delta[1] = (J[0][0] * F[1] - J[1][0] * F[0]) / detJ;
}

// Вычисление delta1
double delta1(const vector<double>& x0) {
    double func1 = fabs(f1(x0[0], x0[1]));
    double func2 = fabs(f2(x0[0], x0[1]));
    return max(func1, func2);
}

// Вычисление delta2
double delta2(const vector<double>& x0, const vector<double>& xk1) {
    double maxDelta = 0;
    for (size_t i = 0; i < x0.size(); i++) {
        if (fabs(xk1[i]) < 1) {
            maxDelta = max(maxDelta, fabs(xk1[i] - x0[i]));
        }
        else {
            maxDelta = max(maxDelta, fabs(xk1[i] - x0[i]) / fabs(xk1[i]));
        }
    }
    return maxDelta;
}
