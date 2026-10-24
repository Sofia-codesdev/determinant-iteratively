#include <iostream>
#include <cstdlib>
#include <ctime>



int randint(int min, int max)
{
    return min+(rand()%(max-min+1));
}

int**matrix(int rows, int cols, int min, int max)
{
    int**arr=new int*[rows];
    {
        for(int i=0; i<rows; ++i)
        {
            arr[i]=new int[cols];
        }
    }

    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
        {
            arr[i][j]=randint(min, max);
        }
    }
    return arr;
}

void printmatrix(int**arr, int rows, int cols)
{
    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
        {
            std::cout<<arr[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

void deletematrix(int**arr, int rows)
{
    for(int i=0; i<rows; ++i)
    {
        delete[]arr[i];
    }
    delete[]arr;
}






// 2. Итеративное вычисление определителя (метод Гаусса - приведение к треугольному виду)
int determinantIterative(int** matrix, int n)
{
    if(n == 0) return 0;
    if(n == 1) return matrix[0][0];
    
    // Создаём копию матрицы, чтобы не изменять исходную
    int** temp = new int*[n];
    for(int i=0; i<n; ++i)
    {
        temp[i] = new int[n];
        for(int j=0; j<n; ++j)
        {
            temp[i][j] = matrix[i][j];
        }
    }
    
    double det = 1.0;
    
    for(int i=0; i<n; ++i)
    {
        // Поиск ведущего элемента (для устойчивости)
        int pivotRow = i;
        for(int k=i+1; k<n; ++k)
        {
            if(abs(temp[k][i]) > abs(temp[pivotRow][i]))
            {
                pivotRow = k;
            }
        }
        // Если ведущий элемент равен 0, определитель равен 0
        if(temp[pivotRow][i] == 0)
        {
            for(int i=0; i<n; ++i) delete[] temp[i];
            delete[] temp;
            return 0;
        }
        
        // Перестановка строк (меняет знак определителя)
        if(pivotRow != i)
        {
            for(int j=0; j<n; ++j)
            {
                std::swap(temp[i][j], temp[pivotRow][j]);
            }
            det = -det;
        }
        
        // Приведение к треугольному виду
        for(int k=i+1; k<n; ++k)
        {
            double factor = (double)temp[k][i] / temp[i][i];
            for(int j=i; j<n; ++j)
            {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }
    
    // Произведение диагональных элементов
    for(int i=0; i<n; ++i)
    {
        det *= temp[i][i];
    }
    
    // Очистка памяти
    for(int i=0; i<n; ++i) delete[] temp[i];
    delete[] temp;
    
    return (int)det;
}



int main()
{
    srand(time(0));
    int**A=nullptr;
    int rows=3;
    int cols=3;
    int n=3;
    int min=0;
    int max=5;


    std::cout<<"matrix:\n";
    A=matrix(rows,cols,min,max);
    printmatrix(A,rows,cols);  
    

    std::cout<<"determinant:\n";
    int det=determinantIterative(A,n);
    std::cout<<det;

    return 0;
}