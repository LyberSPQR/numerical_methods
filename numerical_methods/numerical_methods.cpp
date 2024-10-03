// numerical_methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
void extendedMatrixOutput(vector<vector<double>> extendedMatrix, const int N);
int main()
{
	setlocale(LC_ALL, "ru");
	const int N = 4, M = 3;
	double l1=0, l2=0, l3=0;
	int n;
	double x, y, z;
	x = 1.71;
	y = 8.64;
	z = 1.71 / 8.64;
	double matrix[M][M] = {8.64,1.71,5.42,
					 -6.39,4.25,1.84,
					 4.21, 7.92,-3.41};
	cout << "Z= " << z << endl;
	cout << "Выберите вариант задания:" << endl << "1 - вариант 6" << endl <<  "2 - вариант 21" << endl << "3 - ввод данных вручную" << endl;
	cin >> n;

	switch (n)
	{
		case 1:
		{
			double matrix[M][M] = {8.64,1.71,5.42,
					 -6.39,4.25,1.84,
					 4.21, 7.92,-3.41};
			vector<double> vec = { 10.21,3.41,12.29 };
		}
		case 3:
		{
			int arrSize,vecSize;
			cout << "Введите размер матрицы" << endl;
			cin >> vecSize;
				
			vector<vector<double>> Matrix(arrSize, vector<double>(arrSize));
				
			vector<double> vec(vecSize);

			for (int i = 0; i < arrSize; i++) // заполнение расширенной матрицы
			{
				for (int j = 0; j < arrSize; j++)
				{
					cin >> Matrix[i][j];
				}
				Matrix[i].push_back(vec[i]);
			}
		}
		break;
		case 2:
		{
			cout << "Введите параметры λ1, λ2, λ3" << endl;
			cin >> l1, l2, l3;
			double matrix[M][M] = { 2*l1 + 4*l2, 2*(l1-l2), 2 * (l1 - l2),
					2 * (l1 - l2), 2*l1+l2+3*l3, 2 * l1 + l2 - 3 * l3,
					2 * (l1 - l2), 2 * l1 + l2 - 3 * l3, 2 * l1 + l2 + 3 * l3 };
			vector<double> vec = { -4*l1-2*l2, -4 * l1 + l2 + 9 * l3, -4 * l1 + l2 - 9 * l3 };
		}
		break;
		default:
		{
			cout << "Введено неверное значение";
			return 0;
		}

	}

	//double matrix[N][N] = {8.64,1.71,5.42,
	//					 -6.39,4.25,1.84,
	//					 4.21, 7.92,-3.41};
	//vector<double> vec = { 10.21,3.41,12.29 };

	/*double matrix[N][N] = { 8.0,4.0,2.0,
						 1.0,3.0,5.0,
						 2.0, 4.0,5.0 };
	vector<double> vec = { 10.0,3.0,12.0 };*/

	//double matrix[N][N] = { 1.0,1.0,1.0,1.0,
	//					 1.0,2.0,-2.0, 3.0,
	//					 2.0, 0.0,1.0, 0.0,
	//					 3.0, 1.0, 2.0, 2.0};
	//vector<double> vec = { 10.0,11.0,5.0, 19.0};

	//vector<double> vec1;
	//vector<vector<double>> extendedMatrix(N, vector<double>(N));

		//for (int i = 0; i < N; i++) // заполнение расширенной матрицы
		//{
		//	for (int j = 0; j < N; j++)
		//	{
		//		extendedMatrix[i][j] = matrix[i][j];
		//	}
		//	extendedMatrix[i].push_back(vec[i]);
		//}
		//extendedMatrixOutput(extendedMatrix, N);

		
		for (int g = 0; g < N; g++)
		{
			if (extendedMatrix[g][g] == 0)
			{
				cout << "IER = 1";
				return 0;
			}

			for (int i = 0 + g; i < N; i++) // деление всех элементов строк на первый элемент строки
			{
				double temp = extendedMatrix[i][g];
				/*cout << endl << "temp " << temp << endl;*/
				for (int j = 0 + g; j < N + 1; j++)
				{
					extendedMatrix[i][j] = extendedMatrix[i][j] / temp;
				}
			}
			/*extendedMatrixOutput(extendedMatrix, N);*/

			for (int i = 1 + g; i < N; i++)
			{
				
				for (int j = 0 + g; j < N  + 1; j++)
				{
					extendedMatrix[i][j] = extendedMatrix[i][j] - extendedMatrix[g][j];
				}
			}
			/*extendedMatrixOutput(extendedMatrix, N);*/
			
			extendedMatrixOutput(extendedMatrix, N);
			for (int i = 0; i < N; i++) {
				if (i != g) {
					double factor = extendedMatrix[i][g];
					for (int j = g; j < N + 1; j++) {
						extendedMatrix[i][j] -= factor * extendedMatrix[g][j];
					}
				}
			}
			extendedMatrixOutput(extendedMatrix, N);
			cout << endl << "end of cycle " << g + 1 << endl << endl;
		}
		/*extendedMatrixOutput(extendedMatrix, N);*/

		for (int i = 0; i < N; i++)
		{
			vec1.push_back(extendedMatrix[i][N]);
		}
		cout << "vec1= ";
		for (int i = 0; i < N; i++)
		{
			cout << vec1[i] << " ";
		}
			/*for (int j = N - 2; j >= 0; j--)
			{

				for (int i = N - 1; i >= 0; i--)
				{
					double temp = extendedMatrix[i][j];
					for (int k = i; k < N; k++)
					{
						extendedMatrix[i][k] = extendedMatrix[i][k] - extendedMatrix[i + 1][j] * temp;
					}

				}
			}
			extendedMatrixOutput(extendedMatrix, N);*/

			/*for (int i = 1 + g; i < N; i++)
			{

				for (int j = 0 + g; j < N + 1; j++)
				{
					extendedMatrix[i][j] = extendedMatrix[i][j] - extendedMatrix[g][j];
				}
			}*/
		/*	extendedMatrixOutput(extendedMatrix, N);*/
		/*	cout << endl << "end of cycle " << g + 1 << endl << endl;*/
		
		

}
void extendedMatrixOutput(vector<vector<double>> extendedMatrix, const int N)
{
	for (int i = 0; i < N; i++) // вывод расширенной матрицы
	{
		for (int j = 0; j < N + 1; j++)
		{
			cout << extendedMatrix[i][j] << left << setw(12);
		}
		cout << endl;
	}
	cout << endl << endl;
}