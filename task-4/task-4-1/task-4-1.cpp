#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <sstream>

using namespace std;

/**
* \brief Определяет чётное ли число
* \param value Число, которое необходимо проверить
* \return True если чётное
**/
bool isEven(int value);

/**
* \brief Заполнение массива случайными числами
* \array Массив
* \size Размер массива
* \param min Минимально возможное число
* \param max Максимально возможное число
**/
void randomizeArray(int* array, const size_t size, const int min, const int max);

/**
* \brief Ввод массива с клавиатуры
* \param array Массив
* \param size Размер массива
**/
void manualInput(int* array, const size_t size);

/**
* \brief Конвертация массива строку вида {element_1, element_2, ... ,element_n}
* \param array Массив
* \param size Размер массива
* \param message Сообщение, которое будет выведено перед массивом
**/
string arrayToString(int* array, const size_t size, const string& message);

/**
* \brief Произведение элементов массива, имеющих чётное значение
* \param array Массив
* \param size Размер массива
* \param return Значение произведения 
**/
int calcProduction(int* array, const size_t size);

/**
* \brief Замена элементов массива с нечетными номерами на квадраты их номеров
* \param array Массив
* \param size Размер массива
**/
void replaceElements(int* array, const size_t size);

/**
* \brief Определяет, есть ли в данном массиве положительные элементы, делящиеся на заданное число k с остатком 2
* \param array Массив
* \param size Размер массива
* \param k Заданное число
* \param remainder Остаток
* \return True если есть
**/
bool elementExists(int* array, const size_t size, const int k, const int remainder);

/**
* \brief Выбор заполнеия массива
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

    int* array = new int [size];

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

    //произведение элементов, имеющих четное значение.
    cout << "\nProduction of even elements = " << calcProduction(array, size) << "\n";
    
    //Заменf элементjd массива с нечетными номерами на квадраты их номеров.
    replaceElements(array, size);
    cout << arrayToString(array, size, "\nArray with replaced elements = ") << "\n";

    //Определение, есть ли в данном массиве положительные элементы, делящиеся на заданное число k с остатком 2
    cout << "\nk = ";
    int k;
    cin >> k;

    if (elementExists(array, size, k, REMAINDER))
      cout << "There is at least one element that is positive and has remainder of " << REMAINDER << " of division by " << k << "\n";
    else
      cout << "There is no elements that are positive and have remainder of " << REMAINDER << " of division by " << k << "\n";


    delete [] array;

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

const string& arrayToString(int* array, const size_t size, const string& message = "")
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

    for (size_t i = 0; i < size; i++)
    {
        if (array[i] > 0 && array[i] % k == remainder)
            exist = true;        
    }

    return exist;
}
