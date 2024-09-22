#ifndef MATH_H
#define MATH_H

#include <vector>
#include "matrix.h"

double min(Vector vector);
double max(Vector vector);
int min_index(Vector vector);
int max_index(Vector vector);
double min(std::vector<double> array);
double max(std::vector<double> array);
int min_index(std::vector<double> array);
int max_index(std::vector<double> array);

#endif // MATH_H