#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "input_lib.cpp"

using namespace std;

int main()
{
	const double a = 2;
	double x = input::inputDouble(true, "X: "), y;

	if (1 <= x && x <= 2)
		y = a * pow(x, 2 * log(x));
	else if (x < 1)
		y = 1;
	else
		y = pow(M_E, a * x) * cos(x);

	cout << "y = " << y << "\n";

	return 0;
}