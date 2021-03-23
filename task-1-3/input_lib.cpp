#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class input
{
	public:

		static double inputDouble(const bool allowNegative = true, const string valueInputMessage = "Value: ", const string valueIncorrectMessage = "Incorrect value!Please try again\n")
		{

			string str;
			bool isValid = false;

			while (!isValid)
			{

				isValid = true;

				cout << valueInputMessage;
				cin >> str;

				isValid = isValidDouble(str, allowNegative);

				if (!isValid)
					cout << valueIncorrectMessage;

			}

			return stod(str);
		}
	
		static int inputInt(const bool allowNegative = true, const string valueInputMessage = "Value: ", const string valueIncorrectMessage = "Incorrect value!Please try again\n")
		{

			string str;
			bool isValid = false;

			while (!isValid)
			{

				isValid = true;

				cout << valueInputMessage;
				cin >> str;

				isValid = isValidInt(str, allowNegative);

				if (!isValid)
					cout << valueIncorrectMessage;

			}

			return stoi(str);
		}

	private:

		static bool isValidDouble(string str, const bool allowNegative)
		{

			bool isValid = true, isFloat = false;
			int i = 0;

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

		static bool isValidInt(string str, const bool allowNegative)
		{

			bool isValid = true;
			int i = 0;

			if (allowNegative && str[0] == '-' && str != "-")
				str.erase(0, 1);

			while (i < str.length() && isValid)
			{

				if (!isdigit(str[i]))
					isValid = false;

				i++;
			}

			return isValid;
		}
};