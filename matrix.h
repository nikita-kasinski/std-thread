#pragma once
#include <ostream>
#include <random>

template<class T>
class Matrix
{
public:
    Matrix(std::size_t n, std::size_t m)
    {
        init(n, m);
    }
    Matrix(const Matrix<T>& other)
    {
        std::cout << "Copy was called\n";
        if (this != &other)
        {
            release();
            init(other);
        }
    }
    T& get(std::size_t i, std::size_t j)
    {
        return _matr[i][j];
    }
    T at(std::size_t i, std::size_t j) const
    {
        return _matr[i][j];
    }
    std::size_t getRows() const
    {
        return _n;
    }
    std::size_t getColumns() const
    {
        return _m;
    }
    ~Matrix()
    {
        release();
    }
    bool operator==(const Matrix<T>& other) const
    {
        if ((other._m != this._m) || (other._n != this._n))
        {   
            return false;
        }
        for (std::size_t i = 0; i < _n; ++i)
        {
            for (std::size_t j = 0; j < _m; ++j)
            {
                if (this.at(i, j) != other.at(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }
    Matrix<T>& operator=(const Matrix<T>& other)
    {
        if (&other != this)
        {
            release();
            init(other);
        }
        return *this;
    }
private:
    void init(std::size_t n, std::size_t m)
    {
        _n = n;
        _m = m;
        allocate(n, m);
        for (std::size_t i = 0; i < n; ++i)
        {
            for (std::size_t j = 0; j < m; ++j)
            {
                _matr[i][j] = 0;
            }
        }
    }
    void init(const Matrix<T>& other)
    {
        _n = other._n;
        _m = other._m;
        allocate(other._n, other._m);
        for (std::size_t i = 0; i < other._n; ++i)
        {
            for (std::size_t j = 0; j < other._m; ++j)
            {
                _matr[i][j] = other.at(i, j);
            }
        }
    }
    void allocate(std::size_t n, std::size_t m)
    {
        _matr = new T*[n];
        for (std::size_t i = 0; i < n; ++i)
        {
            _matr[i] = new T[m];
        }
    }
    void release()
    {
        for (std::size_t i = 0; i < _n; ++i)
        {
            delete[] _matr[i];
        }
        delete[] _matr;
    }
    T** _matr;
    size_t _n, _m;
};

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