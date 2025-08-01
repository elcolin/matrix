#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ostream>

template <typename T>
class Vector {
    private:
        std::vector<T> array;
    public:
        Vector<T>(std::vector<T> const &array);
        ~Vector<T>() = default;

        std::size_t shape() const;

        T &operator[](std::size_t i);
        T const &operator[](std::size_t i) const;
        void operator+=(const Vector<T> &A);
        void operator-=(const Vector<T> &A);
        void operator*=(const T &scalar);
        bool operator==(const Vector<T> &A) const;

};

template <typename T>
bool Vector<T>::operator==(const Vector<T> &A) const
{
    if (this->shape() != A.shape())
        throw std::invalid_argument("Vectors aren't the same size.");
    for (int i = 0; i < A.shape(); i++)
    {
        if ((*this)[i] != A[i])
            return false;
    }
    return true;
}

template <typename T>
Vector<T> linear_interpolation(Vector<T> const &u, Vector<T> const &v, float t)
{

}

template <typename T>
void Vector<T>::operator*=(const T &scalar)
{
    for (int i = 0; i < this->shape(); i++)
    {
        (*this)[i] *= scalar;
    }
    return;
}

template <typename T>
void Vector<T>::operator+=(const Vector<T> &A)
{
    if (this->shape() != A.shape())
        throw std::invalid_argument("Vectors aren't the same size.");
    for (int i = 0; i < this->shape(); i++)
        array[i] += A[i];
    return;
}

template <typename T>
void Vector<T>::operator-=(const Vector<T> &A)
{
    if (this->shape() != A.shape())
        throw std::invalid_argument("Vectors aren't the same size.");
    for (int i = 0; i < this->shape(); i++)
        array[i] -= A[i];
    return;
}


template <typename T>
Vector<T>::Vector(std::vector<T> const &array) : array(array)
{
    if (array.empty())
        throw std::invalid_argument("Vectors can't be empty.");
}


template <typename T>
std::ostream &operator<<(std::ostream &os, Vector<T> const &vec)
{
    os << "[ " << vec[0] << " ]\n";
    if (vec.shape() == 1)
        return os;
    for (int i = 1; i < vec.shape() - 1; i++)
    {
        os << "| " << vec[i] << " |\n";
    }
    os << "[ " << vec[vec.shape() - 1] << " ]\n";
    return os;
}

template <typename T>
T const &Vector<T>::operator[](std::size_t i) const
{
    if (this->shape() <= i)
        throw std::out_of_range("Index is out of array range.");
    return this->array[i];
}

template <typename T>
T &Vector<T>::operator[](std::size_t i)
{
    if (this->shape() <= i)
        throw std::out_of_range("Index is out of array range.");
    return this->array[i];
}

template <typename T>
std::size_t Vector<T>::shape() const
{
    return this->array.size();
}
