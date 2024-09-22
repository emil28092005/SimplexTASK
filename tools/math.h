#ifndef MATH_H
#define MATH_H

#include <vector>

class ColumnVector;

class Math {
public:
    double min(ColumnVector columnVector);
    double max(ColumnVector columnVector);
    static int min_index(ColumnVector columnVector);
    static int max_index(ColumnVector columnVector);
    double min(std::vector<double> array);
    double max(std::vector<double> array);
    int min_index(std::vector<double> array);
    int max_index(std::vector<double> array);
};

#endif // MATH_H