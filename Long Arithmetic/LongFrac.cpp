#include "long_arithmetic.hpp"

//--------------------------------- LongFrac ---------------------------------

LongFrac::LongFrac(const string &str): LongNum(0) {
    string frac;
    bool flag = true;
    frac = str;

    if (frac[0] == '-' ) {
        flag = false;
        frac.erase(0, 1);
    }

    if (correct_frac_value(frac)) {
        throw BadString();
    }

    string val;
    for (int i = 0; i < frac.size(); i++) {
        if (i == frac.size()) {
            break;
        }

        if (frac[i] == ',' || frac[i] == '.') {
            frac.erase(0, 1);
            break;
        }

        val.push_back(frac[i]);
        frac.erase(0, 1);
        i--;
    }

    LongNum::value_ = val;
    LongNum::sign_ = flag;
 
    if (frac.size() == 0) {
        fraction_ = "0";
    } else {
        fraction_ = frac;
    }  
}

LongFrac::LongFrac(const string &val, const string &frac): LongNum(0) {
    string new_val = val;
    bool flag = true;
    if (val[0] == '-') {
            new_val.erase(0, 1);
            flag = false;
    }
    
    if (correct_frac_value(new_val) || correct_frac_value(frac)) {
        throw BadString();
    }

    if (frac[0] == '-') {
        throw NegativeValue();
    }

    LongNum::value_ = new_val;
    LongNum::sign_ = flag;
    fraction_ = frac;
}

LongFrac::LongFrac(const LongNum &val, const LongNum &frac): LongNum(0) {
    if (!frac.sign()) {
        throw NegativeValue();
    }

    LongNum::value_ = val.value();
    LongNum::sign_ = val.sign();

    fraction_ = frac.value();
}

string LongFrac::fraction() const { return fraction_; }

//---------------------------- LongFrac Operators ----------------------------

