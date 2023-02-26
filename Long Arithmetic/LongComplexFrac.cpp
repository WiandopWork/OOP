#include "long_arithmetic.hpp"

//--------------------------------- LongComplexFrac ---------------------------------

LongComplexFrac::LongComplexFrac(const LongFrac &real, const LongFrac &image): LongFrac(real.value(), real.fraction()) {
    this->LongNum::sign_ = real.sign();
    this->LongNum::value_ = real.value();
    this->fraction_ = real.fraction();

    image_fraction_ = image;
}

LongFrac LongComplexFrac::Real_frac() const { 
    string tmp;
    if (!this->LongNum::sign()) {
        tmp.push_back('-');
    }

    for (int i = 0; i < this->LongNum::value().size(); i++) {
        tmp.push_back(this->LongNum::value()[i]);
    }

    tmp.push_back('.');

    for (int i = 0; i < this->fraction().size(); i++) {
        tmp.push_back(this->fraction()[i]);
    }


    LongFrac ans(tmp);

    return ans;
}

LongFrac LongComplexFrac::Image_frac() const { return image_fraction_; }

//--------------------------------- LongComplexFrac operators ---------------------------------

bool LongComplexFrac::operator ==(const LongComplexFrac &num) {
    if (this->Real_frac() == num.Real_frac()) {
        if (this->Image_frac() == num.Image_frac()) {
            return true;
        }
    }

    return false;
}

LongComplexFrac operator +(const LongComplexFrac &num1, const LongComplexFrac &num2) {
    LongFrac tmp_real("0");
    tmp_real = num1.Real_frac() + num2.Real_frac();

    LongFrac tmp_image("0");
    tmp_image = num1.Image_frac() + num2.Image_frac();

    LongComplexFrac ans(tmp_real, tmp_image);

    return ans;
}

LongComplexFrac operator -(const LongComplexFrac &num1, const LongComplexFrac &num2) {
    LongFrac tmp_real("0");
    tmp_real = num1.Real_frac() - num2.Real_frac();

    LongFrac tmp_image("0");
    tmp_image = num1.Image_frac() - num2.Image_frac();

    LongComplexFrac ans(tmp_real, tmp_image);

    return ans;
}

LongComplexFrac operator *(const LongComplexFrac &num1, const LongComplexFrac &num2) {
    LongFrac tmp_real("0");
    tmp_real = (num1.Real_frac() * num2.Real_frac()) - (num1.Image_frac() * num2.Image_frac());

    //cout << num1.Real_frac() * num2.Real_frac() << endl;
    //cout << (num1.Image_frac() * num2.Image_frac()) << endl;

    LongFrac tmp_image("0");
    tmp_image = (num1.Real_frac() * num2.Image_frac()) + (num1.Image_frac() * num2.Real_frac());

    LongComplexFrac ans(tmp_real, tmp_image);

    return ans;
}

LongComplexFrac operator /(const LongComplexFrac &num1, const LongComplexFrac &num2) {
    LongFrac tmp_real("0");
    tmp_real = ((num1.Real_frac() * num2.Real_frac()) + (num1.Image_frac() * num2.Image_frac())) / (num2.Real_frac() * num2.Real_frac() + num2.Image_frac() * num2.Image_frac());

    LongFrac tmp_image("0");
    tmp_image = ((num2.Real_frac() * num1.Image_frac()) - (num2.Image_frac() * num1.Real_frac())) / (num2.Real_frac() * num2.Real_frac() + num2.Image_frac() * num2.Image_frac());

    LongComplexFrac ans(tmp_real, tmp_image);

    return ans;
}

LongComplexFrac operator %(const LongComplexFrac &num1, const LongComplexFrac &num2) {
    LongComplexFrac ans(LongFrac("0"), LongFrac("0"));

    ans = num1 - ((num1 / num2) * num2);
    return ans;
}