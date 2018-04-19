////////////////////////////////////////////////////////////////////
//Алгоритм преобразования матрица инцидентности в матрицу контуров//
////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#define n 6 // Число вершин
#define m 9 // Число ребер
using namespace std;

void transpose(int matrix[m][m]) // Функция транспонирования 
{
	int t;
	for (int i = 0; i < m; i++)
	{
		for (int j = i; j < m; j++)
		{
			t = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = t;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN"); 
	int i = 0; // Элемент столбцов 
	int j = 0; // Элемент строк
	int MatInc[n][m]; //Массив хранящий матрицу инциденций
	int MatObr[n-1][n-1]; //Массив хранящий матрицу обратную матрицу A12^-1
	int MatA11[n-1][m-n+1]; //Массив хранящий матрицу A11, число ребер m-(n-1)
	int MatCT[m][m]; //Массив хранящий транспонированную матрицу контуров Стд без единичной матрицы 
	int MatC[m-n+1][m]; //Массив хранящий матрицу контуров

	ifstream in1("input1.txt");//Считаем матрицу инциденций из файла
	for (i = 0; i < n; i++) 
		for (j = 0; j < m; j++)
			in1 >> MatInc[i][j];
	in1.close();

	ifstream in2("input2.txt");
	for (i = 0; i < n - 1; i++) //Считаем обратную матрицу A12^-1 из файла
		for (j = 0; j < n - 1; j++)
			in2 >> MatObr[i][j];
	in2.close();

	cout << "Матрица инциденций"<<endl; 
	for (i = 0; i < n; i++) //Выведем матрицу инциденций 
	{
		for (j = 0; j < m; j++)
		cout << MatInc[i][j] << " ";
		cout << endl;
	}
	cout << endl; 

	cout << "Матрица A11" << endl;
	for (i = 0; i < n - 1; i++) //Вывод матрицы A11
	{
		for (j = 0; j < m - n + 1; j++)
		{
			MatA11[i][j] = MatInc[i][j];
			cout << MatA11[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Обратная матрица A12^-1" << endl;
	for (i = 0; i < n - 1; i++) //Выведем обратную матрицу A12^-1
	{
		for (j = 0; j < n - 1; j++)
			cout << MatObr[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "Транспонированная матрица контуров Ст" << endl;
	for (i = 0; i < n - 1; i++)//Умножение матриц 
	{
		for (j = 0; j < m - n + 1; j++)
		{
			MatCT[i][j] = 0;
			for (int k = 0; k < n - 1; k++)
			MatCT[i][j] += MatObr[i][k] * MatA11[k][j];
			if (MatCT[i][j] != 1||0) MatCT[i][j] = 0; //Так как используем сложение по модулю 2
			if (MatCT[i][j] == -1 ) MatCT[i][j] = 1; //Так как граф ненаправленный 
			cout << MatCT[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Матрица контуров" << endl;
	transpose(MatCT); //Вызов функции транспонирования 
	for (i = 0; i <m - n + 1; i++) // Вывод матрицы контуров 
	{
		for (j = 0; j < m; j++)
		{
			if (j == n-1+i) MatC[i][j] = 1; // Если элемент строки равен n-1ому элементу столбца плюс номер строки то записываем 1
			else if ((j > m - n + 1)&&(j != n - 1 + i)) MatC[i][j] = 0; // Если идет после n то пишем 0
			else MatC[i][j] = MatCT[i][j]; // Если не 1 и 2 то присваиваем значение транспонированной матрицы 
			cout << MatC[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}