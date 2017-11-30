#include<iostream>
#include<math.h>

using namespace std;

double Var(double);
double Step(double);
double f(double, double);
double fi(double, double, double);
double fii(double, double);

int main()
{
	setlocale(LC_ALL, "rus");

	double c(Var(2.0));
	double h(Step(c));

	double arr[2][22];
	double arri[3][20];


	for (int i(-1); i < 21; i++)
	{
		arr[0][i + 1] = c + i*h;
		arr[1][i + 1] = f((arr[0][i + 1]), c);
	}

	for (int i(0); i < 20; i++)
	{
		arri[0][i] = c + i*h;
		arri[1][i] = fi(arr[1][i + 2], arr[1][i], h);
		arri[2][i] = fii(arri[0][i], c);
	}


	cout << " differentiation " << endl;
	cout << "\n x		|	f	" << endl;
	cout << fixed << right;
	for (int i(0); i < 22; i++)
	{
		cout << arr[0][i] << "	|  " << arr[1][i] << "  " << endl;
	}

	cout << "\n x`		|	f`	|	f``" << endl;
	for (int i(0); i < 20; i++)
	{
		cout << arri[0][i] << "	|  " << arri[1][i] << "	|	" << arri[2][i] << endl;
	}




	system("pause");
	return 0;
}

double Var(double n)
{
	//option
	return 3 * pow(0.1*(n + 1.0), 3);
}

double Step(double a)
{
	return pow((3 * 0.0001) / a, (1.0 / 3.0));
}
double f(double x, double c)
{
	//function
	return 1 / pow(c, 2)*cos(c*x);
}
double fi(double x1, double x2, double h)
{
	//approximate function
	return (x1 - x2) / (2.0 * h);
}

double fii(double x, double c)
{
	//exact function
	return (-1) / c*sin(c*x);
}