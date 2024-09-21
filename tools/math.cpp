#include "math.h"
#include "matrix.h"

double Math::minVector(ColumnVector columnVector) {
    double temp = columnVector[0];
    for (int j = 0; j < columnVector.getColumns(); j++) {
        if (columnVector[j] < temp) {
            temp = columnVector[j];
        }
    }
    return temp;
}

double Math::maxVector(ColumnVector columnVector) {
    double temp = columnVector[0];
    for (int j = 0; j < columnVector.getColumns(); j++) {
        if (columnVector[j] > temp) {
            temp = columnVector[j];
        }
    }
    return temp;
}

double Math::minArray(std::vector<double> array) {
    double temp = array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] < temp) {
            temp = array[i];
        }
    }
    return temp;
}

double Math::maxArray(std::vector<double> array) {
    double temp = array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] > temp) {
            temp = array[i];
        }
    }
    return temp;
}
