#include <iostream>
#include <string>
#include <cctype>

using namespace std;

double input();

int main()
{
	double a = input();

	if (a <= 0)
	{
		a = abs(a);
		cout << "An attempt was made to fix a mistake" << endl;
	}

	cout << endl << endl;
	cout << "Face area = " << pow(a, 2) << endl;
	cout << "Surface area = " << 6*pow(a, 2) << endl;
	cout << "Volume = " << pow(a, 3) << endl;

}

double input() {

	string str;
	bool isFloat, isNegative, isValid = false;

	while (!isValid)
	{

		isValid = true;
		isFloat = false;
		isNegative = false;

		cin >> str;

		if (str[0] == '-')
		{
			isNegative = true;
			str.erase(0, 1);
		}

		for (int i = 0; i < str.length(); i++)
		{

			if ((isdigit(str[i])) || (str[i] == '.' && !isFloat))
			{
				if ((str[i] == '.' && isFloat)) isValid = false;
				if ((str[i] == '.' && !isFloat)) isFloat = true;
			}
			else
			{
				isValid = false;
			}

		}

		if (!isValid) { cout << "Incorrect value! Please try again" << endl; }
		else break;
	}

	if (isNegative) str.insert(0, "-");
	return stod(str);
}