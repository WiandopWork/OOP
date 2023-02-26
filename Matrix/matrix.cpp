#include "matrix.hpp"

ostream &operator <<(ostream& out, const Matrix &A) {
    for (int i = 0; i < A.row_count; i++) {
        for (int j = 0; j < A.col_count; j++) {
            out << A.data[i][j] << " ";
        }
        out << endl;
    }

    return out;
}

Matrix::Matrix(const int n, const int m, const elem_t def_val) {
    if (n < 0 || m < 0) {
        cerr << "Negative value" << endl;
        exit;
    }

    row_count = n;
    col_count = m;

    data = new elem_t* [row_count];
    for (int i = 0; i < row_count; i++) {
        data[i] = new elem_t [col_count];

        for (int j = 0; j < col_count; j++) {
            data[i][j] = def_val;
        }
    }
}

Matrix::Matrix(const int n, bool is_col, const elem_t def_val) {
    if (n < 0) {
        cerr << "Negative value" << endl;
        exit;
    }

    if (is_col) {
        row_count = n;
        col_count = 1;

        data = new elem_t* [row_count];

        for (int i = 0; i < row_count; i++) {
            data[i] = new elem_t [col_count];

            for (int j = 0; j < col_count; j++) {
                data[i][j] = def_val;
            }
        }
    } else {
        row_count = 1;
        col_count = n;

        data = new elem_t* [row_count];

        data[row_count - 1] = new elem_t [col_count];

        for (int i = 0; i < col_count; i++) {
            data[row_count - 1][i] = def_val;
        }
    }
}

Matrix::Matrix(const vector <vector <elem_t> > &vec) {
    row_count = vec.size();
    col_count = vec[0].size();

    for (int i = 1; i < row_count; i++) {
        if (vec[i].size() != col_count) {
            cerr << "Different values" << endl;
            exit;
        }
    }

    data = new elem_t* [row_count];

    for (int i = 0; i < row_count; i++) {
        data[i] = new elem_t[col_count];

        for (int j = 0; j < col_count; j++) {
            data[i][j] = vec[i][j];
        }
    }
}

Matrix::Matrix(const vector <elem_t> &vec, bool is_col) {
    if (is_col) {
        row_count = vec.size();
        col_count = 1;

        data = new elem_t* [row_count];

        for (int i = 0; i < row_count; i++) {
            data[i] = new elem_t [col_count];

            for (int j = 0; j < col_count; j++) {
                data[i][j] = vec[i];
            }
        }
    } else {
        row_count = 1;
        col_count = vec.size();

        data = new elem_t* [row_count];

        data[row_count - 1] = new elem_t [col_count];

        for (int i = 0; i < col_count; i++) {
            data[row_count - 1][i] = vec[i];
        }
    }
}

Matrix::Matrix(const Matrix &matrix) {
    row_count = matrix.row_count;
    col_count = matrix.col_count;

    data = new elem_t* [row_count];
    for (int i = 0; i < row_count; i++) {
        data[i] = new elem_t [col_count];

        for (int j = 0; j < col_count; j++) {
            data[i][j] = matrix.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < row_count; i++) {
        delete[] data[i];
    }

    delete[] data;
}

int Matrix::get_row() { return row_count; }
int Matrix::get_col() { return col_count; }
elem_t Matrix::get_by_pos(const int n, const int m) { return data[n][m]; }

pair <int, int> Matrix::get_by_val(const elem_t &val) {
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            if (data[i][j] == val) {
                return (make_pair(i, j));
            }
        }
    }

    return make_pair(-1, -1);
}

void Matrix::set_by_pos(const int n, const int m, const elem_t &val) { data[n][m] = val; }

void Matrix::set_all_zero() {
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            data[i][j] = 0;
        }
    }
}

Matrix Matrix::operator =(const Matrix &matrix) {
    if (row_count != matrix.row_count || col_count != matrix.col_count) {
        for (int i = 0; i < row_count; i++) {
            delete[] data[i];
        }

        delete[] data;
    }

    row_count = matrix.row_count;
    col_count = matrix.col_count;

    data = new elem_t* [row_count];
    for (int i = 0; i < row_count; i++) {
        data[i] = new elem_t [col_count];

        for (int j = 0; j < col_count; j++) {
            data[i][j] = matrix.data[i][j];
        }
    }

    return *this;
}


