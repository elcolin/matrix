#pragma once
#include "vector.hpp"
#include "matrix.hpp"

template <typename T>
Vector<T> linear_combination(std::vector<Vector<T>> const &u, std::vector<float>  const &coefs)
{
    T   res;
    std::vector<T> array;
    if (coefs.size() != u.size())
        throw std::invalid_argument("Vector and coefs are the wrong size.");
    for (int i = 0; i < u[0].shape(); i++)
    {
        for (int j = 0; j < coefs.size(); j++)
        {
            if (u[j].shape()!= u[0].shape())
                throw std::invalid_argument("Vectors aren't all the same size.");    
            res = std::fma(u[j][i], coefs[j], res);
        }
        array.push_back(res);
        res = 0;
    }
    return std::move(Vector<T>(array));
}

template <typename T>
Matrix<T> linear_combination(std::vector<Matrix<T>> const &u, std::vector<float>  const &coefs)
{
    //std::vector<T> res;
    std::vector<std::vector<T>> array;
    if (coefs.size() != u.size())
        throw std::invalid_argument("Vector and coefs are the wrong size.");
    for (int i = 0; i < u[0].shape().second; i++)
    {
        for (int k = 0; k < u[0].shape().first; k++)
        {
            T res = 0;
            array.push_back(std::vector<T>());
            for (int j = 0; j < coefs.size(); j++)
            {
                if (u[j].shape()!= u[0].shape())
                    throw std::invalid_argument("Vectors aren't all the same size.");    
                res = std::fma(u[j][k][i], coefs[j], res);
            }
            array[k].push_back(res);
        }
    }
    return std::move(Matrix<T>(array));
}