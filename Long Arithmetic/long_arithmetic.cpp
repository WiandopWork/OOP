#include "long_arithmetic.hpp"

bool correct_num_value(const string &str) {
    for (int i = 0; i < str.size(); i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            if ((str[i] == '-') && i == 0) {
                continue;
            }

            return true;
        }
    }

    return false;
}

bool correct_frac_value(const string &str) {
    for (int i = 0; i < str.size(); i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            if (((str[i] == '.') || (str[i] == ','))) {
                continue;
            }

            if ((str[i] == '-') && i == 0) {
                continue;
            }

            return true;
        }
    }

    return false;
}

int string_comp(const string &str1, const string &str2) {
    if (str1.size() < str2.size()) {
        return 1;
    } else if (str1.size() == str2.size()) {
        for (int i = 0; i < str2.size(); i++) {
            if ((str2[i] - '0') > (str1[i] - '0')) {
                return 1;
            } else if ((str2[i] - '0') == (str1[i] - '0')) {
                continue;
            } else {
                return 0;
            }
        }
    } else {
        return 0;
    }

    return 2;
}

void del_nulls(string &str) {
    while(true) {
        if (str[0] == '0') {
            str.erase(0, 1);
        } else {
            break;
        }
    }

    if (str.size() == 0) {
        str.push_back('0');
    }

    return;
}

//-------------------------------- Exceptions --------------------------------

const char* ArithmeticException::what() const noexcept {
    return "Division by zero";
}

const char* NegativeValue::what() const noexcept {
    return "Negative Value";
}

const char* BadString::what() const noexcept {
    return "Invalid Value";
}

//----------------------------------- Out -----------------------------------

ostream &operator <<(ostream& out, const LongNum &cur) {
    if (!cur.sign_) {
        out << '-';
    }

    for (int i = 1; i <= cur.value_.size(); i++) {
        out << cur.value_[i - 1];

        if (i == cur.value_.size()) {
            continue;
        } else if (i == (cur.value_.size() % 3)) {
            out << ' ';
        } else if (i > (cur.value_.size() % 3) && (i - (cur.value_.size() % 3)) % 3 == 0) {
            out << ' ';
        } 
    }
    

    return out;
}

ostream &operator <<(ostream& out, const LongFrac &cur) {
    if (!cur.sign_) {
        out << '-';
    }

    for (int i = 1; i <= cur.value_.size(); i++) {
        out << cur.value_[i - 1];

        if (i == cur.value_.size()) {
            continue;
        } else if (i == (cur.value_.size() % 3)) {
            out << ' ';
        } else if (i > (cur.value_.size() % 3) && (i - (cur.value_.size() % 3)) % 3 == 0) {
            out << ' ';
        } 
    }
    
    out << '.' << cur.fraction_ << endl;

    return out;
}

ostream &operator <<(ostream& out, const LongComplexNum &cur) {
    if (!cur.sign_) {
        out << '-';
    }

    out << cur.value_;

    if (!cur.image_part_.sign()) {
        out << " - ";
    } else {
        out << " + ";
    }

    out << cur.image_part_.value();

    out << "i";

    return out;
}

ostream &operator <<(ostream& out, const LongComplexFrac &cur) {
    if (!cur.sign()) {
        out << '-';
    }

    out << cur.Real_frac().value() << '.' << cur.Real_frac().fraction();

    if (!cur.Image_frac().sign()) {
        out << " - ";
    } else {
        out << " + ";
    }

    out << cur.Image_frac().value() << '.' << cur.Image_frac().fraction();

    out << "i";

    return out;
}