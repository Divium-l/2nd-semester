#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

using namespace std;

/**
* \brief Выбор заполнеия массива
**/
enum class FillType
{
    randomize = 1,
    manual = 2
};

/**
 *\brief Создание двумерного массива
 *\param row Кол-во строк
 *\param col Кол-во столбцов
 *\return Двумерный массив
 */
int** initializeArray(const size_t row, const size_t col);

/**
 *\brief Заполнение массива рандомными числами
 *\param matrix Двумерный массив
 *\param row Кол-во строк
 *\param col Кол-во столбцов
 *\param min Минимальное значение
 *\param max Максимальное значение
 */
void randomizeArray(int** matrix, const size_t row, const size_t col, const int min, const int max);

/**
 *\brief Заполнение массива от руки
 *\param matrix Двумерный массив
 *\param row Кол-во строк
 *\param col Кол-во столбцов
 */
void manualInput(int** matrix, const size_t row, const size_t col);

/**
 *\brief Конвертация двумерного массива в строку
 *\param matrix Двумерный мвссив
 *\param row Кол-во строк
 *\param col Кол-во столбцов
 *\param width Ширина столбцов матрицы
 *\param message Сообщение, которое будет выведено перед массивом
 *\return Матрица в читаемом виде
 */
string arrayToString(int** matrix, const size_t row, const size_t col, const int width, const string& message);

/**
 *\brief Поиск минимального элемента в столбце
 *\param matrix Двумерный мвссив
 *\param row Кол-во строк
 *\param currentCol Проверяемый столбец
 *\return Минимальное значение
 */
int findMin(int** matrix, const size_t row, const size_t currentCol);

/**
 *\brief Замена минимальных элементов в столбце
 *\param matrix Двумерный массив
 *\param row Кол-во строк
 *\param col Кол-во столбцов
 */
void replaceElements(int** matrix, const size_t row, const size_t col);

/**
 *\brief Поиск нового размера двумерного массива
 *\param matrix Двумерный массив
 *\param row Кол-во строк
 *\param col Кол-во столбцов
 *\return Новое кол-во столбцов
 */
int getNewColSize(int** matrix, const size_t row, const size_t col);

/**
 *\brief Поиск нового размера двумерного массива
 *\param oldMatrix Двумерный массив, в котором необходимо удалить столбцы
 *\param row Кол-во строк
 *\param oldCol Кол-во столбцов в старой матрице
 *\param newCol Кол-во столбцов в новой матрице
 *\return Новый двумерный массив
 */
int** getNewArray(int** oldMatrix, const size_t row, const size_t oldCol, const size_t newCol);


int main()
{
    const int MIN = -9, MAX = 9, WIDTH = 2;
    size_t row, col;

    cout << "Please input matrix dimensons\nrow x col: ";
    cin >> row >> col;

    int** matrix = initializeArray(row, col);

    cout << "Choose an option:\n" << "1) Generate matrix\n" << "2) Manual input\n" << "1 or 2: ";
    unsigned int choice;
    cin >> choice;

    const auto fillType = static_cast<FillType>(choice);

    switch (fillType)
    {
        case FillType::randomize:
        {
            randomizeArray(matrix, row, col, MIN, MAX);
            break;
        }
        case FillType::manual:
        {
            manualInput(matrix, row, col); cout << matrix << "\n";
            break;
        }
        default:
            break;
    }

    
    

    cout << arrayToString(matrix, row, col, WIDTH, "matrix: \n") << "\n\n";

    //замена
    replaceElements(matrix, row, col);
    cout << arrayToString(matrix, row, col, WIDTH, "matrix with replaced elements: \n") << "\n\n";

    //удаление
    size_t newCol = getNewColSize(matrix, row, col); 
    matrix = getNewArray(matrix, row, col, newCol);
    col = newCol;
    cout << arrayToString(matrix, row, col, WIDTH, "matrix with deleted columns: \n") << "\n\n";

}

int** initializeArray(const size_t row, const size_t col)
{
    int** matrix = new int* [row];

    for (size_t i = 0; i < row; i++)
    {
        matrix[i] = new int[col];
    }

    return matrix;
}

void randomizeArray(int** matrix, const size_t row, const size_t col, const int min, const int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    const uniform_int_distribution<> uniformIntDistribution(min, max);

    for (size_t i = 0; i < row; ++i)
        for (size_t j = 0; j < col; ++j)
            matrix[i][j] = uniformIntDistribution(gen);

}

void manualInput(int** matrix, const size_t row, const size_t col)
{
    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
        {
            cout << "array[" << i << ", " << j << "] = ";
            cin >> matrix[i][j];
        }
}

string arrayToString(int** matrix, const size_t row, const size_t col, const int width, const string& message = "") //{{1,2},{3,4},{5,6}}
{
    std::stringstream buffer;

    buffer << message;

    for (size_t i = 0; i < row; ++i)
    {
        if (i != row && i != 0)
            buffer << "\n";

        buffer << "{";

        for (size_t j = 0; j < col; ++j)
        {
            buffer << setw(width) << matrix[i][j];
            if (j != col - 1)
                buffer << ", ";
        }

        buffer << "}";
    }

    return buffer.str();
}

int findMin(int** matrix, const size_t row, const size_t currentCol)
{
    int min = abs(matrix[0][currentCol]);

    for (size_t i = 1; i < row; i++)
        if (abs(matrix[i][currentCol]) < min)
            min = abs(matrix[i][currentCol]);

    return min;
}

void replaceElements(int** matrix, const size_t row, const size_t col)
{
    int min;

    for (size_t j = 0; j < col; j++)
    {
        min = findMin(matrix, row, j);

        //замена минимального(ых) элементов на 0
        for (size_t i = 0; i < row; i++)
            if (abs(matrix[i][j]) == min)
                matrix[i][j] = 0;
    }

}

int getNewColSize(int** matrix, const size_t row, const size_t col)
{
    size_t newCol = col;

    for (size_t j = 0; j < col; j++)
        if (matrix[0][j] > matrix[row - 1][j])
            newCol--;

    return newCol;
}

int** getNewArray(int** oldMatrix, const size_t row, const size_t oldCol, const size_t newCol)
{
    size_t colOffset = 0;

    int** newMatrix = initializeArray(row, newCol);

    for (size_t j = 0; j < oldCol; j++)
    {
        if (oldMatrix[0][j] > oldMatrix[row - 1][j])
            colOffset++;
        else
            for (size_t i = 0; i < row; i++)
                newMatrix[i][j - colOffset] = oldMatrix[i][j];
    }

    return newMatrix;
}
