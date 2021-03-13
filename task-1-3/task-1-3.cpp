#include <iostream>
#include <string>
#include <cctype>

using namespace std;

double input();
double calcGravityForce(const double mass);

int main()
{
	double force, mass = input();

	if (mass <= 0)
	{
		mass = abs(mass);
		cout << "An attempt was made to fix a mistake" << endl;
	}

	force = calcGravityForce(mass);

	cout << endl << endl;
	cout << "Gravity force = " << force;
	cout << "\nWeight = " << force;

}

double input() {

	string str;
	bool isFloat, isNegative, isValid = false;
	int i;

	while (!isValid)
	{

		isValid = true;
		isFloat = false;
		isNegative = false;

		cout << "Mass: ";
		cin >> str;

		if (str[0] == '-' && str != "-" && str != "-.")
		{
			isNegative = true;
			str.erase(0, 1);
		}

		i = 0;
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

		if (!isValid)
			cout << "Incorrect value! Please try again" << endl;

	}

	if (isNegative) str.insert(0, "-");
	return stod(str);
}

double calcGravityForce(const double mass)
{
	return 9.81 * mass;
}