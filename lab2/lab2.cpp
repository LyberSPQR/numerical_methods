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
double f1(double x, double y);
double f2(double x, double y);
double df1_dx(double x, double y);
double df1_dy(double x, double y);
double df2_dx(double x, double y);
double df2_dy(double x, double y);
double df_dx(double (*func)(double, double), double x, double y, double delta);
double df_dy(double (*func)(double, double), double x, double y, double delta);
void solveLinearSystem(double J[2][2], double F[2], double delta[2]);

int main() {
    setlocale(LC_ALL, "ru");
    // Начальное приближение
    double x = 4.0, y = 2.0;
    double delta[2];
    int iter = 0;
    double normF, normDelta;

    // Установка формата вывода
    cout << fixed << setprecision(6);
    cout << "Итерация\tX\t\tY\t\t|F|\t\t|Delta|\n";

    while (iter < NIT) {
        // Вычисление функции невязки
        double F[2] = { -f1(x, y), -f2(x, y) };

        // Вычисление нормы невязки
        normF = sqrt(F[0] * F[0] + F[1] * F[1]);

        // Проверка критерия сходимости по невязке
        if (normF < eps1) {
            cout << "Решение достигнуто по критерию невязки.\n";
            break;
        }

        // Вычисление матрицы Якоби
        double J[2][2];

        // Способ 1: Аналитически
        J[0][0] = df1_dx(x, y);
        J[0][1] = df1_dy(x, y);
        J[1][0] = df2_dx(x, y);
        J[1][1] = df2_dy(x, y);

        // Способ 2: Численно (раскомментируйте, чтобы использовать численный способ)
        // double deltaM = 1e-5;
        // J[0][0] = df_dx(f1, x, y, deltaM);
        // J[0][1] = df_dy(f1, x, y, deltaM);
        // J[1][0] = df_dx(f2, x, y, deltaM);
        // J[1][1] = df_dy(f2, x, y, deltaM);

        // Решаем систему для поправки
        solveLinearSystem(J, F, delta);

        // Уточняем решение
        x += delta[0];
        y += delta[1];

        // Вычисление нормы шага
        normDelta = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

        // Вывод результатов текущей итерации
        cout << iter + 1 << "\t\t" << x << "\t" << y << "\t" << normF << "\t" << normDelta << "\n";

        // Проверка критерия сходимости по шагу
        if (normDelta < eps2) {
            cout << "Решение достигнуто по критерию шага.\n";
            break;
        }

        iter++;
    }

    if (iter == NIT) {
        cout << "Превышено максимальное количество итераций.\n";
    }
    else {
        cout << "Решение: X = " << x << ", Y = " << y << "\n";
    }

    return 0;
}

// Определения функций

double f1(double x, double y) {
    return x * x + y * y - 4; // Пример функции f1(x, y) = x^2 + y^2 - 4 = 0
}

double f2(double x, double y) {
    return x * y - 1; // Пример функции f2(x, y) = x * y - 1 = 0
}

double df1_dx(double x, double y) {
    return 2 * x;
}

double df1_dy(double x, double y) {
    return 2 * y;
}

double df2_dx(double x, double y) {
    return y;
}

double df2_dy(double x, double y) {
    return x;
}

// Численное вычисление Якобиана методом конечных разностей
double df_dx(double (*func)(double, double), double x, double y, double delta) {
    return (func(x + delta, y) - func(x, y)) / delta;
}

double df_dy(double (*func)(double, double), double x, double y, double delta) {
    return (func(x, y + delta) - func(x, y)) / delta;
}

// Функция для решения системы линейных уравнений методом Крамера
void solveLinearSystem(double J[2][2], double F[2], double delta[2]) {
    double detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];
    if (fabs(detJ) < 1e-12) {
        throw runtime_error("Якобиан вырожден.");
    }
    delta[0] = (F[0] * J[1][1] - F[1] * J[0][1]) / detJ;
    delta[1] = (J[0][0] * F[1] - J[1][0] * F[0]) / detJ;
}
