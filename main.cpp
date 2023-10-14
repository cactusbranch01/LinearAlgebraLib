//
// Created by Ben Roberts on 6/16/2023.
//

#include <iostream>
#include "testing.h"

int main() {

    // Test Linear Regression method with 2 points (O(n) where n is the # points).
    // Previous test averaged .00333 seconds per 1,000,000 point simulation.
    double avg1 = testLinReg(100, 1000000);
    std::cout << avg1 << " seconds average per regression on each 1,000,000 simulation." << std::endl;

    // Test upper triangular reduction (O(n^2) where n is # dim).
    // Previous test averaged .00321 seconds per 100x100 matrix.
    double avg2 = testReduce(100, 100);
    std::cout << avg2 << " seconds average per reduction of each 100x100 matrix." << std::endl;

    // Test det on square matrices (O(n^2) where n is # dim).
    // Previous test averaged .00321 seconds per 100x100 matrix.
    double avg3 = testDet(100, 100);
    std::cout << avg3 << " seconds average per determinant computation on each 100x100 matrix." << std::endl;

    // Test RREF on square matrices (n! where n is # dim).
    // Previous test averaged .00255 seconds per 100x100 matrix.
    double avg4 = testRREF(100, 100);
    std::cout << avg4 << " seconds average per reduced row echelon form on each 100x100 matrix." << std::endl;

    // Test Linear Regression method with  points (O(mn) where n is the # points in m dimensions).
    // Previous test averaged .00301 seconds per 1,000 vector simulation in 1,000 dimensions.
    double avg5 = testLinReg2(100, 1000, 1000);
    std::cout << avg5 << " seconds average per regression on each set of 1,000 vectors in 1,000 dimensions." << std::endl;

    return 0;
}