//
// Created by Ben Roberts on 6/21/2023.
//

#include "testing.h"

// Function to call LinReg with sample dataset of n points.
double testLinReg(int times, int numPoints) {
    double elapsed_time = 0.0;

    for (int i = 0; i < times; i++) {
        Point* points = createPoints(numPoints);
        double start_time = clock();
        Point res = LinearRegression(points, numPoints);
        double end_time = clock();
        elapsed_time += (end_time - start_time) / CLOCKS_PER_SEC;
    }
    return elapsed_time / times;
}

// Function to test LinReg with sample dataset of n vectors in d dimensions.
double testLinReg2(int times, int numPoints, int dimensions) {
    double elapsed_time = 0.0;

    for (int i = 0; i < times; i++) {
        Matrix points = createPointsND(dimensions, numPoints);
        double start_time = clock();
        NDLine res = linearRegression2(points);
        double end_time = clock();
        elapsed_time += (end_time - start_time) / CLOCKS_PER_SEC;
    }
    return elapsed_time / times;
}

// Function to test row echelon form method reduction on a nxn matrix.
double testRREF(int times, int matrixSize) {
    double elapsed_time = 0.0;

    for (int i = 0; i < times; i++) {
        Matrix m = createSquareMatrix(matrixSize);
        double start_time = clock();
        Matrix res = RREF(m);
        double end_time = clock();
        elapsed_time += (end_time - start_time) / CLOCKS_PER_SEC;
    }
    return elapsed_time / times;
}

// Function to test upper triangular reduction on a nxn matrix.
double testReduce(int times, int matrixSize) {
    double elapsed_time = 0.0;

    for (int i = 0; i < times; i++) {
        Matrix m = createSquareMatrix(matrixSize);
        double start_time = clock();
        Matrix res = reduce(m);
        double end_time = clock();
        elapsed_time += (end_time - start_time) / CLOCKS_PER_SEC;
    }
    return elapsed_time / times;
}

// Function to calculate the determinant of a nxn matrix.
double testDet(int times, int matrixSize) {
    double elapsed_time = 0.0;

    for (int i = 0; i < times; i++) {
        Matrix m = createSquareMatrix(matrixSize);
        double start_time = clock();
        double res = det(m);
        double end_time = clock();
        elapsed_time += (end_time - start_time) / CLOCKS_PER_SEC;
    }
    return elapsed_time / times;
}

Point* createPoints(int numPoints) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    auto* points = new Point[numPoints];
    double mockM = dist(gen);
    double mockB = dist(gen);
    // Generate points and add random noise to y value.
    for (int i = 0; i < numPoints; i++) {
        double x = i;
        double noise = dist(gen);
        double y = mockM * x + mockB + noise;
        points[i] = {x, y};
    }
    return points;
}

Matrix createSquareMatrix(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    std::uniform_int_distribution<int> depDist(0, 1); // 0 for independent, 1 for dependent
    Matrix m{};
    m.rows = size;
    m.cols = size;
    m.rowVector = new Vector[size];
    // Determine if the matrix should be linearly dependent
    bool isDependent = (depDist(gen) == 1);

    // Generate the vectors for the matrix
    for (int i = 0; i < size; i++) {
        m.rowVector[i].dim = size;
        m.rowVector[i].vectorArray = new double[size];
        double randDouble = dist(gen);
        if (isDependent && i > 0) {
            for (int j = 0; j < size; j++) {
                m.rowVector[i].vectorArray[j] = m.rowVector[0].vectorArray[j] * randDouble;
            }
        } else {
            for (int j = 0; j < size; j++) {
                randDouble = dist(gen);
                m.rowVector[i].vectorArray[j] = randDouble;
            }
        }
    }
    return m;
}

Matrix createPointsND(int dimensions, int numPoints) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    auto* rowVector = new Vector[numPoints];
    // Generate random slopes for each dimension
    auto* slopes = new double[dimensions];
    for (int i = 0; i < dimensions; i++) {
        slopes[i] = dist(gen);
    }

    for (int i = 0; i < numPoints; i++) {
        rowVector[i].vectorArray = new double[dimensions];
        for (int j = 0; j < dimensions; j++) {
            double x = i;
            double noise = dist(gen);
            double y = slopes[j] * x + noise;
            rowVector[i].vectorArray[j] = y;
        }
    }
    Matrix points{};
    points.rows = numPoints;
    points.cols = dimensions;
    points.rowVector = rowVector;
    return points;
}