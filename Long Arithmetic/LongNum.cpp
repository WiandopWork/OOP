#include "long_arithmetic.hpp"

//--------------------------------- LongNum private ---------------------------------

string LongNum::similar_add(const string &str1, const string &str2) {
    string ans;

    string str1_tmp = str1;
    reverse(str1_tmp.begin(), str1_tmp.end());

    string str2_tmp = str2;
    reverse(str2_tmp.begin(), str2_tmp.end());

    if (str1_tmp.size() > str2_tmp.size()) {
        for (int i = str2_tmp.size(); i < str1_tmp.size(); i++) {
            str2_tmp.push_back('0');
        }
    } else if (str1_tmp.size() < str2_tmp.size()) {
        for (int i = str1_tmp.size(); i < str2_tmp.size(); i++) {
            str1_tmp.push_back('0');
        }
    }

    int num = 0;
    int flag = 0;
    for (int i = 0; i <= str2_tmp.size(); i++) {
        if (i == str2_tmp.size()) {
            if (flag == 1) {
                ans.push_back('1');
                break;
            } else {
                break;
            }
        }

        num = (str1_tmp[i] - '0') + (str2_tmp[i] - '0');

        if (flag == 1) {
            num++;
            flag = 0;
        }

        if (num >= 10) {
            flag++;
            num = num % 10;
        }

        ans.push_back(num + '0');
        num = 0;
    }

    reverse(ans.begin(), ans.end());

    del_nulls(ans);

    return ans;
}

string LongNum::different_add(const string &str1, const string &str2) {
    string ans;

    string str1_tmp = str1;
    if (str1_tmp[0] == '-') {
        str1_tmp.erase(0, 1);
    }

    string str2_tmp = str2;
    if (str2_tmp[0] == '-') {
        str2_tmp.erase(0, 1);
    }

    int sum_flag = 0;
    if (str2_tmp.size() > str1_tmp.size()) {
            sum_flag = 1;
    } else if (str2_tmp.size() < str1_tmp.size()) {
        sum_flag = 0;
    } else {
        for (int i = 0; i < str2_tmp.size(); i++) {
            if (str2_tmp[i] - '0' > str1_tmp[i] - '0') {
                sum_flag = 1;
            } else if (str2_tmp[i] - '0' == str1_tmp[i] - '0') {
                continue;
            } else {
                break;
            }
        }
    }

    reverse(str1_tmp.begin(), str1_tmp.end());
    reverse(str2_tmp.begin(), str2_tmp.end());

    if (str1_tmp.size() > str2_tmp.size()) {
        for (int i = str2_tmp.size(); i < str1_tmp.size(); i++) {
            str2_tmp.push_back('0');
        }
    } else if (str1_tmp.size() < str2_tmp.size()) {
        for (int i = str1_tmp.size(); i < str2_tmp.size(); i++) {
            str1_tmp.push_back('0');
        }
    }

    int sign_flag = 0;
    if (str1[0] == '-') {
        if (str1.size() - 1 > str2.size()) {
            sign_flag = 1;
        } else if (((str1.size() - 1 == str2.size()))) {
            for (int i = 0; i < str2.size(); i++) {
                if (str1[i + 1] - '0' > str2[i] - '0') {
                    sign_flag = 1;
                } else if (str1[i + 1] - '0' == str2[i] - '0') {
                    continue;
                } else {
                    break;
                }
            }
        }
    }

    if (str2[0] == '-') {
        if (str2.size() - 1 > str1.size()) {
            sign_flag = 1;
        } else if (((str2.size() - 1 == str1.size()))) {
            for (int i = 0; i < str1.size(); i++) {
                if (str2[i + 1] - '0' > str1[i] - '0') {
                    sign_flag = 1;
                } else if (str2[i + 1] - '0' == str1[i] - '0') {
                    continue;
                } else {
                    break;
                }
            }
        }
    }

    int flag = 0;
    int num = 0;

    for (int i = 0; i < str1_tmp.size(); i++) {
        if (sum_flag) {
            num = (str2_tmp[i] - '0') - flag - (str1_tmp[i] - '0');
        } else {
            num = (str1_tmp[i] - '0') - flag - (str2_tmp[i] - '0');
        }

        if (flag) {
            flag = 0;
        }

        if (num < 0) {
            flag++;
            num += 10;
        }
        
        ans.push_back(num + '0');
    }

    if (sign_flag) {
        ans.push_back('-');
    }

    reverse(ans.begin(), ans.end());
    
    while(true) {
        if (ans[0] == '-') {
            if (ans[1] == '0') {
                ans.erase(1, 1);
            } else {
                break;
            }
        } else {
            if (ans[0] == '0') {
                ans.erase(0, 1);
            } else {
                break;
            }
        }
    }

    return ans;
}