Matrix & Matrix::operator +(const Matrix &matrix) {
    if (row_count != matrix.row_count || col_count != matrix.col_count) {
        cerr << "Bad dimensions" << endl;
        return *this;
    }

    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            data[i][j] += matrix.data[i][j];
        }
    }

    return *this;
}

Matrix & Matrix::operator -(const Matrix &matrix) {
    if (row_count != matrix.row_count || col_count != matrix.col_count) {
        cerr << "Bad dimensions" << endl;
        return *this;
    }

    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            data[i][j] -= matrix.data[i][j];
        }
    }

    return *this;
}

Matrix Matrix::operator *(const Matrix &matrix) const {
    if (col_count != matrix.row_count) {
        cerr << "Bad dimensions" << endl;
        return matrix;
    }

    Matrix res(row_count, matrix.col_count);

    for (int i = 0; i < res.row_count; i++) {
        for (int j = 0; j < res.col_count; j++) {
            for (int k = 0; k < col_count; k++) {
                res.data[i][j] += data[i][k] * matrix.data[k][j];
            }
        }
    }

    return res;
}

Matrix operator *(const double val, const Matrix &matrix) {
    for (int i = 0; i < matrix.row_count; i++) {
        for (int j = 0; j < matrix.col_count; j++) {
            matrix.data[i][j] *= val;
        }
    }

    return matrix;
}

Matrix operator *(const Matrix &matrix, const double val) {
    for (int i = 0; i < matrix.row_count; i++) {
        for (int j = 0; j < matrix.col_count; j++) {
            matrix.data[i][j] *= val;
        }
    }

    return matrix;
}

Matrix Matrix::operator ^(const int val) {
    if (row_count != col_count) {
        cerr << "Bad dimensions" << endl;
        return *this;
    }

    Matrix res = *this;

    for (int i = 1; i < val; i++) {
        *this = (*this) * res;
    }

    return *this;
}

int Matrix::sigma(const vector <int> &alpha) const {
    int res = 0;

    for (int i = 0; i < alpha.size(); i++) {
        for (int j = i + 1; j < alpha.size(); j++) {
            if (alpha[i] > alpha[j]) {
                res++;
            }
        }
    }

    return res % 2;
}

elem_t Matrix::cofactor(int x, int y) const {
    elem_t res = (x + y) % 2 ? -1 : 1;
    Matrix wA(row_count - 1, col_count - 1);

    int n = 0;
    int m = 0;

    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            if (i == x) {
                continue;
            }

            if (j == y) {
                continue;
            }

            wA.data[n][m] = data[i][j];
            m++;
        }

        if (i != x) {
            n++;
        }

        m = 0;
    }

    return res * (wA.det());
}

elem_t Matrix::det() const {
    if (row_count != col_count) {
        cerr << "Bad dimensions" << endl;
        return -1e9;
    }

    vector <int> alpha(col_count);
    elem_t ans = 0;

    for (int i = 1; i <= col_count; i++) {
        alpha[i - 1] = i;
    }

    do { // Запустится n! раз и alpha будет очередной перестановкой
        elem_t tmp = (sigma(alpha) == 0 ? 1 : -1);

        for (int i = 0; i < col_count; i++) {
            tmp *= data[i][alpha[i] - 1];
        }

        ans += tmp;
    } while (next_permutation(alpha.begin(), alpha.end()));

    return ans;
}

Matrix Matrix::inverse() const {
    if (row_count != col_count) {
        cerr << "Bad dimensions" << endl;
        return *this;
    }

    Matrix res(row_count, col_count);

    for (int i = 0; i < res.row_count; i++) {
        for (int j = 0; j < res.col_count; j++) {
            res.data[i][j] = (this->cofactor(i, j));
        }
    }

    double tmp = (1.0 / (this->det()));
    res * tmp;

    return res;
}