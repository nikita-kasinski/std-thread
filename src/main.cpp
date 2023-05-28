#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <iomanip>
#include <ranges>
#include <list>
#include <future>
#include <chrono>

#include "matrix.h"
#include "matrix-utils.h"

int main()
{
    std::size_t columns = 1000;
    std::size_t rows = columns;
    std::size_t maximumThreads = std::thread::hardware_concurrency();
    std::cout << "Hardware concurrency: " << maximumThreads << "\n";
    Matrix<int> a = generate<int>(rows, columns);
    Matrix<int> b = generate<int>(rows, columns);
    //std::cout << a << "\n"
    //          << b;
    for (auto numberOfThreads : std::ranges::iota_view(1u, 2 * maximumThreads + 1))
    {
        std::list<std::thread> threads;
        Matrix<int> result(rows, columns);
        std::vector<std::list<std::size_t>> columnsByThread(numberOfThreads, std::list<std::size_t>());
        for (auto column : std::ranges::iota_view(0u, columns))
        {
            columnsByThread[column % numberOfThreads].push_back(column);
        }
        std::cout << "Number of threads: " << numberOfThreads << "\n";
        /*std::cout << "Columns partition: \n";
        for (const auto& columnsList : columnsByThread)
        {
            for (const auto& column : columnsList)
            {
                std::cout << column << ' ';
            }
            std::cout << "\n";
        }*/
        auto begin = std::chrono::steady_clock::now();
        for (auto thread : std::ranges::iota_view(0u, numberOfThreads))
        {
            threads.emplace_back(
                [](
                    std::list<std::size_t> columns,
                    const Matrix<int>& a,
                    const Matrix<int>& b,
                    Matrix<int>& result
                ){
                    multiplyColumns<int>(
                        columns,
                        a,
                        b,
                        result);
                },
                std::cref(columnsByThread[thread]),
                std::cref(a),
                std::cref(b),
                std::ref(result)
                );
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
        auto end = std::chrono::steady_clock::now();
        auto time_ns = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "Time elapsed: " << time_ns.count() << " microseconds\n\n";
        //std::cout << "Result:\n" << result << "\n"; 
        std::cout.flush();
    }
    return 0;
}