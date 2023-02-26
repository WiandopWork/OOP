#include "long_arithmetic.hpp"

int main() {
    cout << "LongNum:" << endl;
    try {
        LongNum A("154543514534562");
        LongNum B("1513532154154231435435135");

        cout << "+: " << A + B << endl;
        cout << "-: " << A - B << endl;
        cout << "*: " << A * B << endl;
        cout << "/: " << B / A << endl;
        cout << "%: " << B % A << endl;
    } 
    catch (const exception &ex) {
        cout << ex.what() << endl;
    }  

    cout << endl;

    cout << "LongFrac:" << endl;
    try {
        LongFrac A("15487789.43131356");
        LongFrac B("7989658.12656");

        cout << "+: " << A + B;
        cout << "-: " << A - B;
        cout << "*: " << A * B;
        cout << "/: " << A / B;
        cout << "%: " << A % B;
    } 
    catch (const exception &ex) {
        cout << ex.what() << endl;
    }  

    cout << endl;

    cout << "LongComplexNum:" << endl;
    try {
        LongNum A("125895");
        LongNum B("789545");

        LongComplexNum C(A, B);
        LongComplexNum D(LongNum(45664), LongNum(421000));

        cout << "+: " << C + D << endl;
        cout << "-: " << C - D << endl;
        cout << "*: " << C * D << endl;
        cout << "/: " << C / D << endl;
        cout << "%: " << C % D << endl;
    } 
    catch (const exception &ex) {
        cout << ex.what() << endl;
    }  

    cout << endl;

    cout << "LongComplexFrac:" << endl;
    try {
        LongFrac A("1");
        LongFrac B("1.123");

        LongComplexFrac C(A, B);
        LongComplexFrac D(LongFrac(1), LongFrac(2));

        cout << "+: " << C + D << endl;
        cout << "-: " << C - D << endl;
        cout << "*: " << C * D << endl;
        cout << "/: " << C / D << endl;
        cout << "%: " << C % D << endl;
    } 
    catch (const exception &ex) {
        cout << ex.what() << endl;
    } 
    return 0;
}