bool LongFrac::operator <(const LongFrac &tmp) {
    if ((int) sign() > (int) tmp.sign()) {
        return false;
    } else if ((int) sign() < (int) tmp.sign()) {
        return true;
    } else {
        if (this->value().size() > tmp.value().size()) {
            return false;
        } else if (this->value().size() < tmp.value().size()) {
            return true;
        } else {
            if (string_comp(this->value(), tmp.value()) == 1) {
                return true;
            } else if (string_comp(this->value(), tmp.value()) == 2) {
                if (string_comp(fraction_, tmp.fraction_) == 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool LongFrac::operator ==(const LongFrac &tmp) {
    if (this->sign() == tmp.sign()) {
        if (this->value() == tmp.value()) {
            if (fraction_ == tmp.fraction_) {
                return true;
            }
        }
    }

    return false;
}

LongFrac operator +(const LongFrac &num1, const LongFrac &num2) {
    LongFrac ans("0");

    string tmp_num1 = num1.value();
    if (!num1.sign()) {
        tmp_num1.insert(tmp_num1.begin(), '-');
    }

    string tmp_num2 = num2.value();
    if (!num2.sign()) {
        tmp_num2.insert(tmp_num2.begin(), '-');
    }

    LongNum tmp_val((LongNum(tmp_num1) + LongNum(tmp_num2)));

    tmp_num1 = num1.fraction_;
    tmp_num2 = num2.fraction_;

    //cout << tmp_num1 << "  " << tmp_num2 << endl;

    reverse(tmp_num1.begin(), tmp_num1.end());
    reverse(tmp_num2.begin(), tmp_num2.end());

    del_nulls(tmp_num1);

    del_nulls(tmp_num2);

    reverse(tmp_num1.begin(), tmp_num1.end());
    reverse(tmp_num2.begin(), tmp_num2.end());

    //cout << tmp_num1 << "   " << tmp_num2 << endl;

    if (tmp_num1.size() > tmp_num2.size()) {
        for (int i = tmp_num2.size(); i < tmp_num1.size(); i++) {
            tmp_num2.push_back('0');
        }
    } else if (tmp_num1.size() < tmp_num2.size()) {
        for (int i = tmp_num1.size(); i < tmp_num2.size(); i++) {
            tmp_num1.push_back('0');
        }
    }

    if (!num1.sign()) {
        if (tmp_num1 == "0" && tmp_num2 != "0" && num2.sign()) {
            tmp_num1.insert(tmp_num1.begin(), '1');
        }

        tmp_num1.insert(tmp_num1.begin(), '-');
    }

    if (!num2.sign()) {
        if (tmp_num2 == "0" && tmp_num1 != "0" && num1.sign()) {
            tmp_num2.insert(tmp_num2.begin(), '1');
        }

        tmp_num2.insert(tmp_num2.begin(), '-');
    }

    //cout << tmp_num1 << "      " << tmp_num2 << endl;

    LongNum tmp_frac((LongNum(tmp_num1) + LongNum(tmp_num2)));

    //cout << tmp_val << "      " << tmp_frac << endl;

    string tmp_nulls = tmp_frac.value();
    int j = 0;
    while (true) {
        if(tmp_num1[0] == '-' && tmp_num2[0] == '-') {
            if (tmp_num1[j + 1] == '0' && tmp_num2[j + 1] == '0') {
                tmp_nulls.insert(tmp_nulls.begin(), '0');
                j++;
            } else {
                break;
            }
        } else if (tmp_num1[0] == '-' && tmp_num2[0] != '-') {
            if (tmp_num1[j + 1] == '0' && tmp_num2[j] == '0') {
                tmp_nulls.insert(tmp_nulls.begin(), '0');
                j++;
            } else {
                break;
            }
        } else if (tmp_num1[0] != '-' && tmp_num2[0] == '-') {
            if (tmp_num1[j] == '0' && tmp_num2[j + 1] == '0') {
                tmp_nulls.insert(tmp_nulls.begin(), '0');
                j++;
            } else {
                break;
            }
        } else {
            if (tmp_num1[j] == '0' && tmp_num2[j] == '0') {
                tmp_nulls.insert(tmp_nulls.begin(), '0');
                j++;
            } else {
                break;
            }
        }
    }

    //cout << tmp_frac << endl;

    if (!tmp_frac.sign() && tmp_val.sign() && tmp_val.value() != "0") {
        tmp_val = tmp_val - 1;

        string minus = "1";
        for (int i = 0; i < tmp_frac.value().size(); i++) {
            minus.push_back('0');
        }

        tmp_frac = tmp_frac + minus;
    } else if (tmp_frac.sign() && !tmp_val.sign()) {
        tmp_val = tmp_val + 1;
        
        string minus = "1";
        for (int i = 0; i < tmp_frac.value().size(); i++) {
            minus.push_back('0');
        }

        tmp_frac = tmp_frac - minus;
    }

    //cout << tmp_val << "     " << tmp_frac << endl;

    if (tmp_val.value() == "0" && tmp_frac.value().size() != 1 && !tmp_frac.sign()) {
        tmp_val = tmp_val - 1;

        string minus = "10";
        int nulls = 0; 

        for (int i = 1; i < tmp_frac.value().size() - 1; i++) {
            minus.push_back('0');
        }

        while (true) {
            if (tmp_frac.value()[nulls + 1] == '0') {
                nulls++;
            } else {
                break;
            }
        }
        
        if (!tmp_frac.sign()) {
            tmp_frac = minus + tmp_frac;
        } else {
            tmp_frac = minus - tmp_frac;
        }

        //cout << tmp_val << "     " << tmp_frac << endl;
        
        string buf = tmp_frac.value();
        for (int i = 0; i < nulls; i++) {
            buf.insert(buf.begin(), '0');
        }

        tmp_frac = buf;
    }

    if (tmp_frac.value().size() > max(num1.fraction_.size(), num2.fraction_.size())) {
        if (!tmp_val.sign()) {
            tmp_val = tmp_val - 1;
        } else {
            tmp_val = tmp_val + 1;
        }

        //cout << tmp_val << "     " << tmp_frac << endl;
        
        string minus = "10";
        int nulls = 0; 

        for (int i = 1; i < tmp_frac.value().size() - 1; i++) {
            minus.push_back('0');
        }

        while (true) {
            if (tmp_frac.value()[nulls + 1] == '0') {
                nulls++;
            } else {
                break;
            }
        }
        
        if (!tmp_frac.sign()) {
            tmp_frac = minus + tmp_frac;
        } else {
            tmp_frac = minus - tmp_frac;
        }

        //cout << tmp_val << "     " << tmp_frac << endl;
        
        string buf = tmp_frac.value();
        for (int i = 0; i < nulls; i++) {
            buf.insert(buf.begin(), '0');
        }

        // reverse(buf.begin(), buf.end());

        // del_nulls(buf);

        // reverse(buf.begin(), buf.end());

        tmp_frac = buf;
    }

    //cout << tmp_val << "  " << tmp_frac << endl;

    tmp_nulls = tmp_frac.value();
    int flagic_1 = 0;
    int flagic_2 = 0;
    if (tmp_num1[0] == '-') {
        flagic_1++;
    }

    if (tmp_num2[0] == '-') {
        flagic_2++;
    }

    if (j == 0 && tmp_frac.value().size() < max(tmp_num1.size() - flagic_1, tmp_num2.size() - flagic_2)) {
        for (int i = tmp_frac.value().size(); i < max(tmp_num1.size() - flagic_1, tmp_num2.size() - flagic_2); i++) {
            tmp_nulls.insert(tmp_nulls.begin(), '0');
            //cout << tmp_nulls << endl;
        }
    }

    //cout << tmp_nulls << endl;

    if (!tmp_frac.sign()) {
        tmp_nulls.insert(tmp_nulls.begin(), '-');
    }

    LongNum tmp_nulls_num(tmp_nulls, true);

    tmp_frac = tmp_nulls_num;

    //cout << tmp_frac << endl;

    if (tmp_frac.value()[0] == '1' && tmp_frac.value().size() != 1) {
        int flag = 1;
        for (int i = 0; i < tmp_frac.value().size() - 1; i++) {
            if (tmp_frac.value()[i] != '0') {
                flag--;
                break;
            }
        }

        if (flag) {
            string minus = "10";

            for (int i = 1; i < tmp_frac.value().size() - 1; i++) {
                minus.push_back('0');
            }

            if (tmp_frac.sign()) {
                tmp_frac = tmp_frac - minus;
            } else {
                tmp_frac = tmp_frac + minus;
            }
            
            
            if (tmp_val.sign()) {
                tmp_val = tmp_val + 1;
            } else {
                tmp_val = tmp_val - 1;
            }
        }
    }

    if (tmp_val.value() == "0") {
        ans.LongNum::sign_ = tmp_frac.sign();
    } else {
        ans.LongNum::sign_ = tmp_val.sign();
    }

    string buf = tmp_frac.value();
    reverse(buf.begin(), buf.end());

    del_nulls(buf);

    reverse(buf.begin(), buf.end());


    tmp_frac = LongNum(buf, true);
    
    ans.LongNum::value_ = tmp_val.value();
    ans.fraction_ = tmp_frac.value();

    return ans;
}

LongFrac operator -(const LongFrac &num1, const LongFrac &num2) {
    LongFrac ans(num1.value());

    if ((num1.sign() && num2.sign()) || (!num1.sign() && num2.sign())) {
        string buf = num2.value();
        buf.insert(buf.begin(), '-');

        LongFrac num3(buf, num2.fraction_);

        ans = num1 + num3;
    } else if (!num1.sign() && !num2.sign()) {
        LongFrac num3(num2.value() , num2.fraction_);
        
        ans = num1 + num3;
    } else if (num1.sign() && !num2.sign()) {
        LongFrac num3(num2.value() , num2.fraction_);

        ans = num1 + num3;
    }

    return ans;
}

LongFrac operator *(const LongFrac &num1, const LongFrac &num2) {
    LongFrac ans(num1.value());

    int null_1 = 0;
    string tmp1 = num1.value();

    int null_2 = 0;
    string tmp2 = num2.value();

    for (int i = 0; i < num1.fraction_.size(); i++) {
        null_1++;
        tmp1.push_back('0');
    }

    LongNum num1_tmp(tmp1);
    num1_tmp = num1_tmp + num1.fraction_;

    for (int i = 0; i < num2.fraction_.size(); i++) {
        null_2++;
        tmp2.push_back('0');
    }

    LongNum num2_tmp(tmp2);
    num2_tmp = num2_tmp + num2.fraction_;

    ans = num1_tmp * num2_tmp;

    string tmp_val;
    string tmp_frac;

    if (null_1 + null_2 < ans.value().size()) {
        for (int i = 0; i < ans.value().size() - (null_1 + null_2); i++) {
            tmp_val.push_back(ans.value()[i]);
        }
    } else {
        tmp_val.push_back('0');
    }
    
    if (null_1 + null_2 < ans.value().size()) {
        for (int i = ans.value().size() - (null_1 + null_2); i < ans.value().size(); i++) {
            tmp_frac.push_back(ans.value()[i]);
        }
    } else {
        for (int i = 0; i < (null_1 + null_2) - ans.value().size(); i++) {
            tmp_frac.push_back('0');
        }

        for (int i = 0; i < ans.value().size(); i++) {
            tmp_frac.push_back(ans.value()[i]);
        }
    }
    
    if (tmp_val.size() == 0) {
        tmp_val.push_back('0');
    }

    ans.LongNum::value_ = tmp_val;

    reverse(tmp_frac.begin(), tmp_frac.end());

    del_nulls(tmp_frac);

    reverse(tmp_frac.begin(), tmp_frac.end());

    ans.fraction_ = tmp_frac;

    if ((num1.sign() && !num2.sign()) || (!num1.sign() && num2.sign())) {
        ans.LongNum::sign_ = false;
    }

    return ans;
}

LongFrac operator /(const LongFrac &num1, const LongFrac &num2) {
    LongFrac ans(num1.value());

    string tmp1 = num1.value();
    string tmp2 = num2.value();

    for (int i = 0; i < max(num1.fraction_.size(), num2.fraction_.size()); i++) {
        tmp1.push_back('0');
    }

    LongNum num1_tmp(tmp1);
    num1_tmp = num1_tmp + num1.fraction_;

    for (int i = 0; i < max(num1.fraction_.size(), num2.fraction_.size()); i++) {
        tmp2.push_back('0');
    }

    LongNum num2_tmp(tmp2);
    num2_tmp = num2_tmp + num2.fraction_;

    //cout << num1_tmp << "    " << num2_tmp << endl;

    LongNum buf(0);

    buf = num1_tmp / num2_tmp;

    ans.LongNum::value_ = buf.value();
    ans.fraction_ = "0";

    if ((num1.sign() && !num2.sign()) || (!num1.sign() && num2.sign())) {
        ans.LongNum::sign_ = false;
    }

    return ans;
}

LongFrac operator %(const LongFrac &num1, const LongFrac &num2) {
    LongFrac ans(num1.value());

    if (!num1.sign() || !num2.sign()) {
        throw NegativeValue();
    }

    string tmp1 = num1.value();
    tmp1.push_back('.');
    for (int i = 0; i < num1.fraction_.size(); i++) {
        tmp1.push_back(num1.fraction_[i]);
    }

    string tmp2 = num2.value();
    tmp2.push_back('.');
    for (int i = 0; i < num2.fraction_.size(); i++) {
        tmp2.push_back(num2.fraction_[i]);
    }

    LongFrac num1_tmp(tmp1);
    LongFrac num2_tmp(tmp2);

   // cout << num1_tmp << "    " << num2_tmp << endl;

    if (num1_tmp == num2_tmp) {
        ans.LongNum::value_ = "0";
        ans.fraction_ = "0";

        return ans;
    }

    if (num1_tmp < num2_tmp) {
        ans = num1;
        return ans;
    }

    ans = num1_tmp - ((num1_tmp / num2_tmp) * num2_tmp);

    //cout << (num1_tmp / num2_tmp) * num2_tmp << endl;

    return ans;
}