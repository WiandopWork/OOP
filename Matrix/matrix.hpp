#ifndef start
#define start

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

typedef double elem_t;

class Matrix {
    elem_t ** data;
    int row_count = 0, col_count = 0;

    int sigma(const vector <int> &) const;
    elem_t cofactor(int, int) const;

    public:
        Matrix(const int, const int, const elem_t = 0);
        Matrix(const int, bool = true, const elem_t = 0);
        Matrix(const vector <vector <elem_t> > &);
        Matrix(const vector <elem_t> &, bool = true);
        Matrix(const Matrix &);
        ~Matrix();

        int get_row();
        int get_col();
        elem_t get_by_pos(const int, const int);
        pair <int, int> get_by_val(const elem_t &);
        void set_by_pos(const int, const int, const elem_t &);
        void set_all_zero();

        Matrix operator =(const Matrix &);
        Matrix & operator +(const Matrix &);
        Matrix & operator -(const Matrix &);
        Matrix operator *(const Matrix &) const;
        Matrix operator ^(const int);

        friend Matrix operator *(const double, const Matrix &);
        friend Matrix operator *(const Matrix &, const double);
        friend ostream &operator <<(ostream&, const Matrix &);

        elem_t det() const;
        Matrix inverse() const;
};

#endif
