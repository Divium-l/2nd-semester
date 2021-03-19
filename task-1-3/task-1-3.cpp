#include <iostream>
#include <string>
#include <cctype>

using namespace std;

double input(bool allowNegative);
bool isValidDouble(string str, bool allowNegative);
double calcGravityForce(const double mass);


int main()
{
	double force, mass = input(false);

	force = calcGravityForce(mass);

	cout << endl << endl;
	cout << "Gravity force = " << force;
	cout << "\nWeight = " << force;

}

double input(bool allowNegative) {

	string str;
	bool isValid = false;
	int i;

	while (!isValid)
	{

		isValid = true;

		cout << "Mass: ";
		cin >> str;

		isValid = isValidDouble(str, allowNegative);

		if (!isValid)
			cout << "Incorrect value! Please try again" << endl;

	}

	return stod(str);
}

bool isValidDouble(string str, bool allowNegative)
{
	bool isValid, isFloat;
	int i = 0;

	isValid = true;
	isFloat = false;

	if (allowNegative && str[0] == '-' && str != "-" && str != "-.")
		str.erase(0, 1);

	while (i < str.length() && isValid)
	{

		if ((isdigit(str[i])) || (str[i] == '.' && !isFloat) && str != ".")
		{
			isFloat = (str[i] == '.');
		}
		else
		{
			isValid = false;
		}

		i++;
	}

	return isValid;
}

double calcGravityForce(const double mass)
{
	return 9.81 * mass;
}