//--------------------------------- LongNum ---------------------------------

LongNum::LongNum(const int num) {
    if (num < 0) {
        sign_ = false;
        value_ = to_string(abs(num));
    } else {
        value_ = to_string(num);
    }   
}

LongNum::LongNum(const string &str) {
    if (str.size() == 0) {
        throw BadString();
    }

    string val;
    val = str;

    if (val[0] == '-') {
        sign_ = false;
        val.erase(0, 1);
    }

    if (correct_num_value(val)) {
        throw BadString();
    }

    del_nulls(val);

    value_ = val;
}

LongNum::LongNum(const string &str, bool nulls) {
    if (str.size() == 0) {
        throw BadString();
    }

    string val;
    val = str;

    if (val[0] == '-') {
        sign_ = false;
        val.erase(0, 1);
    }

    if (correct_num_value(val)) {
        throw BadString();
    }

    if (!nulls) {
        del_nulls(val);
    }

    value_ = val;
}

string LongNum::value() const { return value_; }

bool LongNum::sign() const { return sign_; }

//---------------------------- LongNum Operators ----------------------------

bool LongNum::operator <(const LongNum &tmp) {
    if ((int) sign() > (int) tmp.sign()) {
        return false;
    } else if ((int) sign() < (int) tmp.sign()) {
        return true;
    } else {
        if (string_comp(this->value_, tmp.value_) == 1) {
            return true;
        }
    }

    return false;
}

bool LongNum::operator <=(const LongNum &tmp) {
    if (sign_ == tmp.sign_) {
        if (value_ == tmp.value_) {
            return true;
        }
    }

    if ((int) sign() > (int) tmp.sign()) {
        return false;
    } else if ((int) sign() < (int) tmp.sign()) {
        return true;
    } else {
        if (string_comp(this->value_, tmp.value_) == 1) {
            return true;
        }
    }

    return false;
}

bool LongNum::operator ==(const LongNum &tmp) {
    if (sign_ == tmp.sign_) {
        if (value_ == tmp.value_) {
            return true;
        }
    }

    return false;
}

LongNum operator +(const LongNum &num1, const LongNum &num2) {
    if (num1.sign_ && num2.sign_) {
        LongNum ans(0);
        ans.value_ = ans.LongNum::similar_add(num1.value_, num2.value_);

        return ans;
    } else if (!num1.sign_ && !num2.sign_) {
        LongNum ans(0);
        ans.value_ = ans.LongNum::similar_add(num1.value_, num2.value_);
        ans.sign_ = false;

        return ans;
    } else {
        LongNum ans(0);

        string num1_tmp;
        if (!num1.sign_) {
            num1_tmp.push_back('-');
        }
        for (int i = 0; i < num1.value_.size(); i++) {
            num1_tmp.push_back(num1.value_[i]);
        }

        string num2_tmp;
        if (!num2.sign_) {
            num2_tmp.push_back('-');
        }
        for (int i = 0; i < num2.value_.size(); i++) {
            num2_tmp.push_back(num2.value_[i]);
        }

        //cout << num1_tmp << " " << num2_tmp << endl;

        string tmp = ans.LongNum::different_add(num1_tmp, num2_tmp);

        if (tmp[0] == '-') {
            ans.sign_ = false;
            tmp.erase(0, 1);
        }

        if (tmp.size() == 0){
            tmp.push_back('0');
        }

        ans.value_ = tmp;

        return ans;
    }
}

LongNum operator -(const LongNum &num1, const LongNum &num2) {
    LongNum ans(0);

    if ((num1.sign_ && num2.sign_) || (!num1.sign_ && num2.sign_)) {
        LongNum num3(num2.value_);
        num3.sign_ = false;

        ans = num1 + num3;
    } else if (!num1.sign_ && !num2.sign_) {
        LongNum num3(num2.value_);
        
        ans = num1 + num3;
    } else if (num1.sign_ && !num2.sign_) {
        LongNum num3(num2.value_);

        ans = num1 + num3;
    }

    return ans;
}

