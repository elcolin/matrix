#include <iostream>
#include <string>
#include <vector>
#include <ostream>

template <typename T>
class Vector {
    private:
        std::vector<T> list;
        Vector<T>() = default;
    public:
        Vector<T>(std::vector<T> &list);
        ~Vector<T>() = default;
        std::size_t shape() const;

        T const &operator[](std::size_t i) const;
        T &operator[](std::size_t i);
        void operator+=(const Vector<T> &a);
        void operator-=(const Vector<T> &a);
        void operator*=(const T &scalar);

};

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
void Vector<T>::operator+=(const Vector<T> &a)
{
    if (this->shape() != a.shape())
        throw std::length_error("Vectors aren't the same size.");
    for (int i = 0; i < this->shape(); i++)
        list[i] += a[i];
    return;
}

template <typename T>
void Vector<T>::operator-=(const Vector<T> &a)
{
    if (this->shape() != a.shape())
        throw std::length_error("Vectors aren't the same size.");
    for (int i = 0; i < this->shape(); i++)
        list[i] -= a[i];
    return;
}


template <typename T>
Vector<T>::Vector(std::vector<T> &list) : list(list)
{
    if (list.empty())
        throw std::length_error("Vectors can't be empty.");
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Vector<T> const &vec)
{
    for (int i = 0; i < vec.shape(); i++)
    {
        os << "[ " << vec[i] << " ]\n";
    }
    return os;
}

template <typename T>
T const &Vector<T>::operator[](std::size_t i) const
{
    if (this->shape() <= i || i < 0)
        throw std::out_of_range("Index is out of list range.");
    return this->list[i];
}

template <typename T>
T &Vector<T>::operator[](std::size_t i)
{
    if (this->shape() <= i || i < 0)
        throw std::out_of_range("Index is out of list range.");
    return this->list[i];
}

template <typename T>
std::size_t Vector<T>::shape() const
{
    return this->list.size();
}
