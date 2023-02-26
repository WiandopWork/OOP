#include "long_arithmetic.hpp"

//--------------------------------- LongComplexNum ---------------------------------

LongComplexNum::LongComplexNum(const LongNum &real, const LongNum &image): LongNum(0) {
    this->LongNum::value_ = real.value();
    this->LongNum::sign_ = real.sign();

    image_part_ = image;
}

LongNum LongComplexNum::Real_part() const {
    string tmp;
    if (!this->LongNum::sign()) {
        tmp.push_back('-');
    }

    for (int i = 0; i < this->LongNum::value().size(); i++) {
        tmp.push_back(this->LongNum::value()[i]);
    }

    LongNum ans(tmp);

    return ans;
}

LongNum LongComplexNum::Image_part() const { return image_part_; }

//--------------------------------- LongComplexNum operators ---------------------------------

bool LongComplexNum::operator ==(const LongComplexNum &num) {
    if (this->Real_part() == num.Real_part()) {
        if (this->Image_part() == num.Image_part()) {
            return true;
        }
    }

    return false;
}

LongComplexNum operator +(const LongComplexNum &num1, const LongComplexNum &num2) {
    LongNum tmp_real(0);
    tmp_real = num1.Real_part() + num2.Real_part();

    LongNum tmp_image(0);
    tmp_image = num1.Image_part() + num2.Image_part();

    LongComplexNum ans(tmp_real, tmp_image);

    return ans;
}

LongComplexNum operator -(const LongComplexNum &num1, const LongComplexNum &num2) {
    LongNum tmp_real(0);
    tmp_real = num1.Real_part() - num2.Real_part();

    LongNum tmp_image(0);
    tmp_image = num1.Image_part() - num2.Image_part();

    LongComplexNum ans(tmp_real, tmp_image);

    return ans;
}

LongComplexNum operator *(const LongComplexNum &num1, const LongComplexNum &num2) {
    LongNum tmp_real(0);
    tmp_real = (num1.Real_part() * num2.Real_part()) - (num1.Image_part() * num2.Image_part());

    LongNum tmp_image(0);
    tmp_image = (num1.Real_part() * num2.Image_part()) + (num1.Image_part() * num2.Real_part());

    LongComplexNum ans(tmp_real, tmp_image);

    return ans;
}

LongComplexNum operator /(const LongComplexNum &num1, const LongComplexNum &num2) {
    LongNum tmp_real(0);
    tmp_real = ((num1.Real_part() * num2.Real_part()) + (num1.Image_part() * num2.Image_part())) / (num2.Real_part() * num2.Real_part() + num2.Image_part() * num2.Image_part());

    LongNum tmp_image(0);
    tmp_image = ((num2.Real_part() * num1.Image_part()) - (num2.Image_part() * num1.Real_part())) / (num2.Real_part() * num2.Real_part() + num2.Image_part() * num2.Image_part());

    LongComplexNum ans(tmp_real, tmp_image);

    return ans;
}

LongComplexNum operator %(const LongComplexNum &num1, const LongComplexNum &num2) {
    LongComplexNum ans;

    ans = num1 - ((num1 / num2) * num2);

    return ans;
}