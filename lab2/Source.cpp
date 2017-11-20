#include<iostream>
#include<algorithm>
#include<math.h>

using namespace std;

double Var(int);// изменение задания по варианту 
void Print(double[][4], double[]);// вывод матрицы 3х1 и 4х4 
void Prepa(double[][4], double[]);// Преобразованная система по диагонали
double normal(double[]);// норма матрицы 3х1
double normal(double[][4]);// норма матрицы 4х4
double Error(double, double);//кол-во шагов погрешности
void Mult(double[][4], double[], double[]);// умножение матриц
void Print(double[]);// вывод матрицы 3х1
void Minus(double[], double[], double[]);// вычитание матриц
void cp(double[], double[]);


int main()
{
	setlocale(LC_ALL, "rus");
	double c;
	c = Var(2);//2 = вариант!
	double arrC[4][4] = { { { 0.95 + c },{ 0.26 + c },{ -0.17 + c },{ 0.27 + c }, },
	{ { -0.15 + c },{ 1.26 + c },{ 0.36 + c },{ 0.42 + c }, },
	{ { 0.26 + c },{ -0.52 + c },{ -1.76 + c },{ 0.31 + c }, },
	{ { -0.44 + c },{ 0.29 + c },{ -0.78 + c },{ -1.78 + c }, }, };
	double arrB[4] = { 2.48,-3.16,1.52,-1.29 };
	double arrCB[4], arrX[4], temp[4], test[4];

	Print(arrC, arrB);
	Prepa(arrC, arrB);
	Print(arrC, arrB);
	cout << "Число шагов для достижения 0.0001: " << Error(normal(arrC), normal(arrB)) << endl;

	//////////////////////////////////////
	Mult(arrC, arrB, arrCB);//C*B
	Minus(arrB, arrCB, arrX);//B-CB

	for (int i(0); i <(int)Error(normal(arrC), normal(arrB)); i++)
	{
		cp(temp, arrX);
		Mult(arrC, arrX, arrCB);
		Minus(arrB, arrCB, arrX);
		Minus(arrX, temp, test);
		cout << "интерпритация № " << i + 1 << " - " << normal(arrC) / (1 - normal(arrC))*normal(test) << endl;
	}

	Mult(arrC, arrX, arrCB);//C*X(k)
	Minus(arrB, arrCB, arrX);//B-C*X(k)
							 /////////////////////////////////////

							 //Print(temp);//X(k-1)
							 //Print(arrX);//X(k)

							 //проверка погрешности
							 //Minus(arrX, temp, test);
							 //cout << normal(test) << endl;

							 //cout << normal(arrC) / (1 - normal(arrC))*normal(test) << endl;

	system("pause");
	return 0;
}

double Var(int n)
{
	return (double)n*0.01;
}

void Print(double C[][4], double B[])
{
	cout << endl;
	for (int i(0); i < 4; i++)
	{
		cout << C[i][0] << "*x1";
		for (int j(1); j < 4; j++)
		{
			if (C[i][j] >= 0)
				cout << "+" << C[i][j] << "*x" << j;
			else cout << C[i][j] << "*x" << j;
		}
		cout << " = " << B[i] << endl;
	}
	cout << endl;
}

void Prepa(double C[][4], double B[])
{
	for (int i(0); i < 4; i++)
	{
		double temp;
		temp = C[i][i];
		for (int j(0); j < 4; j++)
		{
			if (C[i][j] == temp)
				C[i][j] = 0;
			C[i][j] /= temp;
		}
		B[i] /= temp;
	}
}

double normal(double C[][4])
{
	double str[4];
	for (int i(0); i < 4; i++)
	{
		str[i] = abs(C[i][0]) + abs(C[i][1]) + abs(C[i][2]) + abs(C[i][3]);
	}
	return max(str[0], max(str[1], max(str[2], str[3])));
}

double normal(double B[])
{
	return max(B[0], max(B[1], max(B[2], B[3])));
}

double Error(double C, double B)
{
	return round(log((0.0001 / B)*(1 - C)) / log(C) - 1);
}

void Mult(double C[][4], double B[], double CB[])
{
	for (int i(0); i < 4; i++)
	{
		CB[i] = C[i][0] * B[i] + C[i][1] * B[i] + C[i][2] * B[i] + C[i][3] * B[i];
	}
}

void Print(double X[])
{
	cout << endl << X[0] << endl << X[1] << endl << X[2] << endl << X[3] << endl;
}

void Minus(double B[], double CX[], double X[])
{
	for (int i(0); i < 4; i++)
	{
		X[i] = B[i] - CX[i];
	}
}

void cp(double A[], double B[])
{
	for (int i(0); i < 4; i++)
	{
		A[i] = B[i];
	}
}
