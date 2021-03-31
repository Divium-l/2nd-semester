#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class input
{
	public:

		/**
		* \brief Метод, при помощи которого пользователь вводит число типа double
		* \param allowNegative разрешает ввод отрицательтных чисел
		* \param valueInputMessage сообщение, которое будет выведено перед тем, как пользователь будет вводить значение
		* \param valueIncorrectMessage сообщение, которое будет выведено, если пользователь ввёл недопустимый символ
		* \return число типа double
		**/
		static double inputDouble(const bool allowNegative = true, const string& valueInputMessage = "Value: ", const string& valueIncorrectMessage = "Incorrect value!Please try again\n")
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
		
		/**
		* \brief Метод, при помощи которого пользователь вводит число типа int
		* \param allowNegative разрешает ввод отрицательтных чисел
		* \param valueInputMessage сообщение, которое будет выведено перед тем, как пользователь будет вводить значение
		* \param valueIncorrectMessage сообщение, которое будет выведено, если пользователь ввёл недопустимый символ
		* \return число типа int 
		**/
		static int inputInt(const bool allowNegative = true, const string& valueInputMessage = "Value: ", const string& valueIncorrectMessage = "Incorrect value!Please try again\n")
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

		/**
		* \brief Метод, который проверяет является ли строка числом типа double
		* \param str строка, которую ввёл пользователь
		* \param allowNegative позволяет отрицательным числам пройти проверку
		* \return true если строка является числом типа double
		**/
		static bool isValidDouble(string& str, const bool allowNegative)
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

		/**
		* \brief Метод, который проверяет является ли строка числом типа int 
		* \param str строка, которую ввёл пользователь
		* \param allowNegative позволяет отрицательным числам пройти проверку
		* \return true если строка является числом типа int
		**/
		static bool isValidInt(string& str, const bool allowNegative)
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