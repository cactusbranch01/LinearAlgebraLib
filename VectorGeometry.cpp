//
// Created by Ben Roberts on 6/16/2023.
//

#include "VectorGeometry.h"

void printPoint(Point p) {
    std::cout << p.x << " ";
    std::cout << p.y << " ";
    std::cout << std::endl;
    std::cout << "" << std::endl;
}

void printVector(Vector v) {
    for (int i = 0; i < v.dim; i++) {
        std::cout << v.vectorArray[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "" << std::endl;
}

Matrix createMatrix(Vector* vectors, int numVectors) {
    Matrix m{};
    m.rows = numVectors;
    int cols = 0;
    // Find the vec with the highest dimension in the set of vectors.
    // Then this dim will become the dim of the matrix.
    for (int i = 0; i < numVectors; i++) {
        if (vectors[i].dim > cols) {
            cols = vectors[i].dim;
        }
    }
    m.cols = cols;
    m.rowVector = new Vector[m.rows];
    // Copy the vectors into the matrix.
    for (int i = 0; i < m.rows; i++) {
        m.rowVector[i].dim = m.cols;
        m.rowVector[i].vectorArray = new double[m.cols];
        // If the vector has a lower dim then the matrix we can just fill in 0s.
        for (int j = 0; j < m.cols; j++) {
            if (vectors[i].dim > j) {
                m.rowVector[i].vectorArray[j] = vectors[i].vectorArray[j];
            } else {
                m.rowVector[i].vectorArray[j] = 0.0;
            }
        }
    }
    return m;
}

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.rowVector[i].dim; j++) {
            std::cout << matrix.rowVector[i].vectorArray[j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "" << std::endl;
}

Vector addVectors (Matrix m) {
    Vector result{};
    result.dim = m.cols;
    result.vectorArray = new double[m.cols]();

    // Add the vectors component-wise
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.vectorArray[j] += m.rowVector[i].vectorArray[j];
        }
    }
    return result;
}

Matrix reduce(Matrix m) {
    for (int piv = 0; piv < m.rows; piv++) {
        double t1 = m.rowVector[piv].vectorArray[piv];
        for (int j = piv + 1; j < m.rows; j++) {
            if (m.rowVector[piv].vectorArray[j] != 0) {
                double t2 = m.rowVector[j].vectorArray[piv];
                double t3 = 0.0;
                if (t2 != 0)
                {
                    t3 = t1 / t2;
                }
                for (int z = piv; z < m.rows; z++) {
                    m.rowVector[j].vectorArray[z] = m.rowVector[piv].vectorArray[z] - (m.rowVector[j].vectorArray[z] * t3);
                    if (m.rowVector[j].vectorArray[z] < 1e-14 && m.rowVector[j].vectorArray[z] > -1e-14)
                    {
                        m.rowVector[j].vectorArray[z] = 0;
                    }
                }
            }
        }
    }
    return m;
}

double det(Matrix& m) {
    double det = 1.0;
    for (int piv = 0; piv < m.rows - 1; piv++) {
        double t1 = m.rowVector[piv].vectorArray[piv];
        if (t1 == 0) {
            return 0.0;
        }
        for (int j = piv + 1; j < m.rows; j++) {
            if (m.rowVector[j].vectorArray[piv] != 0) {
                double t2 = m.rowVector[j].vectorArray[piv];
                double t3;
                if (t2 != 0) {
                    t3 = t1 / t2;
                    if (t3 == 0) {
                        return 0.0;
                    }
                    det /= -t3;
                } else {
                    return 0.0;
                }
                for (int z = piv; z < m.rows; z++) {
                    m.rowVector[j].vectorArray[z] = m.rowVector[piv].vectorArray[z] - (m.rowVector[j].vectorArray[z] * t3);
                    if (m.rowVector[j].vectorArray[z] < 1e-14 && m.rowVector[j].vectorArray[z] > -1e-14) {
                        m.rowVector[j].vectorArray[z] = 0;
                    }
                }
            }
        }
    }
    for (int i = 0; i < m.rows; i++) {
        det *= m.rowVector[i].vectorArray[i];
    }
    return det;
}

Matrix RREF(Matrix m) {
    const int rows = m.rows; // number of rows
    const int cols = m.cols; // number of columns
    int pivCol = 0;

    while (pivCol < rows) {
        double t1, t2;

        for (int r = 0; r < rows; r++) {
            t1 = m.rowVector[pivCol].vectorArray[pivCol];
            t2 = 0;
            if (t1 != 0 && m.rowVector[r].vectorArray[pivCol] != 0) {
                t2 = m.rowVector[r].vectorArray[pivCol] / m.rowVector[pivCol].vectorArray[pivCol];
            }

            for (int c = 0; c < cols; c++) {
                if (r == pivCol) {
                    if (t1 != 0 && m.rowVector[r].vectorArray[c] != 0) {
                        m.rowVector[r].vectorArray[c] /= t1; // make pivot 1
                    } else {
                        m.rowVector[r].vectorArray[c] = 0;
                    }
                }
                else {
                    double t3 = m.rowVector[pivCol].vectorArray[c] * t2;
                    if (t3 != 0) {
                        m.rowVector[r].vectorArray[c] -= t3;
                    }
                }
            }
        }
        pivCol++;
    }
    return m;
}