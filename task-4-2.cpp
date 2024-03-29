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
* \breif �������� �������
* \param array ������
*/
void destroyArray(int* array);

/**
* \brief ������ �������������� �������� ������� �� ������������ �� ������
* \param array ������
* \param size ������ �������
**/
void replaceElement(int* array, const size_t size);

/**
* \brief ��������, ����������� �� ����� �� ����������� �����
* \param number �����, ����������� ���������
* \param digit ����� �� ������� ������ ������������� �����
 * \return True ���� ������������ �� ������ �����
**/
bool hasRequiredLastDigit(const int number, const int digit);

/**
* \brief ����� ������� ������ ������� ��� ������� ���������
* \param array ������
* \param size ������ �������
* \param k ����� �� ������� ������������� �������
* \return ������ �������
**/
size_t getTempSize(int* array, size_t size, const int k);

/**
* \brief ���������� ������ �������; ���� ����� ������, �� �������� �������� ��������� �� ������� Ai = i*Di^2, � ���� ��������, �� �� ������� Ai = Di / (i-1)
* \param array ������
* \param tempArray ����� ������ � ������� ��������� ��������
* \param size ������ �������
* \param tempSize ������ ������ �������
* \param k �����, ������� ���������� ��������
**/
void insertElements(int* array, int* tempArray, size_t size, size_t tempSize, const int k);

/**
* \brief ���������� ������ �������; ���� ����� ������, �� �������� �������� ��������� �� ������� Ai = i*Di^2, � ���� ��������, �� �� ������� Ai = Di / (i-1)
* \param array ������
* \param newArray ����������� ������
* \param size ������ �������
**/
void fillNewArray(int* array, int* newArray, const size_t size);

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


    //������ �������������� �������� ������� �� ������������ �� ������
    replaceElement(array, size);
    cout << arrayToString(array, size, "Array after replacement = ") << "\n";


    //�������� ������� �� ��������� � �� � ����� ���� ���������, ��������������� �� ����� �.
    cout << "k = ";
    int k;
    cin >> k;

    size_t tempSize = getTempSize(array, size, k);
    int* tempArray = new int[tempSize];
    insertElements(array, tempArray, size, tempSize, k);

    size = tempSize;
    array = tempArray;


    cout << arrayToString(array, size, "Array after inserting = ") << "\n";


    //������������ ������ �������
    int* newArray = new int[size];
    fillNewArray(array, newArray, size);
    cout << "\n" << arrayToString(array, size, "New array = ") << "\n";


    destroyArray(array);
    destroyArray(newArray);

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

void destroyArray(int* array)
{
    if (array == nullptr)
        return;

    delete[] array;
    array = nullptr;
}

void replaceElement(int* array, const size_t size)
{
    int max = array[0];

    for (size_t i = 1; i < size; i++)
    {
        if (abs(array[i]) > max)
            max = abs(array[i]);
    }

    array[size - 2] = max;
}

bool hasRequiredLastDigit(const int number, const int digit)
{
    return abs(number) % 10 == digit;
}

size_t getTempSize(int* array, size_t size, const int k)
{
    int targets = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (hasRequiredLastDigit(array[i], k))
            targets++;
    }

    return size + 2 * targets;
}

void insertElements(int* array, int* tempArray, size_t size, size_t tempSize, const int k)
{

    size_t indexOffset = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (hasRequiredLastDigit(array[i], k))
        {
            tempArray[i + indexOffset] = k;
            tempArray[i + 1 + indexOffset] = array[i];
            tempArray[i + 2 + indexOffset] = k;
            indexOffset += 2;
        }
        else
        {
            tempArray[i + indexOffset] = array[i];
        }
    }

}

void fillNewArray(int* array, int* newArray, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (isEven(i))
            newArray[i] = i * array[i];
        else
        {
            //��� ����� ����� ������� �� 0
            if (i == 1)
                newArray[i] = array[i];
            else
                newArray[i] = array[i] / (i - 1);
        }

    }
}
