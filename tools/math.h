#ifndef MATH_H
#define MATH_H

#include <vector>

class ColumnVector;

class Math {
public:
    double minVector(ColumnVector columnVector);
    double maxVector(ColumnVector columnVector);
    double minArray(std::vector<double> array);
    double maxArray(std::vector<double> array);
};

#endif // MATH_H