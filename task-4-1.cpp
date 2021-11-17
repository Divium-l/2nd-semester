#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <sstream>

using namespace std;

/**
* \brief ���������� ������ �� �����
* \param value �����, ������� ���������� ���������
* \return True ���� ������
**/
bool isEven(int value);

/**
* \brief ���������� ������� ���������� �������
* \array ������
* \size ������ �������
* \param min ���������� ��������� �����
* \param max ����������� ��������� �����
**/
void randomizeArray(int* array, const size_t size, const int min, const int max);

/**
* \brief ���� ������� � ����������
* \param array ������
* \param size ������ �������
**/
void manualInput(int* array, const size_t size);

/**
* \brief ����������� ������� ������ ���� {element_1, element_2, ... ,element_n}
* \param array ������
* \param size ������ �������
* \param message ���������, ������� ����� �������� ����� ��������
**/
string arrayToString(int* array, const size_t size, const string& message);

/**
* \brief ������������ ��������� �������, ������� ������ ��������
* \param array ������
* \param size ������ �������
* \param return �������� ������������
**/
int calcProduction(int* array, const size_t size);

/**
* \brief ������ ��������� ������� � ��������� �������� �� �������� �� �������
* \param array ������
* \param size ������ �������
**/
void replaceElements(int* array, const size_t size);

/**
* \brief ����������, ���� �� � ������ ������� ������������� ��������, ��������� �� �������� ����� k � �������� 2
* \param array ������
* \param size ������ �������
* \param k �������� �����
* \param remainder �������
* \return True ���� ����
**/
bool elementExists(int* array, const size_t size, const int k, const int remainder);

/**
* \brief ����� ��������� �������
**/
enum class FillType
{
    randomize = 1,
    manual = 2
};

int main()
{

    const int MIN = -15, MAX = 15, REMAINDER = 2;

    cout << "Please input array length: ";
    size_t size;
    cin >> size;

    int* array = new int[size];

    cout << "Choose an option:\n" << "1) Generate array\n" << "2) Manual input\n" << "1 or 2: ";
    int choice;
    cin >> choice;

    const auto fillType = static_cast<FillType>(choice);

    switch (fillType)
    {
    case FillType::randomize:
    {
        randomizeArray(array, size, MIN, MAX);
        cout << arrayToString(array, size, "Your array = ") << "\n";
        break;
    }
    case FillType::manual:
    {
        manualInput(array, size);
        break;
    }
    default:
        break;
    }

    //������������ ���������, ������� ������ ��������.
    cout << "\nProduction of even elements = " << calcProduction(array, size) << "\n";

    //�����f �������jd ������� � ��������� �������� �� �������� �� �������.
    replaceElements(array, size);
    cout << arrayToString(array, size, "\nArray with replaced elements = ") << "\n";

    //�����������, ���� �� � ������ ������� ������������� ��������, ��������� �� �������� ����� k � �������� 2
    cout << "\nk = ";
    int k;
    cin >> k;

    if (elementExists(array, size, k, REMAINDER))
        cout << "There is at least one element that is positive and has remainder of " << REMAINDER << " of division by " << k << "\n";
    else
        cout << "There is no elements that are positive and have remainder of " << REMAINDER << " of division by " << k << "\n";

    if (array != nullptr)
    {
        delete[] array;
        array = nullptr;
    }
    delete[] array;

    return 0;
}

bool isEven(int value)
{
    return (value % 2 == 0);
}

void randomizeArray(int* array, const size_t size, const int min, const int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    const uniform_int_distribution<> uniformIntDistribution(min, max);

    for (size_t i = 0; i < size; ++i)
        array[i] = uniformIntDistribution(gen);

}

void manualInput(int* array, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << "array[" << i << "] = ";
        cin >> array[i];
    }
}

string arrayToString(int* array, const size_t size, const string& message = "")
{
    std::stringstream buffer;
    buffer << message << "{" << array[0];

    for (size_t i = 1; i < size; ++i)
    {
        buffer << ", " << array[i];
    }

    buffer << "}";

    return buffer.str();
}

int calcProduction(int* array, const size_t size)
{
    int prod = 1;
    for (size_t i = 0; i < size; ++i)
    {
        if (isEven(array[i]))
            prod *= array[i];
    }

    return prod;
}

void replaceElements(int* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (!isEven(i))
            array[i] = pow(i, 2);
    }
}

bool elementExists(int* array, const size_t size, const int k, const int remainder)
{

    bool exist = false;

    for (size_t i = 0; i < size && !exist; i++)
    {
        if (array[i] > 0 && array[i] % k == remainder)
            exist = true;
    }

    return exist;
}
