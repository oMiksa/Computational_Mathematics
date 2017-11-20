#include<iostream>
#include<math.h>

#define c 2

using namespace std;

double step(int);
double li(double, double, double, double, double);
double points(int, double);
double pointsD(int, double);
void Print(double *, double *, int);

int main()
{
	setlocale(LC_ALL, "rus");

	double h(step(c));
	double arr1[31];//exact
	double arr2[30];//interpolation
	double arr3[31];//additional points

	for (int i(0); i < 31; i++)
	{
		arr1[i] = 2 * pow(c, 3)*sin(points(i, h) / c);
		arr3[i] = 2 * pow(c, 3)*sin(pointsD(i, h) / c);
	}
	for (int i(0); i < 30; i++)
	{
		//x1,y1,x2,y2,X
		arr2[i] = li(pointsD(i, h), arr3[i], pointsD((i + 1), h), arr3[i + 1], points(i, h));
	}

	Print(arr1, arr2, 30);

	system("pause");
	return 0;
}

double step(int a)
{
	//step calculation + round up to 3
	return round(sqrt(8 / (2 * (double)a)*(0.0001 - 0.00005)) * 1000) / 1000;
}

double li(double x1, double y1, double x2, double y2, double X)
{
	//interpolation
	return y1 + (y2 - y1) / (x2 - x1)*(X - x1);
}

double points(int i, double h)
{
	//points X
	return (c + (double)i*h);
}

double pointsD(int i, double h)
{
	//additional points X
	return (c + (double)i*h + (i % 4 + 1)*h / 5);
}

void Print(double *arr1, double *arr2, int m)
{
	cout << "|	exact	|	interpolation	|" << endl;
	for (int i(0); i < m; i++)
	{
		cout << "|	" << arr1[i] << "		|	" << arr2[i] << "		|" << endl;
	}
}