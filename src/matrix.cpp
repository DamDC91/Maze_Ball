#include "matrix.h"

double &Matrix::operator()(std::size_t i, std::size_t j)
{
    return data_[j + i * 3];
}

double Matrix::operator()(std::size_t i, std::size_t j) const
{
    return data_[j + i * 3];
}

std::ostream &operator<<(std::ostream &os, Matrix const &mat)
{
    for (std::size_t i = 0; i != 3; ++i)
    {
        for (std::size_t j = 0; j != 3; ++j)
            os << mat(i, j) << "\t";
        os << "\n";
    }
    return os;
}

Vector operator*(const Matrix &mat, const Vector &vec)
{
    Vector res;
    res.x = vec.x * mat(0, 0) + vec.y * mat(0, 1) + vec.z * mat(0, 2);
    res.y = vec.x * mat(1, 0) + vec.y * mat(1, 1) + vec.z * mat(1, 2);
    res.z = vec.x * mat(2, 0) + vec.y * mat(2, 1) + vec.z * mat(2, 2);
    return res;
}

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    Matrix m3;
    double s;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m3(i, j) = 0;
            for (int k = 0; k < 3; ++k)
            {
                m3(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return m3;
}