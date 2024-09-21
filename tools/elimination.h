#ifndef ELIMINATION_H
#define ELIMINATION_H



class Elimination {
    public:
    Matrix elimination(Matrix A, ColumnVector C, ColumnVector b, int pivot_column_index, int pivot_row_index, double eps);
};



#endif //ELIMINATION_H
