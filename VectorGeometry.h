//
// Created by Ben Roberts on 6/16/2023.
//

#include <stdexcept>
#include <random>
#include <iostream>

#ifndef AI_GEOMETRY_H
#define AI_GEOMETRY_H

struct Point {
    double x;
    double y;
};

struct Vector {
    int dim;
    double* vectorArray;
};

struct NDLine {
    Vector vec1;
    Vector vec2;
};

struct Matrix {
    int rows;
    int cols;
    Vector* rowVector;
};

Matrix createMatrix(Vector* vectors, int numVectors);
Vector addVectors (Matrix m);
void printPoint(Point p);
void printVector(Vector v);
void printMatrix(Matrix m);
Matrix reduce(Matrix m);
double det(Matrix& m);
Matrix RREF(Matrix m);

#endif //AI_GEOMETRY_H
