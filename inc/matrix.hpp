#include <iostream>
#include <string>
#include <vector>
#include <ostream>

template <typename T>
class Matrix {
    private:
        std::vector<std::vector<T>> array;
        Matrix() = default;
    public:
        Matrix(std::vector<std::vector<T>> array);
        std::pair<size_t, size_t> shape() const;

};

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> array) : array(array)
{
    if (array.empty())
        throw std::length_error("Matrices can't be empty.");
    size_t sizeReference = array[0].size();
    for (int i = 0; i < array.size(); i++)
    {
        if (sizeReference != array[i].size())
            throw std::length_error("Matrix isn't rectangular.");
    }
}

template <typename T>
std::pair<size_t, size_t> Matrix<T>::shape() const
{

}