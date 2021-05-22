#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

using namespace std;

/**
* \brief ����� ��������� �������
**/
enum class FillType
{
    randomize = 1,
    manual = 2
};

/**
 *\brief �������� ���������� �������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 *\return ��������� ������
 */
int** initializeArray(const size_t row, const size_t col);

/**
 *\brief ������������ ������ (�������� ���������� �������)
 *\param array ��������� ������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 */
void destroyArray(int** array, const size_t row, const size_t col);

/**
 *\brief ���������� ������� ���������� �������
 *\param matrix ��������� ������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 *\param min ����������� ��������
 *\param max ������������ ��������
 */
void randomizeArray(int** matrix, const size_t row, const size_t col, const int min, const int max);

/**
 *\brief ���������� ������� �� ����
 *\param matrix ��������� ������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 */
void manualInput(int** matrix, const size_t row, const size_t col);

/**
 *\brief ����������� ���������� ������� � ������
 *\param matrix ��������� ������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 *\param width ������ �������� �������
 *\param message ���������, ������� ����� �������� ����� ��������
 *\return ������� � �������� ����
 */
string arrayToString(int** matrix, const size_t row, const size_t col, const int width, const string& message);

/**
 *\brief ����� ������������ �������� � �������
 *\param matrix ��������� ������
 *\param row ���-�� �����
 *\param currentCol ����������� �������
 *\return ����������� ��������
 */
int findMin(int** matrix, const size_t row, const size_t currentCol);

/**
 *\brief ������ ����������� ��������� � �������
 *\param matrix ��������� ������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 */
void replaceElements(int** matrix, const size_t row, const size_t col);

/**
 *\brief ����� ������ ������� ���������� �������
 *\param matrix ��������� ������
 *\param row ���-�� �����
 *\param col ���-�� ��������
 *\return ����� ���-�� ��������
 */
int getNewColSize(int** matrix, const size_t row, const size_t col);

/**
 *\brief ����� ������ ������� ���������� �������
 *\param oldMatrix ��������� ������, � ������� ���������� ������� �������
 *\param row ���-�� �����
 *\param oldCol ���-�� �������� � ������ �������
 *\param newCol ���-�� �������� � ����� �������
 *\return ����� ��������� ������
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

    //������
    replaceElements(matrix, row, col);
    cout << arrayToString(matrix, row, col, WIDTH, "matrix with replaced elements: \n") << "\n\n";

    //��������
    size_t newCol = getNewColSize(matrix, row, col);
    matrix = getNewArray(matrix, row, col, newCol);
    col = newCol;
    cout << arrayToString(matrix, row, col, WIDTH, "matrix with deleted columns: \n") << "\n\n";

    destroyArray(matrix, col, row);
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

void destroyArray(int** array, const size_t row, const size_t col)
{
    if (array == nullptr)
        return;

    for (size_t i = 0; i < row; i++)
        delete[] array[i];

    delete[] array;
    array = nullptr;
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

        //������ ������������(��) ��������� �� 0
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

    destroyArray(oldMatrix, row, oldCol);

    return newMatrix;
}
