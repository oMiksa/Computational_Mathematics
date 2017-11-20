#include<iostream>
#include<math.h>

using namespace std;

double f(double, double);//функция
double Q();//Q интеграл
double Qf(double);//f(x) для Q
double du(double, double, double);//ДУ
double li(double, double, double, double, double);//интерполяция

int main()
{
	setlocale(LC_ALL, "rus");

	double arrDU1[5], arrDU2[5];
	double h1(0.5), h2(0.25);
	double x(0), y(0.1);

	//шаг 0.5 + Линейная инторполяция
	arrDU1[0] = 0.1;
	arrDU1[2] = du(x, y, h1);
	arrDU1[4] = du((x + h1), arrDU1[2], h1);

	//Линейная интерполяция
	arrDU1[1] = li(x, y, (x + h1), arrDU1[2], h1 / 2);
	arrDU1[3] = li(x + h1, arrDU1[2], (x + 2 * h1), arrDU1[4], h1 / 2 * 3);

	// шаг 0.25
	arrDU2[0] = 0.1;
	arrDU2[1] = du(x, y, h2);
	for (int i(2); i < 5; i++)
	{
		arrDU2[i] = du((x + h2*(double)i), arrDU2[i - 1], h2);
	}

	cout << "Количество теплоты выделяющееся на единичном сопротивлении за единицу времени Q = " << Q() << endl;

	//Вывод таблица ДУ с интервалом [0,1].
	cout << "Таблица ДУ с интервалом [0,1]" << endl;
	for (int i(0); i < 5; i++)
	{
		cout << (i)*0.25 << " | " << arrDU1[i] << " | " << arrDU2[i] << " |";
		if (abs(abs(arrDU1[i]) - abs(arrDU2[i])) < 0.0001 * 15)
			cout << " Good " << endl;
		else cout << "Bed" << endl;
	}

	system("pause");
	return 0;
}

double f(double x, double y)
{
	return cos(y) / (4 + x) + y;
}

double Q()
{
	double h(0.1), b(1), a(0), sum(Qf(a) + Qf(b));
	double n = (b - a) / h;
	for (double i(0); i < n; i++)
	{
		if ((int)i % 2)
		{
			sum += 4 * Qf(h*i);
		}
		else {
			sum += 2 * Qf(h*i);
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
	k2 = f(x0 + h / 2, y0 + h / 2 * k1);
	k3 = f(x0 + h / 2, y0 + h / 2 * k2);
	k4 = f(x0 + h, y0 + h * k3);
	return y0 + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
}

double li(double x1, double y1, double x2, double y2, double X)
{
	return y1 + (y2 - y1) / (x2 - x1)*(X - x1);
}