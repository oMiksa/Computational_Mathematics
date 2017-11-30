#include<iostream>
#include<math.h>

using namespace std;

double f(double, double);
double Qf(double);
double du(double, double, double);
double li(double, double, double, double, double);
double** dy(double, double, double, double, double);
double Q(double*);

int main()
{
	setlocale(LC_ALL, "rus");


	double h1(0.5), h2(0.25);
	double x(0), y(0.1);
	double a(0), b(1);

	double **D;
	D = dy(x, y, a, b, h1);
	cout << "DU y` = cos(y) / (4 + x) + y;  y(0) = 0.1 \nQ = integral(1,0) y^2 " << endl;
	cout << endl << "Differential solution by Runge-Kutta method of the fourth order with an accuracy of 0.0001,\nThe integral of computation Simpson's formula with a step of 0.1." << endl;
	for (int i(0); i < 5; i++)
	{
		cout << "x= " << D[0][i] << "	y= " << D[1][i] << endl;
	}

	double arrli[2][11];
	for (int i(0); i < 11; i++)
	{
		arrli[0][i] = (double)i*0.1;
	}
	for (int i(0); i < 11; i++)
	{
		if (arrli[0][i] == D[0][i])
		{
			arrli[1][i] = D[1][i];
			continue;
		}

		int j(0);
		while (D[0][j] < arrli[0][i])
		{
			j++;
		}
		arrli[1][i] = li(D[0][j - 1], D[1][j - 1], D[0][j], D[1][j], arrli[0][i]);
	}
	cout << endl << "Find the values of the function in intermediate nodes use linear interpolation" << endl;
	for (int i(0); i < 11; i++)
	{
		cout << "x= " << arrli[0][i] << "	y= " << arrli[1][i] << endl;
	}

	double arrQ[11];
	for (int i(0); i < 11; i++)
	{
		arrQ[i] = arrli[1][i];
	}


	cout << endl << "The amount of heat released per unit time\nQ = " << Q(arrQ) << endl;





	system("pause");
	return 0;
}

double f(double x, double y)
{
	return (cos(y) / (4 + x)) + y;
}

double Q(double *z)
{
	double h(0.1), a(0), b(1);
	int n = (b - a) / h;
	double sum(Qf(z[0]) + Qf(z[n]));

	for (int i(1); i < n; i++)
	{
		if ((int)i % 2)
		{
			sum += 4 * Qf(z[i]);
		}
		else {
			sum += 2 * Qf(z[i]);
		}
	}
	return h / 3 * sum;
}

double Qf(double x)
{
	return pow(x, 2);
}

double du(double x0, double y0, double h)
{
	double k1, k2, k3, k4;
	k1 = f(x0, y0);
	k2 = f(x0 + h / 2.0, y0 + h / 2.0 * k1);
	k3 = f(x0 + h / 2.0, y0 + h / 2.0 * k2);
	k4 = f(x0 + h, y0 + h * k3);
	return y0 + (h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4));
}

double li(double x1, double y1, double x2, double y2, double X)
{
	return y1 + (y2 - y1) / (x2 - x1)*(X - x1);
}

double** dy(double x, double y, double a, double b, double h)
{
	double **arr1 = new double*[2];
	for (int i(0); i < 2; i++)
		arr1[i] = new double[(b - a) / h];

	double **arr2 = new double*[2];
	for (int i(0); i < 2; i++)
		arr2[i] = new double[(b - a) / h*2.0];


	arr1[0][0] = arr2[0][0] = 0;
	arr1[1][0] = arr2[1][0] = 0.1;

	for (int i(1); i < (b - a) / h * 2.0 + 1; i++)
	{
		arr2[0][i] = x + i*(h / 2.0);
		arr2[1][i] = du(arr2[0][i - 1], arr2[1][i - 1], h / 2.0);
	}

	for (int i(1); i < (b - a) / h + 1; i++)
	{
		arr1[0][i] = x + i*h;
		arr1[1][i] = du(arr1[0][i - 1], arr1[1][i - 1], h);
	}

	/*
	cout << endl << " x		 y	 " << endl;
	for (int i(0); i < (b - a) / h+1; i++)
	{
	cout << i*h << ") " << arrX1[i] << "		 " << arrY1[i] << endl;
	}
	cout << endl << " x		 y	 " << endl;
	for (int i(0); i < (b - a) / h * 2+1; i++)
	{
	cout << i*h/2 << ") " << arrX2[i] << "		 " << arrY2[i] << endl;
	}
	*/

	for (int i(0); i < (b - a) / h + 1; i++)
	{
		if (arr1[1][i] - arr2[1][i * 2 + 1] < 0.0001)
		{
			return arr2;
		}
	}
	dy(x, y, a, b, h / 2.0);
}