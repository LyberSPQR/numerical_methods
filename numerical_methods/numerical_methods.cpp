// numerical_methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
void extendedMatrixOutput(vector<vector<double>> extendedMatrix, const int N);
int main()
{
	setlocale(LC_ALL, "ru");
	//int n;
	//double x, y, z;
	//x = 1.71;
	//y = 8.64;
	//z = 1.71 / 8.64;

	int arrSize, vecSize;
	cout << "Введите размер матрицы и вектора" << endl;
	cin >> arrSize;
	vecSize = arrSize;

	vector<vector<double>> extendedMatrix(arrSize, vector<double>(arrSize));
	extendedMatrix = { {1.0,1.0,1.0,1.0,10.0},{1,2,-2,3,11},{2,0,1,0,5}, {3,1,2,2,19} };
	vector<double> vec(vecSize);
	vector<double> vec1(vecSize);
	//cout << "Введите элементы вектора " << vecSize << endl;
	//for (int i = 0; i < vecSize; i++)
	//{
	//	cin >> vec[i];
	//}
	//cout << "Введите элементы матрицы порядка " << arrSize << endl;
	//for (int i = 0; i < arrSize; i++) // заполнение расширенной матрицы
	//{
	//	for (int j = 0; j < arrSize; j++)
	//	{
	//		cin >> extendedMatrix[i][j];
	//	}
	//	extendedMatrix[i].push_back(vec[i]);
	//}
	cout << "Матрица:" << endl;
	extendedMatrixOutput(extendedMatrix, arrSize);
		for (int g = 0; g < arrSize; g++)
		{
			if (extendedMatrix[g][g] == 0)
			{
				cout << "IER = 1";
				return 0;
			}

			double maxElement = extendedMatrix[g][g];
			int maxRow = g;
			for (int j = g; j < arrSize; j++)
			{
				if (abs(extendedMatrix[j][g]) > abs(maxElement))
				{
					maxElement = extendedMatrix[j][g];
					maxRow = j;
				}		
			} 
			//SWAP
			if (maxRow != g)
			{
				swap(extendedMatrix[g], extendedMatrix[maxRow]);
			}
			
			/*vector<double> temp(arrSize);
			temp = extendedMatrix[g];
			extendedMatrix[g] = extendedMatrix[maxRow];
			extendedMatrix[maxRow] = temp;*/

			cout << "Матрица после смены:" << endl;
			extendedMatrixOutput(extendedMatrix, arrSize);

			for (int i = 0 + g; i < arrSize; i++) // деление всех элементов строк на первый элемент строки
			{
				double temp = extendedMatrix[i][g];
				/*cout << endl << "temp " << temp << endl;*/
				for (int j = 0 + g; j < arrSize + 1; j++)
				{
					extendedMatrix[i][j] = extendedMatrix[i][j] / temp;
				}
			}

			for (int i = 1 + g; i < arrSize; i++)
			{
				
				for (int j = 0 + g; j < arrSize + 1; j++)
				{
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

		for (int i = 0; i < arrSize; i++)
		{
			vec1[i] = extendedMatrix[i][arrSize];
		}
		cout << "vec1= ";
		for (int i = 0; i < vecSize; i++)
		{
			cout << vec1[i] << " ";
		}
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