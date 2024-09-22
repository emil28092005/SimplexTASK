#include "math.h"

double min(Vector vector) {
    double temp = vector[0];
    for (int j = 0; j < vector.size(); j++) {
        if (vector[j] < temp) {
            temp = vector[j];
        }
    }
    return temp;
}

double max(Vector vector) {
    double temp = vector[0];
    for (int j = 0; j < vector.size(); j++) {
        if (vector[j] > temp) {
            temp = vector[j];
        }
    }
    return temp;
}

int min_index(Vector vector) {
    int temp_index = 0;
    double temp = vector[0];
    for (int j = 0; j < vector.size(); j++) {
        if (vector[j] < temp) {
            temp_index = j;
            temp = vector[j];
        }
    }
    return temp_index;
}

int max_index(Vector vector) {
    int temp_index = 0;
    double temp = vector[0];
    for (int j = 0; j < vector.size(); j++) {
        if (vector[j] > temp) {
            temp_index = j;
            temp = vector[j];
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