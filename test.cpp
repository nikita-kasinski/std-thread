#include <gtest/gtest.h>
#include <sstream>

#include "matrix.h"

TEST(TestMatrix, singleMultiplyColumn)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    Matrix<int> b(rows, columns);
    Matrix<int> result(rows, columns);
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            a.get(i, j) = 3 * i + j + 1;
            b.get(i, j) = 3 * j + i + 1;
        }
    }
    multiplyColumn(0, a, b, result);
    EXPECT_EQ(result.at(0, 0), 14);
    EXPECT_EQ(result.at(1, 0), 32);
    EXPECT_EQ(result.at(2, 0), 50);
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 1; j < columns; ++j)
        {
            EXPECT_EQ(result.at(i, j), 0);
        }
    }
}

TEST(TestMatrix, AllMultiplyColumns)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    Matrix<int> b(rows, columns);
    Matrix<int> result(rows, columns);
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            a.get(i, j) = 3 * i + j + 1;
            b.get(i, j) = 3 * j + i + 1;
        }
    }
    multiplyColumn(0, a, b, result);
    multiplyColumn(1, a, b, result);
    multiplyColumn(2, a, b, result);
    EXPECT_EQ(result.at(0, 0), 14);
    EXPECT_EQ(result.at(1, 0), 32);
    EXPECT_EQ(result.at(2, 0), 50);
    EXPECT_EQ(result.at(0, 1), 32);
    EXPECT_EQ(result.at(1, 1), 77);
    EXPECT_EQ(result.at(2, 1), 122);
    EXPECT_EQ(result.at(0, 2), 50);
    EXPECT_EQ(result.at(1, 2), 122);
    EXPECT_EQ(result.at(2, 2), 194);
}

TEST(TestMatrix, TestMultiplyColumnsSingle)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    Matrix<int> b(rows, columns);
    Matrix<int> result(rows, columns);
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            a.get(i, j) = 3 * i + j + 1;
            b.get(i, j) = 3 * j + i + 1;
        }
    }
    multiplyColumns(std::list<std::size_t>{1}, a, b, result);
    EXPECT_EQ(result.at(0, 1), 32);
    EXPECT_EQ(result.at(1, 1), 77);
    EXPECT_EQ(result.at(2, 1), 122);
}

TEST(TestMatrix, TestMultiplyColumnsDouble)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    Matrix<int> b(rows, columns);
    Matrix<int> result(rows, columns);
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            a.get(i, j) = 3 * i + j + 1;
            b.get(i, j) = 3 * j + i + 1;
        }
    }
    multiplyColumns(std::list<std::size_t>{1, 2}, a, b, result);
    EXPECT_EQ(result.at(0, 1), 32);
    EXPECT_EQ(result.at(1, 1), 77);
    EXPECT_EQ(result.at(2, 1), 122);
    EXPECT_EQ(result.at(0, 2), 50);
    EXPECT_EQ(result.at(1, 2), 122);
    EXPECT_EQ(result.at(2, 2), 194);
}

TEST(TestMatrix, TestMultiplyColumnsAll)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    Matrix<int> b(rows, columns);
    Matrix<int> result(rows, columns);
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            a.get(i, j) = 3 * i + j + 1;
            b.get(i, j) = 3 * j + i + 1;
        }
    }
    multiplyColumns(std::list<std::size_t>{1, 2, 0}, a, b, result);
    EXPECT_EQ(result.at(0, 0), 14);
    EXPECT_EQ(result.at(1, 0), 32);
    EXPECT_EQ(result.at(2, 0), 50);
    EXPECT_EQ(result.at(0, 1), 32);
    EXPECT_EQ(result.at(1, 1), 77);
    EXPECT_EQ(result.at(2, 1), 122);
    EXPECT_EQ(result.at(0, 2), 50);
    EXPECT_EQ(result.at(1, 2), 122);
    EXPECT_EQ(result.at(2, 2), 194);
}

TEST(TestMatrix, TestGetColumns)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    EXPECT_EQ(a.getColumns(), columns);
}

TEST(TestMatrix, TestGetRows)
{
    constexpr std::size_t rows = 3;
    constexpr std::size_t columns = 3;
    Matrix<int> a(rows, columns);
    EXPECT_EQ(a.getRows(), rows);
}