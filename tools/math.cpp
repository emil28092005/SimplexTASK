#include "math.h"
#include "matrix.h"

double min(ColumnVector columnVector) {
    double temp = columnVector[0];
    for (int j = 0; j < columnVector.getColumns(); j++) {
        if (columnVector[j] < temp) {
            temp = columnVector[j];
        }
    }
    return temp;
}

double max(ColumnVector columnVector) {
    double temp = columnVector[0];
    for (int j = 0; j < columnVector.getColumns(); j++) {
        if (columnVector[j] > temp) {
            temp = columnVector[j];
        }
    }
    return temp;
}

int min_index(ColumnVector columnVector) {
    int temp_index = 0;
    double temp = columnVector[0];
    for (int j = 0; j < columnVector.getColumns(); j++) {
        if (columnVector[j] < temp) {
            temp_index = j;
            temp = columnVector[j];
        }
    }
    return temp_index;
}

int max_index(ColumnVector columnVector) {
    int temp_index = 0;
    double temp = columnVector[0];
    for (int j = 0; j < columnVector.getColumns(); j++) {
        if (columnVector[j] > temp) {
            temp_index = j;
            temp = columnVector[j];
        }
    }
    return temp_index;
}

double min(std::vector<double> array) {
    double temp = array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] < temp) {
            temp = array[i];
        }
    }
    return temp;
}

double max(std::vector<double> array) {
    double temp = array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] > temp) {
            temp = array[i];
        }
    }
    return temp;
}

int min_index(std::vector<double> array) {
    int temp_index = 0;
    double temp = array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] < temp) {
            temp_index = i;
            temp = array[i];
        }
    }
    return temp_index;
}


int max_index(std::vector<double> array) {
    int temp_index = 0;
    double temp = array[0];
    for (size_t i = 1; i < array.size(); i++) {
        if (array[i] > temp) {
            temp_index = i;
            temp = array[i];
        }
    }
    return temp_index;
}