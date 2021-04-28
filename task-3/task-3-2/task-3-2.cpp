#include <iostream>
#include <cmath>

using namespace std;

/**
* \brief Расчёт рекурентного выражения
* \param k Индекс члена ряда
* \return Значение рекурентного соотношения
*/
double recurrent(const size_t k);

/**
* \brief Расчёт суммы ряды
* \param n Колличество членов ряда
* \return Значение суммы
*/
double getSum(const size_t n);

/**
* \brief Расчёт суммы ряды
* \param eps Точность расчёта
* \return Значение суммы
*/
double getSum(const double eps);

int main()
{
    cout << "Sum of first n-members\n" << "n = ";
    size_t n;
    cin >> n;

    cout << "Sum = " << getSum(n) << "\n\n";

    cout << "Sum with precision of e\n" << "e = ";
    double eps;
    cin >> eps;

    cout << "Sum = " << getSum(eps) << "\n";

    return 0;
}

double recurrent(const size_t k)
{
    return (-1.0) / ((k + 2) * (k + 1));
}

double getSum(const size_t n)
{
    double previous = 1, sum = previous, current;

    for (size_t k = 0; k < n; k++)
    {
        current = recurrent(k) * previous;
        previous = current;

        sum += previous;
    }

    return sum;
}

double getSum(const double eps)
{
    double previous = 1, sum = previous, current;

    for (size_t k = 0; abs(previous) > eps; k++)
    {
        current = recurrent(k) * previous;
        previous = current;

        sum += previous;
    }

    return sum;
}