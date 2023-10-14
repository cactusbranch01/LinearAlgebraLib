//
// Created by benrr on 6/21/2023.
//

#ifndef AI_TESTING_H
#define AI_TESTING_H
#include "LinearRegression.h"
#include "VectorGeometry.h"
#include <ctime>
#include <iostream>

class testing {
};

double testLinReg(int times, int numPoints);
double testLinReg2(int times, int numVectors, int dimensions);
double testRREF(int times, int matrixSize);
double testReduce(int times, int matrixSize);
double testDet(int times, int matrixSize);
Point* createPoints(int numPoints);
Matrix createSquareMatrix(int size);
Matrix createPointsND(int dimensions, int numPoints);

#endif //AI_TESTING_H
