#include <iostream>
#include <string>
#include <cctype>
#include "input_lib.cpp"

using namespace std;

/**
* \brief Метод, считающий силу тяжести
* \param mass масса тела
* \return значение гравитационной силы
**/
double calcGravityForce(const double mass);


int main()
{
	double force, mass = input::inputDouble(false, "Value: ");

	force = calcGravityForce(mass);

	cout << "\n\n";
	cout << "Gravity force = " << force;
	cout << "\nWeight = " << force;

}

double calcGravityForce(const double mass)
{	
	const double g = 9.81;
	return g * mass;
}