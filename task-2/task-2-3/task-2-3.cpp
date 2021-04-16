#include <iostream>
#include "input_lib.cpp"

using namespace std;

/**
* \brief Метод, проверяющий, что хотя бы одна сторона XYZ кирпича меньше стороны отверстия R
* \param x сторона кирпича X
* \param y сторона кирпича Y
* \param z сторона кирпича Z
* \param r сторона отверстия R
* \return true, если хотя бы одна сторона XYZ кирпича меньше стороны отверстия R
**/
bool passR(const double x, const double y, const double z, const double r);

/**
* \brief Метод, проверяющий, что хотя бы одна сторона XYZ кирпича меньше стороны отверстия S
* \param x сторона кирпича X
* \param y сторона кирпича Y
* \param z сторона кирпича Z
* \param s сторона отверстия S
* \return true, если хотя бы одна сторона XYZ кирпича меньше стороны отверстия S
**/
bool passS(const double x, const double y, const double z, const double r, const double s);

int main()
{
	double x, y, z, r , s;

	cout << "Input brick dimensions\n";
	x = input::inputDouble(false, "x: ");
	y = input::inputDouble(false, "y: ");
	z = input::inputDouble(false, "z: ");

	cout << "\nInput hole dimensions\n";
	r = input::inputDouble(false, "r: ");
	s = input::inputDouble(false, "s: ");

	if (passR(x, y, z, r) && passS(x, y, z, r, s))
		cout << "\nThe brick can pass through the hole\n";
	else
		cout << "\nThe brick cannot pass through the hole\n";

	return 0;
}

bool passS(const double x, const double y, const double z, const double r, const double s)
{

	return (x < s) || (y < s) || (z < s);
}

bool passR(const double x, const double y, const double z, const double r)
{

	return (x < r) || (y < r) || (z < r);
}