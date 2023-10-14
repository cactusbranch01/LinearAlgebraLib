//
// Created by Ben Roberts on 6/16/2023.
//

#include "LinearRegression.h"

// Function to calculate linear regression and produce a point of the result (x: the slope, y: the bias).
Point LinearRegression (Point* points, int size) {
    double sumX = 0.0;
    double sumY = 0.0;
    double sumXY = 0.0;
    double sumXSquare = 0.0;

    for (int i = 0; i < size; i++) {
        Point point = points[i];
        sumX += point.x;
        sumY += point.y;
        sumXY += point.x * point.y;
        sumXSquare += point.x * point.x;
    }
    double b = (size * sumXY - sumX * sumY) / (size * sumXSquare - sumX * sumX);
    double s = (sumY - b * sumX) / size;
    return Point {s, b};
}

// Function to calculate linear regression and produce two vectors representing the line through the dimensions of the points.
NDLine linearRegression2(Matrix points) {
    int totalDimensions = points.cols;
    int totalVectors = points.rows;
    Vector totalSumN{totalDimensions, new double[totalDimensions]};
    Vector sumProductsXN{totalDimensions, new double[totalDimensions]};
    double sumXSquares = 0.0;

    for (int i = 0; i < points.rows; i++) {
        double currX = points.rowVector[i].vectorArray[0];
        sumXSquares += currX * currX;
        for (int j = 0; j < points.cols; j++) {
            totalSumN.vectorArray[j] += points.rowVector[i].vectorArray[j];
            sumProductsXN.vectorArray[j] += currX * points.rowVector[i].vectorArray[j];
        }
    }

    double slopes[totalDimensions];
    double initial[totalDimensions];
    slopes[0] = 1.0;
    initial[0] = 0.0;

    for (int i = 1; i < totalDimensions; i++) {
        double b = (totalVectors * sumProductsXN.vectorArray[i] - totalSumN.vectorArray[0] * totalSumN.vectorArray[i]) /
                   (totalVectors * sumXSquares - totalSumN.vectorArray[0] * totalSumN.vectorArray[0]);
        double s = (totalSumN.vectorArray[i] - b * totalSumN.vectorArray[0]) / totalVectors;
        slopes[i] = b;
        initial[i] = s;
    }
    return NDLine{Vector{totalDimensions, initial}, Vector{totalDimensions, slopes}};
}