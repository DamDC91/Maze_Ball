#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <array>
#include <iostream>
#include <cmath>

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

Matrix operator*(const Matrix &mat, double sca); //TODO
Matrix operator*(double sca, const Matrix &mat); //TODO

Matrix x_rotation(double theta);

Matrix y_rotation(double theta);

Matrix z_rotation(double theta);

Vector rotate_x(Vector const &vec, double theta);

Vector rotate_y(Vector const &vec, double theta);

Vector rotate_z(Vector const &vec, double theta);

Vector rotate_u(Vector const &vec, Vector const &u, double theta);

#endif //MATRIX_H_INCLUDED
