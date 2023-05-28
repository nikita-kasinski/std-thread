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

int main()
{
    std::size_t columns = 3;
    Matrix<int> a = generate<int>(3, 3);
    Matrix<int> b = generate<int>(3, columns);
    std::cout << a << "\n"
              << b;
    std::list<std::thread> threads;
    for (auto numberOfThreads : std::ranges::iota_view(1u, columns))
    {
        Matrix<int> result(3, 3);
        std::vector<std::list<std::size_t>> columnsByThread(numberOfThreads, std::list<std::size_t>());
        for (auto column : std::ranges::iota_view(1u, columns))
        {
            columnsByThread[column % numberOfThreads].push_back(column);
        }
        for (const auto& columnsList : columnsByThread)
        {
            for (const auto& column : columnsList)
            {
                std::cout << column << ' ';
            }
            std::cout << "\n";
        }
        for (auto thread : std::ranges::iota_view(1u, numberOfThreads))
        {
            threads.emplace_back(
                multiplyColumns<int>,
                std::cref(columnsByThread[thread]),
                std::cref(a),
                std::cref(b),
                std::ref(result));
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
        std::cout << result;
    }
    return 0;
}