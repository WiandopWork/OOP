#include <iostream>
#include <vector>
#include "matrix.hpp"

using namespace std;

int main() {
    vector < vector <elem_t> > V1 {{1, 2}, {3, 4}};
    vector < vector <elem_t> > V2 {{8, 10}, {9, 6}};
    Matrix mat_1(V1);
    Matrix mat_2(V2);

    cout << "+: " << endl << mat_1 + mat_2 << endl;
    cout << "-: " << endl << mat_1 - (mat_2 * 2) << endl;
    cout << "*: " << endl << mat_2 * 2 << endl;

    Matrix mat_3(2, 2, 5);
    cout << "^: " << endl << (mat_3 ^ 2) << endl;

    Matrix mat_4(V1);
    cout << "inverse: " << endl << mat_4.inverse() << endl;

    return 0;
}