LongNum operator *(const LongNum &num1, const LongNum &num2) {
    LongNum ans(0);
    LongNum cur(0);

    string num1_tmp = num1.value_;
    string num2_tmp = num2.value_;

    reverse(num1_tmp.begin(), num1_tmp.end());
    reverse(num2_tmp.begin(), num2_tmp.end());

    //cout << num1_tmp << " " << num2_tmp << endl;

    string tmp;
    int flag = 0;
    int num = 0;

    for (int i = 0; i < num2_tmp.size(); i++) {
        for (int j = 0; j <= num1_tmp.size(); j++) {
            if (j == num1_tmp.size()) {
                if (flag != 0) {
                    tmp.push_back(flag + '0');
                    flag = 0;
                    break;
                } else {
                    flag = 0;
                    break;
                }
            }
                

            num = (num2_tmp[i] - '0') * (num1_tmp[j] - '0') + flag;

            if (num >= 10) {
                flag = num / 10;
                num = num % 10;
            } else {
                flag = 0;
            }
                

           // cout << "num: " << num << endl;
            //cout << "flag: " << flag << endl;

            tmp.push_back(num + '0');
        }

        reverse(tmp.begin(), tmp.end());

        for (int k = 0; k < i; k++) {
            tmp.push_back('0');
        }

        //cout << tmp << endl;

        cur.value_ = tmp;
        tmp.clear();

        ans = ans + cur;
    }
    
    if ((num1.sign_ && !num2.sign_) || (!num1.sign_ && num2.sign_)) {
        ans.sign_ = false;
    }

    return ans;
}

LongNum operator /(const LongNum &num1, const LongNum &num2) {
    if (num2.value_ == "0") {
        throw ArithmeticException();
    }

    LongNum ans(0);

    if (num1.value_ == "0") {
        return ans;
    }

    if (num1.value_ == num2.value_) {
        if ((!num1.sign_ && num2.sign_) || (num1.sign_ && !num2.sign_)) {
            ans.sign_ = false;
        } 

        ans.value_ = "1";

        return ans;
    }

    if (num2.value_ == "1") {
        if ((!num1.sign_ && num2.sign_) || (num1.sign_ && !num2.sign_)) {
            ans.sign_ = false;
        } 

        ans.value_ = num1.value_;

        return ans;
    }

    LongNum num2_buf(num2.value_);
    LongNum num1_buf(num1.value_);

    if (string_comp(num1_buf.value_, num2_buf.value_) == 1) {
        return ans;
    }

    LongNum cur(0);

    LongNum left(1);
    LongNum right(10);

    int buf = num1_buf.value_.size() - num2_buf.value_.size();
    for (int i = 1; i <= abs(buf); i++) {
        right = right * 10;
    }

    while (left <= right) {
        LongFrac mid(left + right);
        mid = (mid * LongFrac("0.5"));

        ans.value_ = mid.value();

        cur = ans * num2_buf;

        // cout << "ans: " << ans << endl;
        // cout << "cur: " << cur << endl;
        // cout << endl;

        if (cur == num1_buf) {
            return ans;
        } else if (num1_buf < cur) {
            right = LongNum(mid.value()) - 1;
        } else {
            left = LongNum(mid.value()) + 1;
        }
    }

    if (num1_buf < cur) {
        ans = ans - 1;
    }

    if ((num1.sign_ && !num2.sign_) || (!num1.sign_ && num2.sign_)) {
        ans.sign_ = false;
    }
    
    return ans;
}

LongNum operator %(const LongNum &num1, const LongNum &num2) {
    if (num2.value_ == "0") {
        throw ArithmeticException();
    }

    if (!num1.sign_ || !num2.sign_) {
        throw NegativeValue();
    }

    LongNum ans(0);

    if (num1.value_ == "0") {
        return ans;
    }


    if (string_comp(num1.value_, num2.value_) == 1) {
        ans.value_ = num1.value_;
        return ans;
    }

    ans = num1 - ((num1 / num2) * num2);

    return ans;
}