#ifndef long_arithmetic
#define long_arithmetic

#include <iostream>
#include <string>
#include <exception> 
#include <cmath> 
#include <algorithm>

using namespace std;

#define EPS 1e-9

bool correct_num_value(const string &);
bool correct_frac_value(const string &);
int string_comp(const string &, const string &);
void del_nulls(string &);

class ArithmeticException: public exception {
    public:
        const char* what() const noexcept;
};

class NegativeValue: public exception {
    public:
        const char* what() const noexcept;
};

class BadString: public exception {
    public:
        const char* what() const noexcept;
};

class LongNum { // Целые длинные числа
    protected:
        string value_;
        bool sign_ = true;

        string similar_add(const string &, const string &);
        string different_add(const string &, const string &);
    public:
        LongNum(const int = 0);
        LongNum(const string &);
        LongNum(const string &, bool);

        string value() const;
        bool sign() const;

        bool operator <(const LongNum &);
        bool operator <=(const LongNum &);
        bool operator ==(const LongNum &);

        friend LongNum operator +(const LongNum &, const LongNum &);
        friend LongNum operator -(const LongNum &, const LongNum &);
        friend LongNum operator *(const LongNum &, const LongNum &);
        friend LongNum operator /(const LongNum &, const LongNum &);
        friend LongNum operator %(const LongNum &, const LongNum &);

        friend ostream &operator <<(ostream&, const LongNum &);
};

class LongFrac: public LongNum { // Рациональные длинные числа
    protected:
        string fraction_;

    public:
        LongFrac(const string &);
        LongFrac(const string &, const string &);
        LongFrac(const LongNum & = 0, const LongNum & = 0);

        string fraction() const;

        bool operator <(const LongFrac &);
        bool operator ==(const LongFrac &);

        friend LongFrac operator +(const LongFrac &, const LongFrac &);
        friend LongFrac operator -(const LongFrac &, const LongFrac &);
        friend LongFrac operator *(const LongFrac &, const LongFrac &);
        friend LongFrac operator /(const LongFrac &, const LongFrac &);
        friend LongFrac operator %(const LongFrac &, const LongFrac &);

        friend ostream &operator <<(ostream&, const LongFrac &);
}; 

class LongComplexNum: public LongNum { // Комплексные длинные числа
    protected:
        LongNum image_part_;

    public:
        LongComplexNum(const LongNum & = 0, const LongNum & = 0);
        LongNum Real_part() const;
        LongNum Image_part() const;

        bool operator ==(const LongComplexNum &);

        friend LongComplexNum operator +(const LongComplexNum &, const LongComplexNum &);
        friend LongComplexNum operator -(const LongComplexNum &, const LongComplexNum &);
        friend LongComplexNum operator *(const LongComplexNum &, const LongComplexNum &);
        friend LongComplexNum operator /(const LongComplexNum &, const LongComplexNum &);
        friend LongComplexNum operator %(const LongComplexNum &, const LongComplexNum &);

        friend ostream &operator <<(ostream&, const LongComplexNum &);
};

class LongComplexFrac: public LongFrac {
    protected:
        LongFrac image_fraction_;

    public:
        LongComplexFrac(const LongFrac &, const LongFrac &);
        LongFrac Real_frac() const;
        LongFrac Image_frac() const;

        bool operator ==(const LongComplexFrac &);

        friend LongComplexFrac operator +(const LongComplexFrac &, const LongComplexFrac &);
        friend LongComplexFrac operator -(const LongComplexFrac &, const LongComplexFrac &);
        friend LongComplexFrac operator *(const LongComplexFrac &, const LongComplexFrac &);
        friend LongComplexFrac operator /(const LongComplexFrac &, const LongComplexFrac &);
        friend LongComplexFrac operator %(const LongComplexFrac &, const LongComplexFrac &);

        friend ostream &operator <<(ostream&, const LongComplexFrac &);
};

#endif