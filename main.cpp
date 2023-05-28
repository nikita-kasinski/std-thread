#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <iomanip>
#include <ranges>
#include <list>

#include "matrix.h"

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
int main()
{
    std::size_t columns = 3;
    Matrix<int> a = generate<int>(3, 3);
    Matrix<int> b = generate<int>(3, columns);
    std::cout << a << "\n"
              << b;
    Matrix<int> result(3, 3);
    std::list<std::thread> threads;
    for (auto numberOfThreads : std::ranges::iota_view(1u, columns))
    {
        std::vector<std::list<std::size_t>> columnsByThread(numberOfThreads, std::list<std::size_t>());
        for (auto column : std::ranges::iota_view(1u, columns))
        {
            columnsByThread[column % numberOfThreads].push_back(column);
        }
        for (auto thread : std::ranges::iota_view(1u, numberOfThreads))
        {
            threads.emplace_back(
                multiplyColumns<int>,
                std::ref(columnsByThread[thread]),
                std::ref(a),
                std::ref(b),
                std::ref(result));
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
    }
    std::cout << result;
    return 0;
}