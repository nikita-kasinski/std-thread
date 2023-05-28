#pragma once
#include <cstdlib>
#include <list>
#include <random>

#include "matrix.h"

template <class T>
Matrix<T> generate(std::size_t n, std::size_t m)
{
    Matrix<T> a(n, m);
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> dist(1, 10);
    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j < m; ++j)
        {
            a.get(i, j) = dist(mt);
        }
    }
    return a;
}

// multiplies firstMatrix with single column of secondMatrix and puts it into corresponding column of result
template <class T>
void multiplyColumn(std::size_t column,
                    const Matrix<T> &firstMatrix,
                    const Matrix<T> &secondMatrix,
                    Matrix<T> &result)
{
    for (std::size_t i = 0; i < firstMatrix.getRows(); ++i)
    {
        result.get(i, column) = 0;
        for (std::size_t j = 0; j < firstMatrix.getColumns(); ++j)
        {
            result.get(i, column) += firstMatrix.at(i, j) * secondMatrix.at(j, column);
        }
    }
}

template <class T>
void multiplyColumns(
    const std::list<std::size_t> &columns,
    const Matrix<T> &a,
    const Matrix<T> &b,
    Matrix<T> &result)
{
    for (auto column : columns)
    {
        multiplyColumn(column, a, b, result);
    }
}

template <class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matr)
{
    constexpr std::size_t width = 5;
    for (std::size_t i = 0; i < matr.getRows(); ++i)
    {
        for (std::size_t j = 0; j < matr.getColumns(); ++j)
        {
            out << std::setw(width) << matr.at(i, j);
        }
        out << "\n";
    }
    out.flush();
    return out;
}