#include <iostream>
#include <cmath>
#include "input_lib.cpp"

using namespace std;

/**
* \brief Метод, считающий гипотенузу
* \param a первый катет треугольника
* \param b второй катет треуголника
* \return значение гипотенузы
**/
double calcHypotenuse(double const a, double const b);

/**
* \brief Метод, считающий периметр
* \param a первый катет треугольника
* \param b второй катет треуголника
* \param c гипотенуза треугольника
* \return значение периметра
**/
double calcPerimeter(double const a, double const b, double const c);

/**
* \brief Метод, считающий площадь
* \param a первый катет треугольника
* \param b второй катет треуголника
* \return значение площади
**/
double calcArea(double const a, double const b);

int main()
{
	double a = input::inputDouble(false, "Cathetus a: "), b = input::inputDouble(false, "Cathetus b: "), c;

	c = calcHypotenuse(a, b);

	cout << "Perimeter: " << calcPerimeter(a, b, c) << "\n";
	cout << "Area: " << calcArea(a, b) << "\n";

	return 0;
}

double calcHypotenuse(double const a, double const b)
{
	return sqrt(pow(a, 2) + pow(b, 2));
}

double calcPerimeter(double const a, double const b, double const c)
{
	return a + b + c;
}

double calcArea(double const a, double const b)
{
	return 0.5 * a * b;
}