#ifndef PROJETTRANSVERSE_MATRIX_H
#define PROJETTRANSVERSE_MATRIX_H


#include <array>
#include <iostream>
#include "geometry.h"

class Matrix
{
private:
    std::array<double, 9> data_;
public:
    explicit Matrix() : data_() {}

    explicit Matrix(const std::array<double, 9> &data, std::size_t n = 0) : data_(data) {}

    double &operator()(std::size_t i, std::size_t j);

    double operator()(std::size_t i, std::size_t j) const;
};

std::ostream &operator<<(std::ostream &os, Matrix const &mat);

Vector operator*(const Matrix &mat, const Vector &vec);
Matrix operator*(const Matrix &m1, const Matrix &m2);

#endif //PROJETTRANSVERSE_MATRIX_H
