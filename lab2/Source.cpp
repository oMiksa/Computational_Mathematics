#include<iostream>
#include<algorithm>
#include<math.h>

#define c 0.02

using namespace std;

void Print(double[][4], double[]);
void Prepa(double[][4], double[]);
double normal(double[]);
double normal(double[][4]);
double Error(double, double);
void Mult(double[][4], double[], double[]);
void Print(double[]);
void Minus(double[], double[], double[]);
void cp(double[], double[]);


int main()
{
	setlocale(LC_ALL, "rus");
	cout << "solution of systems of linear equations" << endl;
	double arrC[4][4] = {	{ { 0.95 + c },{ 0.26 + c },{ -0.17 + c },{ 0.27 + c }, },
							{ { -0.15 + c },{ 1.26 + c },{ 0.36 + c },{ 0.42 + c }, },
							{ { 0.26 + c },{ -0.52 + c },{ -1.76 + c },{ 0.31 + c }, },
							{ { -0.44 + c },{ 0.29 + c },{ -0.78 + c },{ -1.78 + c }, }, };
	double arrB[4] = { 2.48,-3.16,1.52,-1.29 };
	double arrCB[4], arrX[4], temp[4], test[4];

	Print(arrC, arrB);
	Prepa(arrC, arrB);

	cout << "steps to accuracy 0.0001: " << Error(normal(arrC), normal(arrB)) << endl;

	Mult(arrC, arrB, arrCB);		//arrC * arrB = arrCB
	Minus(arrB, arrCB, arrX);		//arrB - arrCB = arrX

	for (int i(0);; i++)
	{
		cp(temp, arrX);				//temp = arrX
		Mult(arrC, arrX, arrCB);	//arrC * arrX = arrCB
		Minus(arrB, arrCB, arrX);	//arrB - arrCB = arrX
		Minus(arrX, temp, test);	//arrX - temp = test

		cout << "interpretation ¹ " << i + 1 << " - (accuracy) " << normal(arrC) / (1 - normal(arrC))*normal(test) << endl;

		if (normal(arrC) / (1 - normal(arrC))*normal(test) < 0.0001)
		{
			Print(arrX);
			break;
		}
	}

	Mult(arrC, arrX, arrCB);		//arrC * arrX = arrCB
	Minus(arrB, arrCB, arrX);		//arrB - arrCB = arrX
							
	system("pause");
	return 0;
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
	double str[4] = {};
	for (int i(0); i < 4; i++)
	{
		for (int j(0); j < 4; j++)
		{
			str[i] += abs(C[i][j]);
		}
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
		CB[i] = 0;
		for (int j(0); j < 4; j++)
		{
			CB[i] += C[i][j] * B[i];
		}
	}
}

void Print(double X[])
{
	for (int i(0); i < 4; i++)
	{
		cout << X[i] << endl;
	}
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
