#include<iostream>
#include<math.h>

using namespace std;

double f(double);
double end(double, double);


int main()
{
	setlocale(LC_ALL, "rus");

	double a(0), b(0.5), e(0.0001);
	const double l1(0.618), l2(0.382);
	double y1, y2, A, B;
	y1 = l1*a + l2*b;
	y2 = l2*a + l1*b;
	A = f(y1);
	B = f(y2);
	while (b - a < e)
	{

		if (A < B)
		{
			B = A;
			y2 = y1;
			y1 = l1*a + l2*b;
			A = f(y1);
		}
		else {
			A = B;
			y1 = y2;
			y2 = l2*a + l1*b;
			B = f(y2);
		}
	}

	cout << end(a, b) << endl;

	system("pause");
	return 0;
}


double f(double x)
{
	return pow(2.7182818, sqrt(x))*(x - 1.0)*(x - 10.0)*(x - 2.0 - 1.0)*(x - 0.5);
}

double end(double a, double b)
{
	return (a + b) / 2.0;
}