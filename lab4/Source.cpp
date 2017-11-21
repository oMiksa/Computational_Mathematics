#include<iostream>
#include<math.h>

using namespace std;

double Vareant(double);
double Step(double);

int main()
{
	setlocale(LC_ALL, "rus");

	double c(Vareant(2.0));
	double h(Step(c));

	double arr[3][22];
	cout << "numerical differentiation" << endl;
	cout << "|	h		|	f(x)	|	f`(x)	|" << endl;

	for (int i(0); i < 22; i++)
	{
		arr[0][i] = c + h*((double)i - 1.0);//интервал с h
		arr[1][i] = (1 / pow(c, 2))*cos(c*arr[0][i]);// f(x)
		arr[2][i] = (-1 / c)*cos(c*arr[0][i]);//f`(x)
		cout << "| " << arr[0][i] << "	|	" << arr[1][i] << "	|	" << arr[2][i] << "	|" << endl;
	}



	system("pause");
	return 0;
}

double Vareant(double n)
{
	return 3 * pow(0.1*(n + 1.0), 3);
}

double Step(double a)
{
	return pow((3 * 0.0001) / a, (1.0 / 3.0));
}