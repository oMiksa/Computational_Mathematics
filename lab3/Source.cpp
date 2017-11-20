#include<iostream>
#include<math.h>

using namespace std;

double f(double);

int main()
{
	setlocale(LC_ALL, "rus");

	// итервал(3.5; 4)
	double a, b, e(0.0001);
	int arr[201];
	arr[200] = 200;
	double AB[10];
	int j(0);
	cout << "Интервалы: ";
	for (int i(-100); i < 100; i++)
	{
		arr[i + 100] = i;
		if (f(i) * f(i + 1) < 0)
		{
			AB[j] = i;
			cout << " (" << AB[j];
			AB[++j] = ++i;
			cout << "; " << AB[j] << ") ";
			j++;
		}
	}
	cout << endl;

	double temp;
	for (int i(0); i < 3; i++)
	{
		cout << "X ~ ";
		a = AB[i * 2];
		b = AB[i * 2 + 1];
		while (1)
		{
			if (abs(a - b) < e)
			{
				cout << a << endl;
				break;
			}
			temp = (a + b) / 2.0;
			if (f(temp) == 0)
			{
				cout << temp << endl;
				break;
			}
			if (f(a)*f(temp) < 0)
				b = temp;
			if (f(temp)*f(b) < 0)

				a = temp;
		}
	}
	system("pause");
	return 0;
}

double f(double x)
{
	return pow(x, 3) + 3 * pow(x, 2) - 24 * x - 10;
}
