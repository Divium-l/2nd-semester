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
* \brief Замена предпоследнего элемента массива на максимальный по модулю
* \param array Массив
* \param size Размер массива
**/
void replaceElement(int* array, const size_t size);

/**
* \brief Проверка, оканчивется ли число на необходимую цифру
* \param number Число, необходимое проверить
* \param digit Цифра на которую должно заканчиваться число
 * \return True если оканчивается на нужную цифру
**/
bool hasRequiredLastDigit(const int number, const int digit);

/**
* \brief Поиск размера нового массива для вставки элементов
* \param array Массив
* \param size Размер массива
* \param k Цифра на которую заканчивается элемент
* \return Размер массива
**/
size_t getTempSize(int* array, size_t size, const int k);

/**
* \brief Заполнение нового массива; если номер четный, то значение элемента находится по формуле Ai = i*Di^2, а если нечетный, то по формуле Ai = Di / (i-1)
* \param array Массив
* \param tempArray Новый массив в который вставляют элементы
* \param size Размер массива
* \param tempSize Размер нового массива
* \param k Цифра, которую необходимо вставить
**/
void insertElements(int* array, int* tempArray, size_t size, size_t tempSize, const int k);

/**
* \brief Заполнение нового массива; если номер четный, то значение элемента находится по формуле Ai = i*Di^2, а если нечетный, то по формуле Ai = Di / (i-1)
* \param array Массив
* \param newArray Заполняемый массив
* \param size Размер массива
**/
void fillNewArray(int* array, int* newArray, const size_t size);

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


    //Замена предпоследнего элемента массива на максимальный по модулю
    replaceElement(array, size);
    cout << arrayToString(array, size, "Array after replacement = ") << "\n";


    //Вставить элемент со значением К до и после всех элементов, заканчивающихся на цифру К.
    cout << "k = ";
    int k;
    cin >> k;

    size_t tempSize = getTempSize(array, size, k);
    int* tempArray = new int[tempSize];
    insertElements(array, tempArray, size, tempSize, k);

    size = tempSize;
    array = tempArray;

    

    cout << arrayToString(array, size, "Array after inserting = ") << "\n";


    //Формирование нового массива
    int* newArray = new int[size];
    fillNewArray(array, newArray, size);
    cout << "\n" << arrayToString(array, size, "New array = ") << "\n";


    delete[] array;
    delete[] newArray;
    //delete[] tempArray; ломается

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
            //без этого будет деление на 0
            if (i == 1)
                newArray[i] = array[i];
            else 
                newArray[i] = array[i] / (i - 1);
        }
            
    }
}
