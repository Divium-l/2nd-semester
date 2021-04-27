#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;


/**
* \brief расчёт функции y1
* \param x значение x
* \param a значение a
* \return значение функции y1
**/
double calcY1(const double x, const double a);

/**
* \brief расчёт функции y2
* \param x значение x
* \param a значение a
* \return значение функции y2
**/
double calcY2(const double x, const double a);

int main()
{
	const double a = 2, LOWER_BOUND = 1, UPPER_BOUND = 2;
	double x, y;
	cin >> x;

	if (LOWER_BOUND <= x && x <= UPPER_BOUND)
		y = calcY1(x, a);
	else if (x < LOWER_BOUND)
		y = 1;
	else
		y = calcY2(x, a);

	cout << "y = " << y << "\n";

	return 0;
}

double calcY1(const double x, const double a)
{
	return a * pow(x, 2 * log(x));
}

double calcY2(const double x, const double a)
{
	return pow(M_E, a * x) * cos(x);
}