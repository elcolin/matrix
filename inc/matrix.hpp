#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <functional>
#include <iterator>

template <typename T>
class Matrix {
    private:
        std::vector<std::vector<T>> array;
    public:
        Matrix(std::vector<std::vector<T>> array);
        std::pair<size_t, size_t> shape() const;
        std::vector<T> const &operator[](std::size_t i) const;
        std::vector<T> &operator[](std::size_t i);
        void operator+=(const Matrix &A);
        void operator-=(const Matrix &A);
        void operator*=(const T &scalar);
};

template <typename T>
void Matrix<T>::operator+=(const Matrix<T> &A)
{
    if (this->shape() != A.shape())
       throw std::invalid_argument("Matrices aren't the same size.");
    for (int i = 0; i < array.size(); i++)
    {
        transform(array[i].begin(), array[i].end(), A[i].begin(), array[i].begin(), std::plus<T>());
    }
}

template <typename T>
void Matrix<T>::operator-=(const Matrix<T> &A)
{
    if (this->shape() != A.shape())
       throw std::invalid_argument("Matrices aren't the same size.");
    for (int i = 0; i < array.size(); i++)
    {
       transform(array[i].begin(), array[i].end(), A[i].begin(), array[i].begin(), std::minus<T>());
    }
}

template <typename T>
void Matrix<T>::operator*=(const T &scalar)
{
    for (int i = 0; i < array.size(); i++)
    {
       transform(array[i].begin(), array[i].end(), array[i].begin(), [&scalar] (T param) {
        return param * scalar; 
       });
    }
}



template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> array) : array(array)
{
    if (array.empty())
        throw std::invalid_argument("Matrices can't be empty.");
    size_t sizeReference = array[0].size();
    for (int i = 0; i < array.size(); i++)
    {
        if (sizeReference != array[i].size())
            throw std::invalid_argument("Matrix isn't rectangular.");
    }
}

template <typename T>
std::pair<size_t, size_t> Matrix<T>::shape() const
{
    return std::pair<size_t, size_t>(array.size(), array.begin()->size());
}

template <typename T>
std::vector<T> const &Matrix<T>::operator[](std::size_t i) const
{
    if (this->shape().first <= i || i < 0)
        throw std::out_of_range("Index is out of array range.");
    return this->array[i];
    
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](std::size_t i)
{
    if (this->shape().first <= i || i < 0)
        throw std::out_of_range("Index is out of array range.");
    return this->array[i];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> const &mat)
{
    size_t max_rows = mat.shape().first;
    size_t max_cols = mat.shape().second;
    for (int rows = 0; rows < max_rows; rows++)
    {
        for (int cols = 0; cols < max_cols; cols++)
        {
            if (cols == 0  && (rows == 0 || rows == max_rows - 1))
                os << "[ ";
            else if (cols == 0)
                os << "| ";
            os << mat[rows][cols];
            if (cols == max_cols - 1 && (rows == 0 || rows == max_rows - 1))
                os << " ]\n";
            else if (cols == max_cols - 1)
                os << " |\n";
            else
                os << ", ";
        }
    }
    return os;
}