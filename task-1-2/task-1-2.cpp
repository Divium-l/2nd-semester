#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

double input();
double calcFaceArea(const double length);
double calcSurfaceArea(const double length);
double calcVolume(const double length);

int main()
{
	double length = input();

	if (length <= 0)
	{
		length = abs(length);
		cout << "An attempt was made to fix a mistake" << endl;
	}

	cout << endl << endl;
	cout << "Face area = " << calcFaceArea(length);
	cout << "\nSurface area = " << calcSurfaceArea(length);
	cout << "\nVolume = " << calcVolume(length);

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

		cout << "Length: ";
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

double calcFaceArea(const double length)
{
	return pow(length, 2);
}

double calcSurfaceArea(const double length)
{
	return 6 * calcFaceArea(length);
}

double calcVolume(const double length)
{
	return pow(length, 3);
}